// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>
#include <GL/glut.h>
// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include "shader.hpp"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <chrono>

const double PI = 3.141592653589793238463;
int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "The CLOCK", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
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

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint FrameArrayID,hand1ArrayID, hand2ArrayID;
	glGenVertexArrays(1, &FrameArrayID);
	glGenVertexArrays(1, &hand1ArrayID);
	glGenVertexArrays(1, &hand2ArrayID);
	

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("circlevertex.vs", "circleframe2.fs");
	GLuint hand1ID = LoadShaders("hand1vertex.vs", "hand1frame.fs");
	GLuint hand2ID = LoadShaders("hand2vertex.vs", "hand2frame.fs");
	

	
	const GLfloat RADIUS = 0.9f;
	//generate the vertices of the clock frame
	GLfloat frame_buffer_data[720];
	for (int a = 0; a <720; a++)
	{
		float angle = 2.0f*PI*(float(a) / 360.0f);
		GLfloat x = cosf(angle)*RADIUS;
		GLfloat y = sinf(angle)*RADIUS;
		int tmp = a*2;

		frame_buffer_data[a*2] = x;
		frame_buffer_data[a * 2 + 1] = y;
	}
	
	/////////////////////////////////////////////// 
	// 2) create a buffer object name(ID) holder.
	GLuint vertexbuffer,hands1Buffer, hands2Buffer;
	///////////////////////////////////////////////
	// 3) reserve/generate a buffer object name(ID).
	// void glGenBuffers(GLsizei n, GLuint * buffers);
	// n: number of names to be generated. (you can generate more than one name) // vertexbuffer: names generated.
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &hands1Buffer);
	glGenBuffers(1, &hands2Buffer);




	// the seconds hand	
	GLfloat hand1_buffer_data[10];
	hand1_buffer_data[0] = -0.01;
	hand1_buffer_data[1] = 0;
	hand1_buffer_data[2] = 0.01;
	hand1_buffer_data[3] = 0;
	hand1_buffer_data[4] = 0.01;
	hand1_buffer_data[5] = 0.6;
	hand1_buffer_data[6] = 0;
	hand1_buffer_data[7] = 0.9;
	hand1_buffer_data[8] = -0.01;
	hand1_buffer_data[9] = 0.6;
	
	// the minutes hand	
	GLfloat hand2_buffer_data[10];
	hand2_buffer_data[0] = -0.02;
	hand2_buffer_data[1] = 0;
	hand2_buffer_data[2] = 0.02;
	hand2_buffer_data[3] = 0;
	hand2_buffer_data[4] = 0.02;
	hand2_buffer_data[5] = 0.02;
	hand2_buffer_data[6] = 0;
	hand2_buffer_data[7] = 0.8;
	hand2_buffer_data[8] = -0.02;
	hand2_buffer_data[9] = 0.6;


	clock_t begin = clock();
	// The program Loop
	 do {
		 
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(FrameArrayID);
		///////////////////////////////////////////////
		// set myBufferID as the current GL_ARRAY_BUFFER.
		// note that since this is the first time we bind myBufferID,
		// in this step OpenGL will both allocate and bind the buffer object.
		// void glBindBuffer(GLenum target,GLuint buffer); 
		// target: Specifies the target to which the buffer object is bound.
		// buffer: Specifies the name of a buffer object.
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//Fill the buffer with the vertices data 
		glBufferData(GL_ARRAY_BUFFER, sizeof(frame_buffer_data), frame_buffer_data, GL_STATIC_DRAW);
		// 1rst attribute buffer : vertices
		//the attributes are 0 indexed, and here we have only one attribute
		glEnableVertexAttribArray(0);		
		// specify the vertex-data format.
		// void glVertexAttribPointer( 
		// GLuint index, (the index of the attribute you are describing) 
		// GLint size, (the number of elements in that attribute)
		// GLenum type, (the type of each element in that attribute) 
		// GLboolean normalized, (do you want to normalize the data?) 
		// GLsizei stride, (the offset between each instance of that attribute)
		// const GLvoid * pointer (the offset of the first component of the first instance of the attribute) );
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		

		// Use the frmaes shaders shader
		glUseProgram(programID);
		// Draw the Circle!
		glPointSize(10.0f);

		clock_t end1 = clock();
		float elapsed_secs1 = double(end1 - begin) / CLOCKS_PER_SEC;
		GLint uniColor1 = glGetUniformLocation(programID, "framecolor");
		glUniform3f(uniColor1, 0.0f, 0.0f, abs(sin(elapsed_secs1*glm::radians(25.0f))));

		
		glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
		glDisableVertexAttribArray(0);


		//Minutes hands
		glBindVertexArray(hand1ArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, hands1Buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(hand1_buffer_data), hand1_buffer_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);		
		glUseProgram(hand1ID);		
		glDrawArrays(GL_TRIANGLE_FAN, 0, 5);
		glDisableVertexAttribArray(0);

		//Seconds hands
		glBindVertexArray(hand2ArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, hands2Buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(hand2_buffer_data), hand2_buffer_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glUseProgram(hand2ID);
		GLint uniColor2 = glGetUniformLocation(hand2ID, "sechandcolor");
		glUniform3f(uniColor2, 0.0f, abs(sin(elapsed_secs1*glm::radians(25.0f))), 0.0f);

		//Transformation of the seconds hand
		//https://open.gl/transformations
		clock_t end = clock();
		float elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		//printf("%f", elapsed_secs);
		glm::mat4 trans;
		trans = glm::rotate(trans, -elapsed_secs*glm::radians(25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		GLint uniTrans = glGetUniformLocation(hand2ID, "trans");
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

		//change the color of the hand at run tim
		//https://open.gl/drawing
		GLint uniColor = glGetUniformLocation(hand2ID, "handColor");
		glUniform3f(uniColor, 0.0f, abs(sin(elapsed_secs*glm::radians(25.0f))), 0.0f);
		printf("%f\n", abs(sin(elapsed_secs*glm::radians(25.0f))));
		glDrawArrays(GL_TRIANGLE_FAN, 0, 5);
		glDisableVertexAttribArray(0);
		//

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &hands1Buffer);
	glDeleteBuffers(1, &hands2Buffer);
	glDeleteVertexArrays(1, &FrameArrayID);
	glDeleteVertexArrays(1, &hand1ArrayID);
	glDeleteVertexArrays(1, &hand2ArrayID);
	glDeleteProgram(programID);
	glDeleteProgram(hand1ID);
	glDeleteProgram(hand2ID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

