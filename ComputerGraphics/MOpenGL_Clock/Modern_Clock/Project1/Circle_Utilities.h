#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>



using namespace std;

// Main variables in the program.  
#define MAINPROGRAM  
#include <math.h>
#include <GLFW\glfw3.h>

#include <vector>

#include <windows.h>  // for MS Windows

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


const double PI = 3.141592653589793238463;

class Circle_Utilities
{
public:	
	GLfloat* generateframe(float radius)
	{
		GLfloat* vertices;// = new g_vertex_buffer_data[720];

	/*	for (int a = 0; a < 720; a++)
		{
			float angle = 2.0f*PI*(float(a) / 360.0f);
			GLfloat x = cosf(angle)*0.9;
			GLfloat y = sinf(angle)*0.9;			

			vertices[a * 2] = x;
			vertices[a * 2 + 1] = y;			
		}*/
		vertices[0] = 3;
		return vertices;
	}
};