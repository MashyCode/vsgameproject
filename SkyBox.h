#pragma once
#include "3dobject.h"

#ifndef GL_EXT_texture_edge_clamp 
#define GL_EXT_CLAMP_TO_EDGE   0x812F
#endif

class CSkyBox :
	public C3dObject
{
public:
	CSkyBox(float x=0.0f, float y=0.0f,float z=0.0f, float w=10.0f, float h=10.0f,float d=10.0f, int textureID=1);
	~CSkyBox(void);
	void Render();
};
