#pragma once
#include "3dObject.h"

#define MAX3dObjectS 150

class C3dObject;
class CLight;
class CCamera;
class CTerrain;

class CGame
{
public:
	CGame(void);
	~CGame(void);
	void DoFrame();
	CCamera * GetCamera();
	CTerrain * GetTerrain();
		
	void HandleMouseMove(float xrel_,float yrel_);

private:
	int	m_i3dObjectsLoaded;
	C3dObject * m_p3dObjects[MAX3dObjectS];

	CCamera * m_pCamera;
	CTerrain * m_pTerrain;
};
