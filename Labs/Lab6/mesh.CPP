#include <windows.h>
#include <gl/Gl.h>
#include <iostream>
#include "mesh.h"


// constructor
Mesh:: Mesh() 
{
	numVerts=0; 
	ready2draw=0;
	numFaces=0; 
	norm=NULL; 
	face=NULL; 	
}

// destructor
Mesh:: 	~Mesh() 
{								
	if(numVerts !=0) {
		delete[] pt;
		delete[] norm;
		delete[] face;
	} 
}

// use OpenGL to draw this mesh in solid object mode
void Mesh:: drawSolid() // use OpenGL to draw this mesh
{  
	if(ready2draw) {
		for(int f = 0; f < numFaces; f++) // draw each face
		{
			glColor3f(f/(float)10,f/(float)10,f/(float)10);
			glBegin(GL_POLYGON);
			  for(int v = 0; v < face[f].nVerts; v++) // for each one..
			  {
				  int in = face[f].vert[v].normIndex ; // index of this normal
				  int iv =  face[f].vert[v].vertIndex ; // index of this vertex
				  //glNormal3f(norm[in].x, norm[in].y, norm[in].z);
				  glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
			  }
			glEnd();
		}
	}
}


// use OpenGL to draw this mesh in wireframe mode
void Mesh:: drawWireframe() 
{  
	if(ready2draw) {
		for(int f = 0; f < numFaces; f++) // draw each face
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_LINE_LOOP);
			  for(int v = 0; v < face[f].nVerts; v++) // for each one..
			  {
				  int iv =  face[f].vert[v].vertIndex ; // index of this vertex
				  glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
			  }
			glEnd();
		}
	}
}


void Mesh:: initPrism(int N)
{
	numVerts = N*2;
	numNormals = N + 2;
	numFaces = N + 2;

	pt = new Point3[numVerts];
	norm = new Vector3[numNormals];
	face = new Face[numFaces];
} 


void Mesh:: createPrism(int N, Point3 *p, float length)
{
	// initialize the prism
	initPrism(N);

	// create the vertex list
	for (int i = 0; i < N; i++) {
		pt[2 * i].set(p->x, p->y, p->z);
		pt[2 * i + 1].set(p->x, p->y, p->z + 5.0);
		p++;
	}

	// create side faces
	for (int i = 0; i < N; i++) {
		face[i] = Face();
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
		face[i].vert[0].vertIndex = 2 * i;
		face[i].vert[1].vertIndex = 2 * i + 1;
		face[i].vert[2].vertIndex = i == N - 1 ? 0 : 2 * (i + 1);
		face[i].vert[3].vertIndex = i == N - 1 ? 1 : 2 * (i + 1) + 1;
	}

	// create the base and cap faces
	for (int i = 0; i < 2; i++) {
		face[N + i] = Face();
		face[N + i].nVerts = N;
		face[N + i].vert = new VertexID[N];
		for (int j = 0; j < N; i++) {
			face[N + i].vert[j].vertIndex = 2 * j + 1;
		}
	}

	// when all is done, ready2draw=1;
	ready2draw = 1;
}