#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <gl/glew.h>
#include <GL/glut.h>

#include <SOIL.h>
#include <FreeImage.h>


using namespace std;


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


void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}


//Makes the image into a texture, and returns the id of the texture


GLuint _textureId, _textureId1; //The id of the texture
GLuint _cubeTextures[6];

GLUquadric *quad;
GLUquadric *quad2;
GLfloat rotat = 0;

void initRendering() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	quad = gluNewQuadric();
	quad2 = gluNewQuadric();
	_textureId = loadtextures("pyramids.jpg");
	_textureId1 = loadtextures("2.jpg");

	//for (int i = 0; i < sizeof(_cubeTextures)/sizeof(*_cubeTextures); i++)
	//{
	//	string fullName;
	//	string strIndex;
	//	sprintf(strIndex, "%d", i);
	//	string name = "test";
	//	fullName = name + strIndex;
	//	printf("%s\n", fullName);


	//	//_cubeTextures[i] = loadtextures("")
	//}

}


void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);

}


void drawScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// The big pyrmaid
	glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and in depth into the screen		
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles									 // Front

	glTexCoord2d(0.5, 1);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glTexCoord2d(0.5, 1);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2d(1, 0);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glTexCoord2d(0.5, 1);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2d(1.0, 0);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glTexCoord2d(0.5, 1);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0, 0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2d(1.0, 0);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();   // Done drawing the pyramid
	glPopMatrix();





	glPushMatrix();
	glTranslatef(0.0f, 1.0f, -20.0f);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	gluQuadricTexture(quad, 1);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glRotatef(rotat, 0.0f, 0.0f, 1.0f);
	//quad		quad
	//radius 	Specifies the radius of the sphere.
	//slices 	Specifies the number of subdivisions around the z axis(similar to lines of longitude).
	//stacks	Specifies the number of subdivisions along the z axis(similar to lines of latitude).
	gluSphere(quad, 2, 20, 20);
	glPopMatrix();


	// Draw a billiard ball
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, -20.0f);
	glBindTexture(GL_TEXTURE_2D, _textureId1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(rotat, 0.0f, 1.0f, 0.0f);
	glTranslatef(0, 1, 5);
	glScalef(0.3, 0.3, 0.3);
	gluQuadricTexture(quad2, 1);
	gluSphere(quad2, 0.5, 20, 20);
	glPopMatrix();
	glutSwapBuffers();

}

void update(int value)

{
	rotat += 0.3;
	if (rotat>360.f)
		rotat -= 360;

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);

}
void idleFunc(void)
{
	rotat += 0.3;
	glutPostRedisplay();
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Giza Pyramids");
	initRendering();
	glutIdleFunc(idleFunc);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;

}
