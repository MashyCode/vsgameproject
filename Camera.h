#pragma once

#include "3dObject.h"

class CCamera : public C3dObject
{
public:
	CCamera(void);
	CCamera(float x_,float y_,float z_);
	~CCamera(void);
	void Update(float dt);

	bool m_bClampToTerrain;
	float m_fClampOffset;

	void SetSpeed(float speed_){m_fSpeed=speed_;}

private:

	float m_fSpeed; //forward motion
	float m_fRotateYaw;
};
