/* ******************************************************
 * Homework 2: OpenGL                                  *
 * CS 148 (Summer 2016), Stanford University           *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 ****************************************************** */

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = { 0,1,4,1 };
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 3; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {

	//1st teacup
	glPushMatrix(); //begin
	glTranslatef(1, 0, 0); //[position
	glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end
	//2nd pot
	glPushMatrix();
	glTranslatef(1, 0.5, 0);
	glRotatef(36, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	//3rd pot
	glPushMatrix();
	glTranslatef(0.5, 1, 0);
	glRotatef(72, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	//4th pot
	glPushMatrix();
	glTranslatef(-0.5, 1, 0);
	glRotatef(108, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	//5th pot
	glPushMatrix();
	glTranslatef(-1, 0.5, 0);
	glRotatef(144, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	//6th pot
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	//7th pot
	glPushMatrix();
	glTranslatef(-1, -0.5, 0);
	glRotatef(216, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	//8th
	glPushMatrix();
	glTranslatef(-0.5, -1, 0);
	glRotatef(252, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	//9th
	glPushMatrix();
	glTranslatef(0.5, -1, 0);
	glRotatef(288, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	//10th
	glPushMatrix();
	glTranslatef(1, -0.5, 0);
	glRotatef(324, 0, 0, 1);
	glutSolidTeapot(0.2);
	glPopMatrix();
	
	
}

void problem2() {
	//left to right in increasing order cube size 0.1-0.75
	//size=0.1
	glPushMatrix();
	glTranslatef(-1.1,0.05,0.05);
	glutSolidCube(0.1);
	glPopMatrix();

	//size=0.15
	glPushMatrix();
	glTranslatef(-1.05,0.075,0.0375);
	glutSolidCube(0.15);
	glPopMatrix();

	//size=0.2
	glPushMatrix();
	glTranslatef(-0.975,0.1,0.05);
	glutSolidCube(0.2);
	glPopMatrix();

	//size=0.25
	glPushMatrix();
	glTranslatef(-0.875,0.125,0.0625);
	glutSolidCube(0.25);
	glPopMatrix();

	//size=0.3
	glPushMatrix();
	glTranslatef(-0.75,0.15,0.075);
	glutSolidCube(0.3);
	glPopMatrix();


	//size=0.35
	glPushMatrix();
	glTranslatef(-0.6,0.175,0.0875);
	glutSolidCube(0.35);
	glPopMatrix();

	//size=0.4
	glPushMatrix();
	glTranslatef(-0.425,0.2,0.1);
	glutSolidCube(0.4);
	glPopMatrix();

	//size=0.45
	glPushMatrix();
	glTranslatef(-0.225,0.225,0.1125);
	glutSolidCube(0.45);
	glPopMatrix();

	//size=0.5
	glPushMatrix();
	glTranslatef(0.25,0.25,0.125);
	glutSolidCube(0.5);
	glPopMatrix();

	//size=0.55
	glPushMatrix();
	glTranslatef(0.525,0.275,0.1375);
	glutSolidCube(0.55);
	glPopMatrix();

	//size=0.6
	glPushMatrix();
	glTranslatef(0.825,0.3,0.15);
	glutSolidCube(0.6);
	glPopMatrix();

	//size=0.65
	glPushMatrix();
	glTranslatef(1.15,0.325,0.1625);
	glutSolidCube(0.65);
	glPopMatrix();

	//size=0.7
	glPushMatrix();
	glTranslatef(1.5,0.35,0.175);
	glutSolidCube(0.7);
	glPopMatrix();

	//size=0.75
	glPushMatrix();
	glTranslatef(1.875,0.375,0.1875);
	glutSolidCube(0.75);
	glPopMatrix();

	
	

}

void problem3() {



	//1st teacup
	glPushMatrix(); //begin
	glTranslatef(0, 1, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//2nd
	glPushMatrix(); //begin
	glTranslatef(-0.5, 0.5, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//3rd
	glPushMatrix(); //begin
	glTranslatef(0.5, 0.5, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//4th
	glPushMatrix(); //begin
	glTranslatef(-1, 0, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//5th
	glPushMatrix(); //begin
	glTranslatef(0, 0, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//6th
	glPushMatrix(); //begin
	glTranslatef(1.0, 0, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//7th
	glPushMatrix(); //begin
	glTranslatef(-1.5, -0.5, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//8th
	glPushMatrix(); //begin
	glTranslatef(-0.5, -0.5, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//9th teacup
	glPushMatrix(); //begin
	glTranslatef(0.5, -0.5, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//10th
	glPushMatrix(); //begin
	glTranslatef(1.5, -0.5, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//11
	glPushMatrix(); //begin
	glTranslatef(-2.0, -1.0, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//12
	glPushMatrix(); //begin
	glTranslatef(-1.0, -1.0, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//13th
	glPushMatrix(); //begin
	glTranslatef(0, -1.0, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//14th
	glPushMatrix(); //begin
	glTranslatef(1.0, -1.0, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//15th
	glPushMatrix(); //begin
	glTranslatef(2.0, -1.0, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//16th
	glPushMatrix(); //begin
	glTranslatef(-2.5, -1.5, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//17th teacup
	glPushMatrix(); //begin
	glTranslatef(-1.5, -1.5, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//18th
	glPushMatrix(); //begin
	glTranslatef(-0.5, -1.5, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//19th
	glPushMatrix(); //begin
	glTranslatef(0.5, -1.5, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//20th
	glPushMatrix(); //begin
	glTranslatef(1.5, -1.5, 0.5); //[position
	//glRotatef(0, 0, 0, 1);  //rotation in z-axis
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	//21st
	glPushMatrix(); //begin
	glTranslatef(2.5, -1.5, 0.5); //[position
	glutSolidTeapot(0.2);	//draws the teapot
	glPopMatrix();	//end

	
	
}

void problem4() {
	// TODO: Your code here!
}

void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, windowWidth, windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot, 0, 1, 0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1, (y - lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key - '0';
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}


//// C++ code to demonstrate star pattern 
//#include <iostream> 
//using namespace std;
//
//// Function to demonstrate printing pattern 
//void triangle(int n)
//{
//	// number of spaces 
//	int k = 2 * n - 2;
//
//	// outer loop to handle number of rows 
//	//  n in this case 
//	for (int i = 0; i < n; i++)
//	{
//		// inner loop to handle number spaces 
//		// values changing acc. to requirement 
//		for (int j = 0; j < k; j++)
//			cout << " ";
//
//		// decrementing k after each loop 
//		k = k - 1;
//
//		//  inner loop to handle number of columns 
//		//  values changing acc. to outer loop 
//		for (int j = 0; j <= i; j++)
//		{
//			// printing stars 
//			cout << "* ";
//		}
//
//		// ending line after each row 
//		cout << endl;
//	}
//}
//
//// Driver Function 
//int main()
//{
//	int n = 5;
//	triangle(n);
//	system("pause");
//	return 0;
//}