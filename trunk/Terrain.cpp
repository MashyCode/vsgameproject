#include "stdafx.h"
#include "Terrain.h"
#include "Game.h"
#include <math.h>

extern CGame gGame;
extern bool gWireFrame;
extern bool gLighting;

//constructor - note how Terrain takes same initialization parameters as a 3dObject
CTerrain::CTerrain(float x_, float y_,float z_, float w_, float h_,float d_, int textureID_)
:C3dObject(x_,y_,z_,w_,h_,d_,textureID_)
{

//load bitmap
LoadBitmapFile("assets/heightfield256.bmp");
//resize data structures to suit image
m_iMapVerticesx=this->m_pImage_RGB->sizeX;
m_iMapVerticesz=this->m_pImage_RGB->sizeY;

char outputDebug[64];
sprintf(outputDebug,"\n***loading heightfield with size: %d * %d**\n",m_iMapVerticesx,m_iMapVerticesz);
OutputDebugString(outputDebug);

//m_bClampToTerrain=false;
bDisplayListCreated=0;
//resize data structures to match size of image loaded
m_vHeights.resize(m_iMapVerticesx*m_iMapVerticesz);
m_vNormals.resize(m_iMapVerticesx*m_iMapVerticesz);
//calculate how much u,v coordinates change by in each step
m_fTerrainStepWidth=1.0f/m_iMapVerticesx;
m_fTerrainStepHeight=1.0f/m_iMapVerticesz;

//ComputeVertexHeights();
ComputeNormals();
//DumpVertexData();
m_bClampToTerrain=false;
}

CTerrain::~CTerrain(void)
{
	UnloadBitmapFile();
}

//used to calculate height of each vertex based on data from heightmap greyscale image
//number of vertices in width= number of pixels width in image
void
CTerrain::ComputeVertexHeights()
{
float xfactor=1.0/(m_iMapVerticesx-1);
float zfactor=1.0/(m_iMapVerticesz-1);

for (int z=0;z<(m_iMapVerticesz-1);z++)
{
		for (int x=0;x<(m_iMapVerticesx-1);x++)
        {	
				char txt[64];

				int vertxindex=x;
				int vertzindex=z;				
				float xprop=xfactor*vertxindex;
				float zprop=zfactor*vertzindex;
				float y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				m_vHeights[vertxindex + m_iMapVerticesx * vertzindex]=y;

				vertxindex=x;
				vertzindex=z+1;				
				xprop=xfactor*vertxindex;
				zprop=zfactor*vertzindex;
				glTexCoord2f(xprop,zprop);
				y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				m_vHeights[vertxindex + m_iMapVerticesx * vertzindex]=y;	

				vertxindex=x+1;
				vertzindex=z;				
				xprop=xfactor*vertxindex;
				zprop=zfactor*vertzindex;
				y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				m_vHeights[vertxindex + m_iMapVerticesx * vertzindex]=y;


				vertxindex=x+1;
				vertzindex=z+1;				
				xprop=xfactor*vertxindex;
				zprop=zfactor*vertzindex;
				y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				m_vHeights[vertxindex + m_iMapVerticesx * vertzindex]=y;

			}
			
        }

}

//in openGL a displaylist is a more efficient way of rendering large sets of data
//it is a kind of retained mode where it remembers the geometry, rather than
//immediate mode where you have to specify the geometry each frame

