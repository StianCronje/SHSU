//This program is based on the article in
//https://learnopengl.com/Lighting/Basic-Lighting
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// to scale
#include <glm/gtc/matrix_transform.hpp> 
using namespace glm;

#include "common/shader.hpp"
#include "common/controls.hpp"
#include "common/objloader.hpp"
//For using the clock
#include <chrono>
//for loading the image
#include <soil.h>

int width, height;
unsigned char* image;


GLuint loadtextures(const char* filename)
{
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	if (image == NULL)
		printf("Could not load the texture image from path %s!\n", filename);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return textureId;
}




int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "Light.vertexshader", "My_Diffuse_Ambient.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Load the texture
	//GLuint Texture = loadtextures("L200-OBJ/truck_color.jpg");
	GLuint Texture = loadtextures("L200-OBJ-triangles/truck_color.jpg");
	
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("L200-OBJ-triangles/truck.obj", vertices, uvs, normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	//Added to load normals from the file
	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	clock_t begin = clock();

	

	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);


		

		glm::mat4 trans;
		//Rotate the car about Y axis
		clock_t end = clock();
		float elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		//Rotate
		//you can control the speed of the rotation if you multiply elapsed_secs*glm::radians(180.0f) (180.0f isjust an example)
		//trans = glm::rotate(trans, -elapsed_secs, glm::vec3(0.0f, 1.0f, 0.0f));
		//Scale down
		trans = glm::scale(trans, glm::vec3(0.4f, 0.4f, 0.4f));
		GLint uniTrans = glGetUniformLocation(programID, "trans");
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Set the ambient light color
		GLint Ambient_Light_color = glGetUniformLocation(programID, "ambientColor");
		glUniform3fv(Ambient_Light_color, 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));

		//Diffuse Staff
		// Set the Diffuse light Position
		GLint Diffuse_Light_position = glGetUniformLocation(programID, "lightPos");
		glUniform3fv(Diffuse_Light_position, 1, glm::value_ptr(glm::vec3(4.0, 50.0, 4.0)));
		GLint Diffuse_Light_position1 = glGetUniformLocation(programID, "lightPos1");
		glUniform3fv(Diffuse_Light_position1, 1, glm::value_ptr(glm::vec3(40.0, 0.0, 0.0)));
		GLint Diffuse_Light_position2 = glGetUniformLocation(programID, "lightPos2");
		glUniform3fv(Diffuse_Light_position2, 1, glm::value_ptr(glm::vec3(-40.0, 0.0, 0.0)));
		// Set the Diffuse light Position
		GLint Diffuse_Light_color = glGetUniformLocation(programID, "lightColor");
		glUniform3fv(Diffuse_Light_color, 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
		GLint Diffuse_Light_color1 = glGetUniformLocation(programID, "lightColor1");
		glUniform3fv(Diffuse_Light_color1, 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
		GLint Diffuse_Light_color2 = glGetUniformLocation(programID, "lightColor2");
		glUniform3fv(Diffuse_Light_color2, 1, glm::value_ptr(glm::vec3(0.0, 0.0, 1.0)));


		//Specular Staff
		//Set the Cameraposition (eye location)
		GLint eye_location = glGetUniformLocation(programID, "vertexPosition_cameraspace");
		glm::vec3 CameraPosition = getCameraPosition();
		glUniform3fv(eye_location, 1, glm::value_ptr(CameraPosition));
		//Set the specular color
		GLint Spec_Light_color = glGetUniformLocation(programID, "specColor");
		glUniform3fv(Spec_Light_color, 1, glm::value_ptr(glm::vec3(0.0, 1.0, 0.0)));
		// Set the Specular light Position
		GLint Spec_Light_position = glGetUniformLocation(programID, "speclightPos");
		glUniform3fv(Spec_Light_position, 1, glm::value_ptr(glm::vec3(0.0, -50.0, 0.0)));

		
		 
		

			


		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);


		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);


		// Draw the Model !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

