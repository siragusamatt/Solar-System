#include <stdio.h>
#include <GL\freeglut.h>
#include <math.h>

char title[] = "Final Project";
float fraction = 0.1f;
float angle = 0.0;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float x = 0.0f, y = 0.0f, z = 5.0f;
float planetAngleR = 0.0;
float planetAngleB = 0.0;
float planetAngleG = 0.0;
int refreshMills = 15;

GLfloat xAngle = 0;
GLfloat yAngle = 0;
GLfloat zAngle = 0;

void initGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LESS);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e':
		exit(0);
		break;
	case 'r':
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
		x = 0;
		y = 0;
		z = 5.0f;
		lx = 0;
		ly = 0;
		lz = -1.0;
		break;
	default:
		break;
	}
}


void KeyboardSpecial(int key, int x, int y)	
{
	switch (key)
	{
	case GLUT_KEY_DOWN:	
			xAngle += -5;	
		break;
	case GLUT_KEY_UP:	
			xAngle += 5;	
		break;
		case GLUT_KEY_LEFT:	
			yAngle += -5;	
			break;
		case GLUT_KEY_RIGHT:
			yAngle += 5;	
			break;
		case GLUT_KEY_PAGE_UP:
				x += lx * 2;
				z += lz * 2;
				break;
			case GLUT_KEY_PAGE_DOWN:
				x -= lx * 2;
				z -= lz * 2;
				break;
		default:
			break;
	}
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity(); 
	GLfloat lightPos0[] = { 0.0f, 0.0f, 1.0f, 0.0f};
	GLfloat towards0[] = { -1.0f, -1.0f, 0.0f };
	float specLight0[4] = {5.5f, 5.5f, 5.5f, 1.0f };
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specLight0);
	glLightfv(GL_LIGHT1, GL_POSITION, specLight0);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, towards0);
	glShadeModel(GL_SMOOTH);

	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);

	glRotatef(xAngle, 1.0, 0.0, 0.0);	
	glRotatef(yAngle, 0.0, 1.0, 0.0);	
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	
	//Sun
	glTranslatef(0.0f, 0.0f, -15.0f);
	glScalef(0.25, 0.25, 0.25);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(10, 50, 50);
	
	//Red Planet
	glRotatef(planetAngleR, 0.0f, 50.0f, 1.0f);
	glTranslatef(50.0f, 0.0f, 0.0f);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(5, 50, 50);

	//Blue Planet
	glTranslatef(-50.0f, 0.0f, 0.0f);
	glRotatef(planetAngleB, 0.0f, 50.0f, -10.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidSphere(3, 50, 50);
	
	//Green Planet
	glTranslatef(-30.0f, 0.0f, 0.0f);
	glRotatef(planetAngleR, 0.0f, 50.0f, 5.0f);
	glTranslatef(20.0f, 0.0f, 0.0f);
	glColor3f(0.0, 1.0, 0.0);
	glutSolidSphere(2, 50, 50);
	
	planetAngleR += 0.05f;
	planetAngleB = planetAngleR - 0.12;
	planetAngleG = planetAngleR - 2.7;

	glEnd();

	glutSwapBuffers();
}

void timer(int value) 
{
	glutPostRedisplay();     
	glutTimerFunc(refreshMills, timer, 0); 
}


void reshape(GLsizei width, GLsizei height) {  
											   
	if (height == 0) height = 1;                
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);						
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();             
	gluPerspective(60.0f, aspect, 0.5f, 200.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(840, 680);   
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);
	glutTimerFunc(0, timer, 0);
	glutDisplayFunc(display);       
	glutIdleFunc(display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(KeyboardSpecial);
	glutReshapeFunc(reshape);
	initGL();        
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glutMainLoop();                 
	return 1;
}