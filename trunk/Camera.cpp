#include "stdafx.h"
#include "Camera.h"
#include <gl.h>
#include <glu.h>
#include <math.h>
#include <dinput.h>
#include "input.h"

#define DEG2RAD(x) 3.142*x/180

CCamera::CCamera(void)
{
	m_fSpeed=2;
	m_fRotateYaw = 0.5f;
}

CCamera::CCamera(float x_, float y_,float z_):C3dObject(x_,y_,z_)
{
	m_fSpeed=2;
	m_fRotateYaw = 0.5f;
}

CCamera::~CCamera(void)
{
}

void
CCamera::Update(float dt_)
{
	float cosYaw,sinYaw,sinPitch;
	cosYaw=(float)cos(DEG2RAD(m_fYaw));
	sinYaw=(float)sin(DEG2RAD(m_fYaw));
	sinPitch=(float)sin(DEG2RAD(m_fPitch));

	//update lookat based on yaw and pitch
	float lookAtx=m_fX+sinYaw;
	float lookAty=m_fY+sinPitch;
	float lookAtz=m_fZ-cosYaw;


	if (CInput::Instance()-> GetIfKeyDown(DIK_W))
	{	
		// Move fowards
		//m_fZ -= m_fSpeed *dt_;

		//m_fZ+=-cosYaw*m_fSpeed*dt_;

		m_fX+=sinYaw*m_fSpeed*dt_;
		m_fZ+=-cosYaw*m_fSpeed*dt_;
	}
	else if (CInput::Instance()-> GetIfKeyDown(DIK_S))
	{	
		// Move backwards
		//m_fZ += m_fSpeed*dt_;

		m_fX+=-sinYaw*m_fSpeed*dt_;
		m_fZ+=cosYaw*m_fSpeed*dt_;
	}

	
	else if (CInput::Instance()->GetIfKeyDown(DIK_A))
	{
		// strafe left
		//m_fX-= m_fSpeed * dt_;

		//Rotate left - TEST FOR 3RD-PERSON
		// Yaw = rotation on Y-Axis!
		//C3dObject::IncrementYaw(-m_fRotateYaw);

		m_fX -= cosYaw*0.05;
		m_fZ -= sinYaw*0.05;
	}

	
	else if (CInput::Instance()->GetIfKeyDown(DIK_D))
	{	
		// Strafe right
		//m_fX+= m_fSpeed* dt_;
		
		//Rotate right - TEST FOR 3RD-PERSON
		// Yaw = rotation on Y-Axis!
		//C3dObject::IncrementYaw(m_fRotateYaw);
		
		m_fX += cosYaw*0.05;
		m_fZ += sinYaw*0.05;
	}
	


	//calculate new lookat based on current Yaw,pitch roll



	//update position based on speed
	//depends on current yaw angle

	//m_fX+=sinYaw*m_fSpeed*dt_;
	//m_fZ+=-cosYaw*m_fSpeed*dt_;


	gluLookAt(m_fX,m_fY,m_fZ,lookAtx,lookAty,lookAtz,0,1,0);
}
