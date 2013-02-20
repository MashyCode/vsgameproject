#include "StdAfx.h"
#include ".\game.h"
#include <gl.h>
#include <glu.h>
#include "Light.h"
#include "Input.h"
#include "Timer.h"
#include "Camera.h"
#include "Billboard.h"
#include "SkyBox.h"
#include "Maxfile.h"
#include "Terrain.h"

//game constructor loads 3dObjects into array
CGame::CGame(void)
{
	m_i3dObjectsLoaded=0;
	//load 3dObjects
	//skybox first
	m_p3dObjects[m_i3dObjectsLoaded++]=new CSkyBox(0,0,0,50,50,50,10);
	


	//setup camera
	m_pCamera=new CCamera(0,1,6);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pCamera;



	//for (int j=0;j<10;j++)
	//{
	//	for(int i=0;i<10;i++)
	//	{
	//	m_p3dObjects[m_i3dObjectsLoaded++]=new C3dObject(i-5,0,j-5,1,0.1,1,2);
	//	}
	//}

	//Tree for loop, needs to be changed to random X position and random Z position
	for (int trees = 0; trees < 20; trees++)
	{
		m_p3dObjects[m_i3dObjectsLoaded++]=new CBillboard(0 + trees, trees * 0.5,rand() % 20 - trees,4,4,rand() % 20 - trees,14);
	}

	m_pTerrain=new CTerrain(0, 0, 0, 50, 3, 50, 17);
	m_p3dObjects[m_i3dObjectsLoaded++]=m_pTerrain;

	//setup the light
	m_p3dObjects[m_i3dObjectsLoaded++]=new CLight(6,0,3);


}

//destructor destroys all loaded 3dObjects
CGame::~CGame(void)
{
	for (int i=0;i<m_i3dObjectsLoaded;i++)
	{
		delete m_p3dObjects[i];
		m_p3dObjects[i]=0;
	}
}

//doframe method iterates through all 3dObjects and 
//updates and renders them

void
CGame::DoFrame()
{
	//this relates to the main game loop
	// get input
	// update all objects
	// render the scene

	//refresh input
	CInput::Instance()->GetInput();
	float dt=CTimer::Instance()->Getdt();

	//update all 3dObjects
	for (int i=0;i<m_i3dObjectsLoaded;i++)
	{
		m_p3dObjects[i]->Update(dt);
	}

	//render all 3dObjects
	for (int i=0;i<m_i3dObjectsLoaded;i++)
	{
		m_p3dObjects[i]->Render();
	}
	

	// Escape key, when pressed, exit with code 0
	if(CInput::Instance()->GetIfKeyDown(DIK_ESCAPE))
	{
		exit(0);
	}

	
}


CCamera * 
CGame::GetCamera()
{
	return m_pCamera;
}

CTerrain * 
CGame::GetTerrain()
{
	return m_pTerrain;
}

void
CGame::HandleMouseMove(float xrel_,float yrel_)
{
//yaw camera according to distance from centre
	//m_pCamera->IncrementYaw(25*(xrel_-0.5));

	//m_pCamera->IncrementPitch(-25*(yrel_-0.5));
}