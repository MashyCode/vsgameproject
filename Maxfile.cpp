#include "StdAfx.h"
#include ".\Maxfile.h"
#include <gl\gl.h>
#include <fstream>
#include <math.h>
//#include "BoundingSphere.h"
#include "Game.h"
using namespace std;

//CMaxFile constructor loads geometry from file
CMaxFile::CMaxFile(char * filepath_,float x_,float y_, float z_,float scale_, int textureID_)
{
	

	//store arguments
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
	m_fW=m_fH=m_fD=scale_;
	m_iTextureID=textureID_;
	

	m_fYaw=0;
	m_fPitch=0;
	m_fRoll=0;

	float maxx,maxy,maxz,minx,miny,minz;
	maxx=maxy=maxz=minx=miny=minz=0;

//try to load data
   using namespace std;
   fstream file;

   // Open and close with a basic_filebuf
   file.open(filepath_,ios::in);
//read number of verts

   file>>m_iNumVerts;
	m_iNumVerts/=3; //convert number of positions to number of 3d coordinate sets

	//now resize data structure to make room
	vertlist.resize(m_iNumVerts);
   for (int i=0;i<m_iNumVerts;i++)
	{
		file>>(vertlist[i].x);
		file>>(vertlist[i].y);
		file>>(vertlist[i].z);
		//update max sizes for bounding sphere
		if ((vertlist[i].x)>maxx){maxx=(vertlist[i].x);}
		if ((vertlist[i].y)>maxy){maxy=(vertlist[i].y);}
		if ((vertlist[i].z)>maxz){maxz=(vertlist[i].z);}
		if ((vertlist[i].x)<minx){minx=(vertlist[i].x);}
		if ((vertlist[i].y)<miny){miny=(vertlist[i].y);}
		if ((vertlist[i].z)<minz){minz=(vertlist[i].z);}
	} 

   //setup bounding sphere
	float dx,dy,dz;
	dx=maxx-minx;
	dy=maxy-miny;
	dz=maxz-minz;


	//float radius=sqrt(0.25*dx*dx+0.25*dy*dy+0.25*dz*dz);
	//m_bSphere=new CBoundingSphere(m_fx+(minx+0.5*dx)*m_fw,m_fy+(miny+0.5*dy)*m_fw,m_fz+(minz+0.5*dz)*m_fw,radius*m_fw);

	//read number of normals

	file>>m_iNumNormals;
	m_iNumNormals/=3; //convert num positions into num 3d position coordinates
	
	//now resize data structure to make room
	normlist.resize(m_iNumNormals);
	
	for (int i=0;i<m_iNumNormals;i++)
	{
	file>>(normlist[i].x);
	file>>(normlist[i].y);
	file>>(normlist[i].z);
	} 

	//read number texture coordinates

	file>>m_iNumTexcoords;
	m_iNumTexcoords/=2; //convert num floats loaded to num (x,y) pairs

	//now resize data structure to make room
	texcoordlist.resize(m_iNumTexcoords);
	float dummy; //used to extract null information if texcoords are 3d

	for (int i=0;i<m_iNumTexcoords;i++)
	{
	file>>(texcoordlist[i].x);
	file>>(texcoordlist[i].y);
	//file>> dummy;
	} 

	//read number of polygons
	//each triangle consists of index for coordinate, normal, texcoord for each of three vertices
	file>>m_iNumTriangleData;
	//m_iNumTriangleData/=9; //convert num integers loaded to num triangle data sets

	//now resize data structure to make room
	trilist.resize(m_iNumTriangleData);

	for (int i=0;i<m_iNumTriangleData;i++)
	{
	file>>(trilist[i].pointindex[0]);
	file>>(trilist[i].normalindex[0]);
	file>>(trilist[i].texcoordindex[0]);
	
	file>>(trilist[i].pointindex[1]);
	file>>(trilist[i].normalindex[1]);
	file>>(trilist[i].texcoordindex[1]);
	
	file>>(trilist[i].pointindex[2]);
	file>>(trilist[i].normalindex[2]);
	file>>(trilist[i].texcoordindex[2]);
	} 
   file.close(); //.rdbuf( )->close( );

	//assume want to clamp to terrain
	//m_bClampToTerrain=1;
	//m_fTerrainHeightOffset=0.95;
	//ApplyClampToTerrain();
}

//destructor destroys all loaded sprites
CMaxFile::~CMaxFile(void)
{
	
}

//doframe method iterates through all sprites and 
//updates and renders them

void
CMaxFile::Render()
{

//this OpenGL code is just here as a placeholder
// we need to get rid of it and move it into our CSprite class
glPushMatrix();
glFrontFace(GL_CCW);
GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
glEnable (GL_LIGHTING);
//use texture
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, m_iTextureID); //use the texture which we loaded
glTranslatef(m_fX,m_fY,m_fZ);	


//pitch is rotation about x axis
glRotatef(m_fPitch,1.0f,0.0f,0.0f);
//yaw or heading is rotation about y axis
glRotatef(m_fYaw,0.0f,1.0f,0.0f);
//roll is rotation about z axis
glRotatef(m_fRoll,0.0f,0.0f,1.0f);

glScalef(m_fW,m_fH,m_fD);
glDisable (GL_BLEND);

glBegin(GL_TRIANGLES);
		int offset=0; //offset is relative to beginning of trilist
		for (int trianglenumber=0;trianglenumber<m_iNumTriangleData;trianglenumber++)
		{
			glTexCoord2f(texcoordlist[trilist[trianglenumber].texcoordindex[0]].x, texcoordlist[trilist[trianglenumber].texcoordindex[0]].y);
			glNormal3f(normlist[trilist[trianglenumber].normalindex[0]].x,normlist[trilist[trianglenumber].normalindex[0]].y,normlist[trilist[trianglenumber].normalindex[0]].z);
			glVertex3f(vertlist[trilist[trianglenumber].pointindex[0]].x,vertlist[trilist[trianglenumber].pointindex[0]].y,vertlist[trilist[trianglenumber].pointindex[0]].z);

			glTexCoord2f(texcoordlist[trilist[trianglenumber].texcoordindex[1]].x, texcoordlist[trilist[trianglenumber].texcoordindex[1]].y);
			glNormal3f(normlist[trilist[trianglenumber].normalindex[1]].x,normlist[trilist[trianglenumber].normalindex[1]].y,normlist[trilist[trianglenumber].normalindex[1]].z);
			glVertex3f(vertlist[trilist[trianglenumber].pointindex[1]].x,vertlist[trilist[trianglenumber].pointindex[1]].y,vertlist[trilist[trianglenumber].pointindex[1]].z);

			glTexCoord2f(texcoordlist[trilist[trianglenumber].texcoordindex[2]].x, texcoordlist[trilist[trianglenumber].texcoordindex[2]].y);
			glNormal3f(normlist[trilist[trianglenumber].normalindex[2]].x,normlist[trilist[trianglenumber].normalindex[2]].y,normlist[trilist[trianglenumber].normalindex[2]].z);
			glVertex3f(vertlist[trilist[trianglenumber].pointindex[2]].x,vertlist[trilist[trianglenumber].pointindex[2]].y,vertlist[trilist[trianglenumber].pointindex[2]].z);	
		}//end loop for each triangle
glEnd();




	glPopMatrix();
	
	//now render bounding sphere?
	//if (this->m_pGame->GetShowBoundingSpheres())
		//{
		//m_bSphere->Render();
		//}

}


