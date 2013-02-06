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
	m_fSpeed=0;
}

CCamera::CCamera(float x_, float y_,float z_):C3dObject(x_,y_,z_)
{
	m_fSpeed=0;
}

CCamera::~CCamera(void)
{
}

void
CCamera::Update(float dt_)
{


	//here is an example of how to check for input
	if (CInput::Instance()->GetIfKeyDown(DIK_A))
	{
	//does something->you need to edit this!!
	}

	//calculate new lookat based on current Yaw,pitch roll

	float cosYaw,sinYaw,sinPitch;
	cosYaw=(float)cos(DEG2RAD(m_fYaw));
	sinYaw=(float)sin(DEG2RAD(m_fYaw));
	sinPitch=(float)sin(DEG2RAD(m_fPitch));

	//update position based on speed
	//depends on current yaw angle

	m_fX+=sinYaw*m_fSpeed*dt_;
	m_fZ+=-cosYaw*m_fSpeed*dt_;

	//update lookat based on yaw and pitch
	float lookAtx=m_fX+sinYaw;
	float lookAty=m_fY+sinPitch;
	float lookAtz=m_fZ-cosYaw;

	gluLookAt(m_fX,m_fY,m_fZ,lookAtx,lookAty,lookAtz,0,1,0);
}