void
CTerrain::CreateDisplayList()
{
m_iDisplayList= glGenLists(1);
glNewList(m_iDisplayList,GL_COMPILE);

float xfactor=1.0/(m_iMapVerticesx-1);
float zfactor=1.0/(m_iMapVerticesz-1);

float xTile=10; //how may times texture repeats in x
float zTile=10; //how many times texture repeats in z

for (int z=0;z<(m_iMapVerticesz-1);z++)
{
		for (int x=0;x<(m_iMapVerticesx-1);x++)
        {	
			glBegin(GL_TRIANGLES);
			{	
				

				int vertxindex=x;
				int vertzindex=z;				
				float xprop=xfactor*vertxindex;
				float zprop=zfactor*vertzindex;
				float y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				vec3 * norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
				glNormal3f(norm->x,norm->y,norm->z);
				glTexCoord2f(xprop*xTile,zprop*zTile);
				glVertex3f(-0.5+xprop,y,-0.5+zprop);		//v0	

				vertxindex=x;
				vertzindex=z+1;				
				xprop=xfactor*vertxindex;
				zprop=zfactor*vertzindex;
				norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
				glNormal3f(norm->x,norm->y,norm->z);
				glTexCoord2f(xprop*xTile,zprop*zTile);
				y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				glVertex3f(-0.5+xprop,y,-0.5+zprop);	//v1	

				vertxindex=x+1;
				vertzindex=z;				
				xprop=xfactor*vertxindex;
				zprop=zfactor*vertzindex;
				norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
				glNormal3f(norm->x,norm->y,norm->z);
				glTexCoord2f(xprop*xTile,zprop*zTile);
				y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				glVertex3f(-0.5+xprop,y,-0.5+zprop);     //v2
				
				
				vertxindex=x+1;
				vertzindex=z;				
				xprop=xfactor*vertxindex;
				zprop=zfactor*vertzindex;
				norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
				glNormal3f(norm->x,norm->y,norm->z);
				glTexCoord2f(xprop*xTile,zprop*zTile);
				y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				glVertex3f(-0.5+xprop,y,-0.5+zprop);    //v2	

				vertxindex=x;
				vertzindex=z+1;				
				xprop=xfactor*vertxindex;
				zprop=zfactor*vertzindex;
				norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
				glNormal3f(norm->x,norm->y,norm->z);
				glTexCoord2f(xprop*xTile,zprop*zTile);
				y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				glVertex3f(-0.5+xprop,y,-0.5+zprop);    //v1	

				vertxindex=x+1;
				vertzindex=z+1;				
				xprop=xfactor*vertxindex;
				zprop=zfactor*vertzindex;
				norm=m_vNormals[vertxindex+m_iMapVerticesx * vertzindex];
				glNormal3f(norm->x,norm->y,norm->z);
				glTexCoord2f(xprop*xTile,zprop*zTile);
				y=(m_pImage_RGB->data[(vertzindex*m_iMapVerticesz+vertxindex)*3])/255.0;
				glVertex3f(-0.5+xprop,y,-0.5+zprop);  //v3
			}
			glEnd();
        }
}

glEndList();

GLenum error=glGetError();
int x=1;


}


//overrides the regular Render method from the base class
void
CTerrain::Render()
{

	if (!bDisplayListCreated)
	{
		bDisplayListCreated=true;
		CreateDisplayList();
	}

glPushMatrix();

if (gWireFrame)
{
	//wireframe version
	glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE);
	
}
else
{
	
	glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL); //wireframe mode
}

//
glDisable(GL_CULL_FACE); //don't cull faces


if (gLighting)
{
	glEnable(GL_LIGHTING);
}
else
{
	glDisable(GL_LIGHTING);
}


glEnable(GL_TEXTURE_2D);
glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
glBindTexture(GL_TEXTURE_2D, m_iTextureID); //use the proper texture!

//material properties
GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat grey[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
glMaterialfv(GL_FRONT, GL_AMBIENT, grey);

glTranslatef(m_fX,m_fY,m_fZ);
glScalef(m_fW, m_fH, m_fD); 

glCallList(m_iDisplayList);


glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL ); //back to normal rendering mode
glEnable(GL_CULL_FACE); //don't cull faces

glPopMatrix();
return;
}

// LoadBitmapFile
// desc: Returns a pointer to the bitmap image of the bitmap specified
//       by filename. Also returns the bitmap header information.
//		 No support for 8-bit bitmaps.
void
CTerrain::LoadBitmapFile(char *filename)
{
	//AUX_RGBImageRec *
	m_pImage_RGB = auxDIBImageLoad( filename );

}


// frees memory used for bitmap file 
//------------------------------------------------

void
CTerrain::UnloadBitmapFile()
{
	if( m_pImage_RGB )
    {
        if( m_pImage_RGB->data )
		{
          free( m_pImage_RGB->data );
		}

        free( m_pImage_RGB );
    }
}

//function used in terrain following - input a 3d location in world coordinates
// and return the y height of the terrain at that point

