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
	window = glfwCreateWindow(1024, 768, "Blue Pentagon", NULL, NULL);
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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vs", "SimpleFragmentShader.fs");

	/*
		0.0f, 1.0f, 0.0f,
		0.7f, 0.2f, 0.0f,
		0.5f, -1.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,
		-0.7f, 0.2f, 0.0f,
	*/

	static const GLfloat g_vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.8f, 0.2f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.8f, 0.2f, 0.0f,
		0.5f, -1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.5f, -1.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,
		-0.8f, 0.2f, 0.0f,

		0.0f, 0.0f, 0.0f,
		-0.8f, 0.2f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	/////////////////////////////////////////////// 
	// 2) create a buffer object name(ID) holder.
	GLuint vertexbuffer;
	///////////////////////////////////////////////
	// 3) reserve/generate a buffer object name(ID).
	// void glGenBuffers(GLsizei n, GLuint * buffers);
	// n: number of names to be generated. (you can generate more than one name) // buffers: names generated.
	glGenBuffers(1, &vertexbuffer);
	///////////////////////////////////////////////
	// 4) set myBufferID as the current GL_ARRAY_BUFFER.
	// note that since this is the first time we bind myBufferID,
	// in this step OpenGL will both allocate and bind the buffer object.
	// void glBindBuffer(GLenum target,GLuint buffer); 
	// target: Specifies the target to which the buffer object is bound.
	// buffer: Specifies the name of a buffer object.
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//Fill the buffer with the vertices data 
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// The program Loop
	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);


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
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			0            // array buffer offset
		);

		// Use our shader
		glUseProgram(programID);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 15); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

