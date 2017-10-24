#ifndef LAB_Modeling_H
#define LAB_Modeling_H


//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 100.0;
const float worldHeight = 100.0; 

int NoOfPts=0;
int displayMode = 0;
Point3 base[3];
Mesh triPrism;

// global values for camera
GLdouble eyex=0.0, eyey=0.0, eyez=50.0;
GLdouble lookx=0.0, looky=0.0, lookz=0.0;

#endif