float 
CTerrain::GetHeightAtPoint(float x_,float z_)
{
	//original terrain has been scaled and translated
	//so undo translation
	float x_relative=x_ - m_fX;
	float z_relative=z_ - m_fZ;
	//now undo scale
	x_relative/=m_fW;
	z_relative/=m_fD;

	//add 0.5 to convert range back to 0->1
	x_relative+=0.5;
	z_relative+=0.5;
	//calculate xmin,max and zmin max
	float xmin,xmax,zmin,zmax;

	if (x_relative<0.0 || x_relative>1.0) return 0;
	if (z_relative<0.0 || z_relative>1.0) return 0;

	//position of ith vertex in x direction
	//=xmin+i* m_fw/m_iMapVerticesx
	//z=zmin+ j* m_fd/m_iMapVerticesz
	int whichvertexx,whichvertexz;
	whichvertexx=(int)(x_relative*(m_iMapVerticesx-1));
	whichvertexz=(int)(z_relative*(m_iMapVerticesz-1));

	// compute the height field coordinates (Col0, Row0)
	// and (Col1, Row1) that identify the height field cell 
	// directly below the camera.
	int col0 = whichvertexx;
	int row0 = whichvertexz;
	int col1 = col0 + 1;
	int row1 = row0 + 1;

	// make sure that the cell coordinates don't fall
	// outside the height field.
	if (col1 > m_iMapVerticesx)
		col1 = 0;
	if (row1 > m_iMapVerticesz)
		row1 = 0;

	// get the four corner heights of the cell from the height field
	int h00 = m_pImage_RGB->data[3*(col0 +row0*m_iMapVerticesz)];
	int h01 = m_pImage_RGB->data[3*(col1 + row0*m_iMapVerticesz)];
	int h11 = m_pImage_RGB->data[3*(col1 + row1*m_iMapVerticesz)];
	int h10 = m_pImage_RGB->data[3*(col0 + row1*m_iMapVerticesz)];

	// calculate the position of the point relative to the cell.
	// note, that 0 <= tx, ty <= 1.
	float tx = (x_relative - float(col0)/m_iMapVerticesx)*64;
	float tz = (z_relative - float(row0)/m_iMapVerticesz)*64;

	// the next step is to perform a bilinear interpolation
	// to compute the height of the terrain directly below
	// the object.
	float txtz = tx * tz;

	float final_height = (float)h00 * (1.0f - tz - tx + txtz)
						+ (float)h01 * (tx - txtz)
						+ (float)h11 * txtz
						+ (float)h10 * (tz - txtz);

	
	
	 final_height*=m_fH/255.0;
	 return final_height;
}

//compute the normal of a face using the indices of its three vertices
vec3 *
CTerrain::ComputeCrossProduct(int x1,int z1,int x2,int z2,int x3,int z3) 
{

	float v1[3],v2[3];
		
	v1[0] = (x2-x1) * m_fTerrainStepWidth; 
	v1[1] = -m_vHeights[z1 * m_iMapVerticesx + x1] 
			+ m_vHeights[z2 * m_iMapVerticesx + x2];
	v1[2] = (z2-z1) * m_fTerrainStepHeight; 


	v2[0] = (x3-x1) * m_fTerrainStepWidth; 
	v2[1] = -m_vHeights[z1 * m_iMapVerticesx + x1] 
			+ m_vHeights[z3 * m_iMapVerticesx + x3];
	v2[2] = (z3-z1) * m_fTerrainStepHeight; 

	vec3 * pAuxNormal=new vec3();

	pAuxNormal->x = v1[1] * v2[2] - v1[2] * v2[1];
	pAuxNormal->y = v1[2] * v2[0] - v1[0] * v2[2];
	pAuxNormal->z = v1[0] * v2[1] - v1[1] * v2[0];

	return(pAuxNormal);
}


