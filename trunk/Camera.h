#pragma once

#include "3dObject.h"
#include "Game.h"

class CCamera : public C3dObject
{
public:
	CCamera(void);
	CCamera(float x_,float y_,float z_);
	~CCamera(void);
	void Update(float dt);

	void SetSpeed(float speed_){m_fSpeed=speed_;}

private:

	float m_fSpeed; //forward motion
	float m_fRotateYaw;
};
