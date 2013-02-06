#include "stdafx.h"
#include "Light.h"
#include <gl.h>
#include <dinput.h>
#include "input.h"

CLight::CLight(float x_, float y_, float z_):C3dObject(x_,y_,z_)
{
}

CLight::~CLight(void)
{
}



void
CLight::Update(float dt_)
{
	if (CInput::Instance()->GetIfKeyDown(DIK_UP))
	{
	m_fY+=5*dt_;
	}

	if (CInput::Instance()->GetIfKeyDown(DIK_DOWN))
	{
	m_fY-=5*dt_;
	}

	if (CInput::Instance()->GetIfKeyDown(DIK_LEFT))
	{
	m_fX-=5*dt_;
	}

	if (CInput::Instance()->GetIfKeyDown(DIK_RIGHT))
	{
	m_fX+=5*dt_;
	}

	//setup light in OpenGL
	GLfloat  position[4];
	position[0]=m_fX;
	position[1]=m_fY;
	position[2]=m_fZ;
	position[3]=1;
	GLfloat color[4]={1,1,1,1};
	GLfloat ambient[4]={0.2,0.2,0.2,1};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHTING);
}

void
CLight::Render()
{
glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	
	glColor4f(1,1,1,1);
	glPointSize (10);
	glBegin(GL_POINTS);
		glVertex3f(m_fX,m_fY,m_fZ);
	glEnd();
glPopMatrix();
}