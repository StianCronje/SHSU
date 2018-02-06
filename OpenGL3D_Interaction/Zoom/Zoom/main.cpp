/*
* OGL01Shape3D.cpp: 3D Shapes
*/
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <string>

/* Global variables */
char title[] = "3D Shapes";
static GLfloat g_fViewDistance = 5;
static BOOL g_bButton1Down = FALSE;
static int g_yClick = 0;

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling	
}


/* Handler for window-repaint event. Called back when the window first appears and
whenever the window needs to be re-painted. */

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix									
	glLoadIdentity();                 // load the model-view matrix
	gluLookAt(-3, 0, g_fViewDistance, 0, 0, -1, 0, 1, 0);

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads									  
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube

			  //	glColor3f(1.0f, 0.0f, 0.0f);
			  //	glutWireTeapot(1);

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

void KeyboardButton(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
	case 'W':
		if (g_fViewDistance > 0)
		{
			g_fViewDistance -= 1;
		}
		break;
	case 's':
	case 'S':if (g_fViewDistance < 100)
	{
		g_fViewDistance += 1;
	}
			 break;
	default:
		break;
	}
		glutPostRedisplay();
}

void SpecialKey(int button, int x, int y)
{
	switch (button)
	{
	case GLUT_KEY_UP:
		if (g_fViewDistance > 0)
		{
			g_fViewDistance -= 1;
		}
		break;
	case GLUT_KEY_DOWN:
		if (g_fViewDistance < 100)
	{
		g_fViewDistance += 1;
	}
			 break;
	default:
		break;
	}
	glutPostRedisplay();
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
	//glutKeyboardUpFunc(KeyboardButton);
	glutKeyboardFunc(KeyboardButton);
	glutSpecialFunc(SpecialKey);
	initGL();							// Our own OpenGL initialization
	glutMainLoop();						// Enter the infinite event-processing loop
	return 0;
}