//function analyzes each vertex in terrain
//looks at adjacent triangles, determines the normal for each adjacent triangle
//then calculates the average normal vector of all the triangles that meet at the vertex
void
CTerrain::ComputeNormals()
{
float xfactor=1.0/(m_iMapVerticesx-1);
float zfactor=1.0/(m_iMapVerticesz-1);

for (int z=0;z<(m_iMapVerticesz);z++)
{
		for (int x=0;x<(m_iMapVerticesx);x++)
        {	
			vec3 * norm1=new vec3();
			vec3 * norm2=new vec3();
			
			//for the four corners
			if (x == 0 && z == 0) {
				norm1 = ComputeCrossProduct(0,0, 0,1, 1,0);	
				NormalizeVector(norm1);				
			}
			else if (x == m_iMapVerticesx-1 && z == m_iMapVerticesz-1) {
				norm1 = ComputeCrossProduct(x,z, x,z-1, x-1,z);	
				NormalizeVector(norm1);				
			}
			else if (x == 0 && z == m_iMapVerticesz-1) {
				norm1 = ComputeCrossProduct(x,z, x+1,z,x,z-1 );	
				NormalizeVector(norm1);				
			}
			else if (x == m_iMapVerticesx-1 && z == 0) {
				norm1 = ComputeCrossProduct(x,z, x-1,z, x,z+1);	
				NormalizeVector(norm1);				
			}


			//for the edges
			/* normals for the borders -> calc average of two triangles */
			else if (z == 0) {
				norm1 = ComputeCrossProduct(x,0, x-1,0, x,1);
				NormalizeVector(norm1);
				
				norm2 = ComputeCrossProduct(x,0,x,1,x+1,0);
				NormalizeVector(norm2);
				AddVector(norm1,norm2);
				NormalizeVector(norm1);
			}
			else if (x == 0) {
				norm1 = ComputeCrossProduct(0,z,1,z, 0,z-1 );
				NormalizeVector(norm1);
				
				norm2 = ComputeCrossProduct(0,z,0,z+1,1,z);
				NormalizeVector(norm2);
				AddVector(norm1,norm2);
				NormalizeVector(norm1);
			}
			else if (x == m_iMapVerticesx-1) {
				norm1 = ComputeCrossProduct(x,z, x,z-1, x-1,z);
				NormalizeVector(norm1);
				
				norm2 = ComputeCrossProduct(x,z,x-1,z,x,z+1);
				NormalizeVector(norm2);
				AddVector(norm1,norm2);
				NormalizeVector(norm1);
			}
			else if (z == m_iMapVerticesz-1) {
				norm1 = ComputeCrossProduct(x,z, x+1,z, x,z-1);
				NormalizeVector(norm1);
				
				norm2 = ComputeCrossProduct(x,z,x,z-1,x-1,z);
				NormalizeVector(norm2);
				AddVector(norm1,norm2);
				NormalizeVector(norm1);
			}

			//for inner vertices, compute
			else 
			{
			norm1 = ComputeCrossProduct(x,z, x-1,z, x-1,z+1);
			NormalizeVector(norm1);
				
			norm2 = ComputeCrossProduct(x,z, x-1,z+1, x,z+1);
			NormalizeVector(norm2);
			AddVector(norm1,norm2);
				
			norm2 = ComputeCrossProduct(x,z, x,z+1, x+1,z+1);
			NormalizeVector(norm2);
			AddVector(norm1,norm2);
				
			norm2 = ComputeCrossProduct(x,z, x+1,z+1, x+1,z);
			NormalizeVector(norm2);
			AddVector(norm1,norm2);
				
			norm2 = ComputeCrossProduct(x,z, x+1,z, x+1,z-1);
			NormalizeVector(norm2);
			AddVector(norm1,norm2);
				
			norm2 = ComputeCrossProduct(x,z, x+1,z-1, x,z-1);
			NormalizeVector(norm2);
			AddVector(norm1,norm2);
				
			norm2 = ComputeCrossProduct(x,z, x,z-1, x-1,z-1);
			NormalizeVector(norm2);
			AddVector(norm1,norm2);
				
			norm2 = ComputeCrossProduct(x,z, x-1,z-1, x-1,z);
			NormalizeVector(norm2);
			AddVector(norm1,norm2);
			NormalizeVector(norm1);
			}
			
			int index=x+m_iMapVerticesx * z;
			m_vNormals[index]=norm1;
		}
}
}

//helper function that normalizes a 3d vector
//probably should have been in a seperate Vector3 class
void 
CTerrain::NormalizeVector(vec3 *v) {

	double d;
	
	d = sqrt((v->x*v->x) + (v->y*v->y) + (v->z*v->z));

	v->x /= d;
	v->y /= d;
	v->z /= d;
}

//helper function that adds two 3d vectors
//helper function that normalizes a 3d vector
//probably should have been in a seperate Vector3 class
void
CTerrain::AddVector(vec3 *a, vec3 *b) {

	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

//function for debugging purposes
//prints out coordinates of vertices in terrain
void
CTerrain::DumpVertexData()
{
	int x=0;
	int z=0;
	//for (std::vector<float>::iterator it = m_vHeights.begin(); it!=m_vHeights.end(); ++it) {
		for (int i=0;i<m_vHeights.size();i++)
		{
	
		float value=m_vHeights[i];
		vec3 * normal=m_vNormals[i];
		char txt[64];
		sprintf(txt,"(%d,%d) y=%2.2f, normal =(%2.2f,%2.2f,%2.2f)\n",x,z,value,normal->x,normal->y,normal->z);
		OutputDebugString(txt);

		x++;
		if (x>=m_iMapVerticesx)
		{
			x=0;
			z++;
		}
	
}
}