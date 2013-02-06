#pragma once

#include "3dObject.h"

class CLight : public C3dObject 
{
public:
	CLight(float x_, float y_, float z_);
	~CLight(void);
	void Update(float dt_);
	void Render();

private:

};
