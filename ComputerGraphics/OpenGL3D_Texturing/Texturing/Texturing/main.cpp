/*
* OGL01Shape3D.cpp: 3D Shapes
*/
#include <windows.h>  // for MS Windows
#include <gl/glew.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <string>

#include <stdlib.h>

#include <SOIL.h>
#include <FreeImage.h>

using namespace std;

/* Global variables */
char buffer[256];
char title[] = "3D Shapes";
static GLfloat g_fViewDistance = 5;
static BOOL g_bButton1Down = FALSE;
static int g_yClick = 0;

int width, height;
unsigned char* image;

GLuint loadtextures(const char* filename)
{
	//textures are objects that need to be generated first by calling a function.
	GLuint textureId;
	glGenTextures(1, &textureId);
	// textures have to be bound to apply operations to them.
	//Since images are 2D arrays of pixels, it will be bound to the GL_TEXTURE_2D target.
	glBindTexture(GL_TEXTURE_2D, textureId);
	//Load an image using SOIL
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	printf("The width and height of the image %s are (%d, %d) respectively \n", filename, width, height);
	//free the memory from the image since no need now for the image
	SOIL_free_image_data(image);
	return textureId;
}

GLuint _textureId, _textureId1; //The id of the texture
GLuint _cubeTextures[6];

GLUquadric *quad;
GLUquadric *quad2;
GLfloat rotat = 0;

/* Initialize OpenGL Graphics */
void initGL() {
	glClearDepth(1.0f);                   // Set background depth to farthest

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < 6; i++)
	{
		sprintf_s(buffer, "%s%d.jpg", "face", i);
		printf("%s\n", buffer);

		_cubeTextures[i] = loadtextures(buffer);
	}

}


/* Handler for window-repaint event. Called back when the window first appears and
whenever the window needs to be re-painted. */

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix									
	glLoadIdentity();                 // load the model-view matrix
	gluLookAt(5, 5, g_fViewDistance, 0, 0, -1, 0, 1, 0);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, _cubeTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);					// glBegin		
	// Top face (y = 1.0f
	glTexCoord2d(1, 1);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2d(0, 1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();							 //glEnd


	glBindTexture(GL_TEXTURE_2D, _cubeTextures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);					//glBegin
	// Bottom face (y = -1.0f)
	glTexCoord2d(1, 1);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2d(0, 1);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();							//glEnd

	glBindTexture(GL_TEXTURE_2D, _cubeTextures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);					//glBegin
	// Front face  (z = 1.0f)
	glTexCoord2d(1, 1);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2d(0, 1);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();							//glEnd

	glBindTexture(GL_TEXTURE_2D, _cubeTextures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);					//glBegin
	// Back face (z = -1.0f)
	glTexCoord2d(1, 1);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2d(0, 1);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();							//glEnd

	glBindTexture(GL_TEXTURE_2D, _cubeTextures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);					//glBegin
	// Left face (x = -1.0f)
	glTexCoord2d(1, 1);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2d(0, 1);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();							//glEnd

	glBindTexture(GL_TEXTURE_2D, _cubeTextures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);					//glBegin
	// Right face (x = 1.0f)
	glTexCoord2d(1, 1);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2d(0, 1);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2d(0, 0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();							//glEnd 

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
											   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.01f, 100.0f); // Enable perspective projection with fovy, aspect, zNear and zFar
}

void MouseButton(int button, int state, int x, int y)
{
	// Respond to mouse button presses.
	// If button1 pressed, mark this state so we know in motion function.
	if (button == GLUT_LEFT_BUTTON)
	{
		g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
		g_yClick = y - g_fViewDistance;
		printf("g_yClick is %d\n", g_yClick);

	}
}
void MouseMotion(int x, int y)
{
	// If button1 pressed, zoom in/out if mouse is moved up/down.
	if (g_bButton1Down)
	{
		g_fViewDistance = (y - g_yClick);
		printf("The eye location is %f and the mouse co-ordinates are (%d, %d) and \n", g_fViewDistance, x, y);
		if (g_fViewDistance < 0)
			g_fViewDistance = 0;
		glutPostRedisplay();
	}
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);				// Initialize GLUT
	glutInitWindowSize(640, 480);		// Set the window's initial width & height	
	glutCreateWindow(title);			// Create window with the given title
	glutDisplayFunc(display);			// Register callback handler for window re-paint event
	glutReshapeFunc(reshape);		    // Register callback handler for window re-size event
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	initGL();							// Our own OpenGL initialization
	glutMainLoop();						// Enter the infinite event-processing loop
	return 0;
}