#include <windows.h>
#include <windows.h> 
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
float yAxisForHuman, yAxisForParashot, xAxisForPlane;
const float PI = 3.14159265;//pi = 3.14
GLfloat twicePi = 2.0 * PI;//2*pi
int objectsAppearenceFlag = 1;//that flag is for controlling the appearence of the objects
int planeState = 1;//state responsible for placing the plane(move it in the screen)
int humanState = 1;//state2 responsible for placing the human(move him in the screen)
int parashotState = 1;//state3 responsible for placing the parashot(move it in the screen)

void movePlane();//function that make the plane move 
void moveHuman();//function that make the man move 
void moveParashot();//function that make the parashot move
void InitGraphics(int argc, char *argv[]);

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations();

void OnDisplay();
//void OnKeyPress(unsigned char key, int x, int y);
void drawEllipsee(float minRad, float majRad, float xc, float yc, float size)//use that function for drawing the clouds , the man head and the parashot head
{
	int triangleNumber = 60; //# of triangles used to draw circle
	glBegin(GL_POLYGON);
	for (int i = 0; i <= triangleNumber; i++) {
		glVertex2f(
			xc + (minRad* cos(i *  size / triangleNumber)),
			yc + (majRad * sin(i * size / triangleNumber))
			);
	}
	glEnd();
}


void setCloudsPosition()//function for drawing the clouds in the sky
{
	glColor3f(0.129411764705882, 0.870588235294118, 0.854901960784314);//set clouds color

	//clouds' position
	drawEllipsee(20, 10, 80, 80, twicePi);
	drawEllipsee(20, 10, 60, 85, twicePi);
	drawEllipsee(30, 10, 0, 75, twicePi);
	drawEllipsee(15, 15, 10, 82, twicePi);
	drawEllipsee(10, 17, -9, 84, twicePi);
	drawEllipsee(20, 10, -80, 80, twicePi);
	drawEllipsee(22, 10, -65, 75, twicePi);
	drawEllipsee(13, 15, -75, 87, twicePi);
}

void drawParashot()
{
	if (objectsAppearenceFlag == 1)//parashot appear
	{
		glColor3f(0.356862745098039, 0.850980392156863, 0.552941176470588);
	}
	else//parashot disappear
	{
		glColor3f(1, 1, 1);
	}
	drawEllipsee(30, 40, 0, 177, PI);//head of the parashot 
	glLineWidth(5);//give the wires of parashot width = 5
	glBegin(GL_LINES);//draw these lines as GL_LINES
	
	//parashot's witres
	glVertex2f(-29, 177);//wire1
	glVertex2f(0, 127);

	glVertex2f(-23, 177);//wire2
	glVertex2f(0, 133);

	glVertex2f(29, 177);//wire3
	glVertex2f(0, 127);

	glVertex2f(23, 177);//wire4
	glVertex2f(0, 133);

	glEnd();
}

void drawHuman()//draw the man on the parashot
{
	if (objectsAppearenceFlag == 1 || objectsAppearenceFlag == 3)//which means the man is safe
	{

		glColor3f(0, 0, 0);
	}
	else if (objectsAppearenceFlag == 2)//if the plane hits the man
	{
		glColor3f(1, 1, 1);
	}
	drawEllipsee(9, 9, 0, 157, twicePi);//head of the man as ellipse
	glLineWidth(5);//gives the man body width = 5
	glBegin(GL_LINES);
	//man body
	glVertex2f(0, 149);
	glVertex2f(0, 122);
	glVertex2f(-1, 149);
	glVertex2f(-1, 122);
	glVertex2f(1, 149);
	glVertex2f(1, 122);

	glVertex2f(-1, 142);//left hand
	glVertex2f(-10, 127);
	glVertex2f(-1, 143);
	glVertex2f(-10, 128);

	glVertex2f(1, 142);//right hand
	glVertex2f(10, 127);
	glVertex2f(1, 143);
	glVertex2f(10, 128);

	glVertex2f(-1, 122);//left leg
	glVertex2f(-9, 102);
	glVertex2f(-1, 123);
	glVertex2f(-9, 103);

	glVertex2f(1, 122);//right leg
	glVertex2f(9, 102);
	glVertex2f(1, 123);
	glVertex2f(9, 103);

	glEnd();
}

