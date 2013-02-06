#include "stdafx.h"
#include "SkyBox.h"

CSkyBox::CSkyBox(float x_, float y_,float z_, float w_, float h_,float d_, int textureID_):C3dObject(x_,y_,z_,w_,h_,d_,textureID_)
{
}

CSkyBox::~CSkyBox(void)
{
}

void
CSkyBox::Render()
{
	
	glPushMatrix();


	glShadeModel(GL_SMOOTH);		// use smooth shading
	glEnable(GL_DEPTH_TEST);
	glTranslatef(m_fX,m_fY,m_fZ);		// move to proper position
	glScalef(m_fW,m_fH,m_fD);

	glEnable(GL_CULL_FACE);	// do not calculate inside of poly's
	
	//skybox needs to be 'inside out'
	glFrontFace(GL_CW);
	//no lighting for skybox
	glDisable(GL_LIGHTING);



	if (m_iTextureID)
	{
	//use texture
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_iTextureID); 
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	 // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_EXT_CLAMP_TO_EDGE );

	
	}
	else
	{
	//zero for texture ID means don't use texture
	glDisable(GL_TEXTURE_2D);
	}
	
	//material properties
	GLfloat white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat grey[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_AMBIENT, grey);

	glEnable(GL_NORMALIZE);

	float pointA[]={0.0f,1.0f};
	float pointB[]={0.5,1.0};
	float pointC[]={1.0,1.0};
	float pointD[]={0.0f,0.66666f};
	float pointE[]={0.5,0.66666};
	float pointF[]={1.0,0.66666};
	float pointG[]={0.0f,0.33333f};
	float pointH[]={0.5,0.33333};
	float pointI[]={1.0,0.33333};
	float pointJ[]={0.0,0.0};
	float pointK[]={0.5,0.0};
	float pointL[]={1.0,0.0};

	// Display a quad size 1 by 1, centred at origin
	glBegin(GL_POLYGON);
				glNormal3f(0.0f, 1.0f, 0.0f);	// top face
				glTexCoord2f(pointA[0],pointA[1]);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(pointB[0],pointB[1]);
				glVertex3f(0.5f, 0.5f, -0.5f);
				glTexCoord2f(pointE[0],pointE[1]);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(pointD[0],pointD[1]);
				glVertex3f(-0.5f, 0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, 0.0f, 1.0f);	// front face
				glTexCoord2f(pointH[0],pointH[1]);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(pointI[0],pointI[1]);
				glVertex3f(-0.5f, 0.5f, 0.5f);
				glTexCoord2f(pointL[0],pointL[1]);
				glVertex3f(-0.5f, -0.5f, 0.5f);
				glTexCoord2f(pointK[0],pointK[1]);
				glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(1.0f, 0.0f, 0.0f);	// right face
				glTexCoord2f(pointH[0],pointH[1]);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(pointK[0],pointK[1]);
				glVertex3f(0.5f, -0.5f, 0.5f);
				glTexCoord2f(pointJ[0],pointJ[1]);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(pointG[0],pointG[1]);
				glVertex3f(0.5f, 0.5f, -0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
				glTexCoord2f(pointD[0],pointD[1]);
				glVertex3f(-0.5f, 0.5f, 0.5f);	
				glTexCoord2f(pointE[0],pointE[1]);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(pointH[0],pointH[1]);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(pointG[0],pointG[1]);
				glVertex3f(-0.5f, -0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, -1.0f, 0.0f);	// bottom face
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, 0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(0.5f, -0.5f, 0.5f);	
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, 0.0f, -1.0f);	// back face
				glTexCoord2f(pointI[0],pointI[1]);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(pointH[0],pointH[1]);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(pointE[0],pointE[1]);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(pointF[0],pointF[1]);
				glVertex3f(0.5f, 0.5f, -0.5f);	
			glEnd();

		glPopMatrix();
}