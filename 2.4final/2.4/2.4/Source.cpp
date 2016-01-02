#include <glut.h> 
#include <math.h>
#include "algoritm.h"
elips myElips;

//Отображение  
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//my alg
	myElips.grid();
	if (myElips.x1 > 0) {
		myElips.draw();//draw standart elipse
		myElips.rasterization();//draw rasterized elipse
	}
	glFlush();
}

//Инициализация 
void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

void mouseclick(int button, int state, int x, int y)//mouse click func
{
	if (state == GLUT_DOWN) {
		myElips.x1 = x;
		myElips.X = x;
		myElips.Y = 500-y;
	}
	else myElips.x1 = -1;
}

void mouseMove(int x, int y)//mouse move func
{
	if (myElips.x1 >= 0) {
		myElips.set(x, 500-y);
		glutPostRedisplay();
	}
}

void start()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Elips rasterization");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseclick);
	glutMotionFunc(mouseMove);
	glutMainLoop();
}
void main() {
	start();
}