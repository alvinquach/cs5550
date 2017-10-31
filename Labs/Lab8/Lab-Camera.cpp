//Lab: Camera Control

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
		cam.slide(0,0,0.2);
		break;
	case GLUT_KEY_PAGE_DOWN:
		// slide camera backward
		std::cout << "Camera zoom-out" << std::endl;
		cam.slide(0,0,-0.2);
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
		// complete pitch function in camera.cpp and invoke cam.pitch() function
		break; 
	case 'P':    
		std::cout << "Camera pitch down" << std::endl;
		// complete pitch function in camera.cpp and invoke cam.pitch() function
		break; 
	case 'y':    
		std::cout << "Camera yaw left" << std::endl;
		// complete yaw function in camera.cpp and invoke cam.yaw() function
		break; 
	case 'Y':    
		std::cout << "Camera yaw right" << std::endl;
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
	glClear(GL_COLOR_BUFFER_BIT);
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
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireTeapot(1.0); // draw the teapot
	glutSwapBuffers();	
} 
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab - Manipulate a camera around a teapot"); // open the screen window

	// register callback functions
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);	
	glutDisplayFunc(myDisplay);

	myInit();

	glutMainLoop();

	return( 0 );
}