void drawPlane()
{
	glColor3f(0.56078431372549, 0.647058823529412, 0.611764705882353);//plane color
	glBegin(GL_QUADS);
	glVertex2f(-90, 50);
	glVertex2f(-80, 35);
	glVertex2f(-55, 50);
	glVertex2f(-80, 65);
	glEnd();
}
void OnKeyPress(unsigned char key, int x, int y);//change the plane speed 

int main(int argc, char* argv[])
{
	yAxisForHuman = yAxisForParashot = xAxisForPlane = 0;
	InitGraphics(argc, argv);
	return 0;
}

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("animation");
	glutDisplayFunc(OnDisplay);
	glutIdleFunc(OnDisplay);

	glutKeyboardFunc(OnKeyPress);
	SetTransformations();

	glutMainLoop();//to make the shape contiue appear
}

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations() {
	//set up the logical coordinate system of the window: [-100, 100] x [-100, 100]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

void OnDisplay()
{

	// clear the transformation matrix
	glLoadIdentity();


	//set the background color to white
	glClearColor(1, 1, 1, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);

	//draw and move(translate)the parashot
	glPushMatrix();
	glTranslatef(0, yAxisForParashot, 0);
	moveParashot();//make parashot move in y axis
	drawParashot();//draw it
	glPopMatrix();

	//draw and move(translate)the man
	glPushMatrix();
	glTranslatef(0, yAxisForHuman, 0);//human in y axis
	moveHuman();// make him move in y axis
	glColor3f(1, 0, 0);
	drawHuman();//draw him
	glPopMatrix();

	//draw and move(translate)the plane
	glPushMatrix();
	glTranslatef(xAxisForPlane, 0, 0);//plane in x axis
	movePlane();//make plane move in x axis
	drawPlane();
	glPopMatrix();
	
	setCloudsPosition();//draw clouds


	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();

}



void movePlane()
{
	if (planeState == 1)//plane is in inital position
	{
		xAxisForPlane += 0.02;//move it in the x direction
	}

	if (xAxisForPlane > 155 && planeState == 1)//when the plane reach the second side of the screen
	{
		xAxisForPlane = 155;//stop it there
	}
}
void moveHuman()
{
	if (humanState == 1)//man is in inital position
	{
		yAxisForHuman -= 0.02;//move him down in the y direction
	}
	if (yAxisForHuman < -202 && humanState == 1)//when the man reach the second side of the screen
	{
		yAxisForHuman = -202;//stpo him there
		objectsAppearenceFlag = 3;
	}
	if (xAxisForPlane >= 50 && xAxisForPlane <= 110 && yAxisForHuman <= -50 && yAxisForHuman >= -110)//if the plane hit him
		objectsAppearenceFlag = 2;//make the parashot and the man disappear
}
void moveParashot()
{
	if (parashotState == 1)//parashot is in inital position
	{
		yAxisForParashot -= 0.02;//move it down in the y direction
	}
	if (yAxisForParashot < -200 && humanState == 1)//when the parashot reach the second side of the screen
	{
		yAxisForParashot = -200;//stop it there
	}
}

/**
Handles the special key press. This event is whenever
a special key is being pressed.
*/
void OnKeyPress(unsigned char key, int x, int y)
{
	if (key == 27)//if press (esc ) button
		exit(0);

	switch (key)
	{
	case 's'://in case press in s ==> speed up
	case 'S':
		xAxisForPlane += 2;//then move the pane more speed
		if (xAxisForPlane > 155)//if it reached the second side of the screen
			xAxisForPlane = 155;//then stop it there
		break;
	};
}
