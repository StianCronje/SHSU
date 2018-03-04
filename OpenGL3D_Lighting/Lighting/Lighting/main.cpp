#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <SOIL.h>
#include <FreeImage.h>

using namespace std;

int width, height;
unsigned char* image;
const int font = (int)GLUT_BITMAP_9_BY_15;

GLuint _textureId, _textureId1, _carTexture, _backgroundTexture; //The id of the texture
GLUquadric *quad;
GLUquadric *quad2;
GLUquadric *quad3;
GLfloat rotat = 0.0;
float trans = 0.0f;



GLuint loadtextures(const char* filename)
{
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	int format = (FI_RGBA_RED == 0) ? GL_RGB : GL_BGR;
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	printf("The width and height of the image %s are (%d, %d) respectively \n", filename, width, height);

	return textureId;
}

void print(float x, float y, int z, const char *string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);
	//get the length of the string to display
	int len = (int)strlen(string);
	printf("print: %s - len: %d\n", string, len);

	glDisable(GL_TEXTURE_2D);
	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	glEnable(GL_TEXTURE_2D);
};


void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

float diffuse_position[] = { -1.0f, 1.0f, 1.0f, 1.0f };
GLfloat spec_position[] = { 1.0, 1.0, 1.0, 0.0 };

GLfloat diffuseLight[] = { 0.0f, 1.0f, 0.0, 1.0f };
GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
/* Initialize OpenGL Graphics */
void initGL()
{
	//Texture
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	quad = gluNewQuadric();
	quad2 = gluNewQuadric();
	quad3 = gluNewQuadric();
	_textureId = loadtextures("earth_day.jpg");
	_textureId1 = loadtextures("moon.jpg");
	_carTexture = loadtextures("tesla.png");
	_backgroundTexture = loadtextures("stars.jpg");

	//specular lighting
	GLfloat mat_shininess[] = { 50.0 };

	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//ambient Light
	GLfloat global_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);


	//Diffuse light the  main light	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, diffuse_position);

	glEnable(GL_DEPTH_TEST);
}




void handleResize(int w, int h) {

	printf("Window sized to %d x %d\n", w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);

}

void drawScene()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.5f, -1.0f, -6.0f);  // Move left and into the screen
										//Earth
	glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		gluQuadricTexture(quad, 1);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glRotatef(rotat, 0.0f, 0.0f, 1.0f);
		glScalef(0.5f, 0.5f, 0.5f);
		gluSphere(quad, 2, 20, 20);
	glPopMatrix();

	//Moon

	glPushMatrix();
		glRotatef(rotat, 0.0f, 1.0f, 0.0f);
		glTranslatef(1, 1, 2);
		glScalef(0.15, 0.15, 0.15);
		glBindTexture(GL_TEXTURE_2D, _textureId1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		gluQuadricTexture(quad2, 1);
		glScalef(0.2f, 0.2f, 0.2f);
		gluSphere(quad2, 2, 20, 20);
		glPopMatrix();

		glPushMatrix();
		//place the moon light
		glRotatef(rotat, 0.0f, 1.0f, 0.0f);
		glTranslatef(1, 0, 2);
		glLightfv(GL_LIGHT0, GL_POSITION, spec_position);
	glPopMatrix();

	// car
	glPushMatrix();
		glTranslatef(1.1f + trans, 1 + (trans * 0.3f), 0);
		glRotatef(20, 0.0f, 0.0f, 1.0f);
		glScalef(0.2f, 0.06f, 0.2f);
		glBindTexture(GL_TEXTURE_2D, _carTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 0);
			glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2d(1, 0);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glTexCoord2d(1, 1);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2d(0, 1);
			glVertex3f(1.0f, 0.0f, 0.0f);
		glEnd();
	glPopMatrix();

	// stars
	glPushMatrix();
		glTranslatef(1.5, 1, -6);
		glScalef(5, 5, 1);
		glBindTexture(GL_TEXTURE_2D, _backgroundTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 0);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2d(0, 1);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glTexCoord2d(1, 1);
			glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2d(1, 0);
			glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		print(2.8, 3.2, 0, "Christiaan Cronje");
	glPopMatrix();


	glutSwapBuffers();

}

void keypress(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'e':
		glEnable(GL_LIGHTING);
		break;
	case 'd':
		glDisable(GL_LIGHTING);
		break;
	case '1':
		glEnable(GL_LIGHT0);
		break;
	case '2':
		glEnable(GL_LIGHT1);
		break;
	case '0':
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		break;

	}

	glutPostRedisplay();
}

void idleFunc(void)
{
	rotat += 0.3;
	trans += 0.002f;
	glutPostRedisplay();
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(800, 800);
	glutCreateWindow("Tesla in Space");
	initGL();
	glutIdleFunc(idleFunc);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keypress);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;

}
