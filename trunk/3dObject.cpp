#include "StdAfx.h"
#include "Input.h"


#include "3dObject.h"


C3dObject::C3dObject(void)
{
	m_fX=0.0f;
	m_fY=0.0f;
	m_fW=1.0f;
	m_fH=1.0f;
	m_fR=m_fG=m_fB=m_fA=1.0;
	
	m_fYaw=0;
	m_fPitch=0;
	m_fRoll=0;

}

C3dObject::C3dObject(float x_, float y_, float z_,float w_, float h_, float d_, int textureID_)
{
	
	m_fX=x_;
	m_fY=y_;
	m_fZ=z_;
	m_fW=w_;
	m_fH=h_;
	m_fD=d_;
	m_fR=m_fG=m_fB=m_fA=1.0;
	m_iTextureID=textureID_;
	
	m_fYaw=0;
	m_fPitch=0;
	m_fRoll=0;
	
}

C3dObject::~C3dObject(void)
{
}

void
C3dObject::Render()
{
	
	glPushMatrix();

	glShadeModel(GL_SMOOTH);		// use smooth shading
	
	glEnable(GL_DEPTH_TEST);
	glTranslatef(m_fX,m_fY,m_fZ);		// move to proper position
	glRotatef(m_fYaw,0.0f,1.0f,0.0f);
	glScalef(m_fW,m_fH,m_fD);

	glEnable(GL_CULL_FACE);	// do not calculate inside of polys
	
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING); //switch on dynamic lighting
	glDisable(GL_BLEND);

	if (m_iTextureID)
	{
		//use texture
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, m_iTextureID); 
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
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

	// Display a quad size 1 by 1, centred at origin
	glBegin(GL_POLYGON);
				glNormal3f(0.0f, 1.0f, 0.0f);	// top face
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(0.5f, 0.0f);
				glVertex3f(0.5f, 0.5f, -0.5f);
				glTexCoord2f(0.5f, 0.5f);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-0.5f, 0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(0.0f, 0.0f, 1.0f);	// front face
				glTexCoord2f(0.5f, 0.5f);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-0.5f, 0.5f, 0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, 0.5f);
				glTexCoord2f(0.5f, 0.0f);
				glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(1.0f, 0.0f, 0.0f);	// right face
				glTexCoord2f(0.5f, 1.0f);
				glVertex3f(0.5f, 0.5f, 0.5f);	
				glTexCoord2f(0.5f, 0.5f);
				glVertex3f(0.5f, -0.5f, 0.5f);
				glTexCoord2f(1.0f, 0.5f);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(0.5f, 0.5f, -0.5f);
			glEnd();
			glBegin(GL_POLYGON);
				glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-0.5f, 0.5f, 0.5f);	
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.0f);
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
				glTexCoord2f(0.5f, 0.0f);
				glVertex3f(0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(-0.5f, -0.5f, -0.5f);
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-0.5f, 0.5f, -0.5f);
				glTexCoord2f(0.5f, 0.5);
				glVertex3f(0.5f, 0.5f, -0.5f);	
			glEnd();

		glPopMatrix();
}

void
C3dObject::Update(float dt_)
{
}



void
C3dObject::SetPosition(float x_,float y_,float z_)
{
m_fX=x_;
m_fY=y_;
m_fZ=z_;
}

void
C3dObject::IncrementYaw(float dyaw_)
{
	m_fYaw+=dyaw_;
		if (m_fYaw > 360)
			{
				m_fYaw=0.0;
			}
		if (m_fYaw <0)
			{
				m_fYaw=360.0;
			}

}

void
C3dObject::IncrementPitch(float dpitch_)
{
m_fPitch+=dpitch_;
if (m_fPitch > 360)
	{
	m_fPitch=0.0;
	}
if (m_fPitch <0)
	{
	m_fPitch=360.0;
	}
}