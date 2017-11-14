//Lab: Camera Control
#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/gl.h>
#include <gl/glu.h>
#include "glut.h"
#include <iostream>

#include "Lab-Camera.h"

//<<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>>>
void myInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // background is black
	glColor3f(1.0f, 1.0f, 1.0f);    // drawing color is white

	// set the view volume shape ----
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();	
	gluPerspective(50.0f, (float)screenWidth/screenHeight, 0.5f, 200.0f);
	//---------------------------
	
	//make the initial camera
	cam.set(Point3(4, 4, 4), Point3(0, 0, 0), Vector3(0, 1, 0)); 
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	switch(theKey)
	{	
	case GLUT_KEY_LEFT:   
		std::cout << "Camera move left" << std::endl;
		cam.slide(-0.2,0,0); 
		break; 
	case GLUT_KEY_RIGHT: 
		std::cout << "Camera move right" << std::endl;
		cam.slide(0.2,0,0); 
		break;
	case GLUT_KEY_UP:  
		std::cout << "Camera move up" << std::endl;
		cam.slide(0,0.2,0); 
		break; 		
	case GLUT_KEY_DOWN: 
		std::cout << "Camera move down" << std::endl;
		cam.slide(0,-0.2,0); 
		break; 		
	case GLUT_KEY_PAGE_UP:
		// slide camera forward
		std::cout << "Camera zoom-in" << std::endl;
		cam.slide(0,0,-0.2);
		break;
	case GLUT_KEY_PAGE_DOWN:
		// slide camera backward
		std::cout << "Camera zoom-out" << std::endl;
		cam.slide(0,0,0.2);
		break;
	default:
		break;
	}	
	glutPostRedisplay(); // draw it again
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'a':
		lightAnimation = !lightAnimation;
		break;
	case 'r':  
		std::cout << "Camera roll counter clock-wise " << std::endl;
		cam.roll(1.0); 
		break; // roll the camera 
	case 'R': 
		std::cout << "Camera roll clock-wise" << std::endl;
		cam.roll(-1.0); 
		break; // roll the camera back	
	case 'p':    
		std::cout << "Camera pitch up" << std::endl;
		cam.pitch(1.0);
		// complete pitch function in camera.cpp and invoke cam.pitch() function
		break; 
	case 'P':    
		std::cout << "Camera pitch down" << std::endl;
		cam.pitch(-1.0);
		// complete pitch function in camera.cpp and invoke cam.pitch() function
		break; 
	case 'y':    
		std::cout << "Camera yaw left" << std::endl;
		cam.yaw(-1.0);
		// complete yaw function in camera.cpp and invoke cam.yaw() function
		break; 
	case 'Y':    
		std::cout << "Camera yaw right" << std::endl;
		cam.yaw(1.0);
		// complete yaw function in camera.cpp and invoke cam.yaw() function
		break; 
	default:
		break;
	}		
	glutPostRedisplay(); // draw it again
}


//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING); // Disable lighting for the axes
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0,0,0);
		glVertex3f(5,0,0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0,0,0);
		glVertex3f(0,5,0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0,0,0);
		glVertex3f(0,0,5);
	glEnd();
	glEnable(GL_LIGHTING);
	
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightIntensity);

	// Draw the gold teapot
	glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, goldShininess);
	glutSolidTeapot(1.0);

	// Draw the silver teapot
	glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmbient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, silverShininess);
	glPushMatrix();
	glTranslatef(0, 0, -3);
	glutSolidTeapot(1.0);
	glPopMatrix();

	glutSwapBuffers();	
}

void myIdle(void) {
	if (lightAnimation) {
		position[0] = 1.5f * cos(lightAngle * M_PI / 180);
		position[2] = 1.5f * sin(lightAngle * M_PI / 180);
		lightAngle++;
		if (lightAngle >= 360) {
			lightAngle -= 360;
		}
		glutPostRedisplay();
	}
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab - Manipulate a camera around a teapot"); // open the screen window

	glEnable(GL_DEPTH_TEST);

	// register callback functions
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);	
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);

	myInit();

	glutMainLoop();

	return( 0 );
}