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

	for (int j=0;j<10;j++)
	{
		for(int i=0;i<10;i++)
		{
		m_p3dObjects[m_i3dObjectsLoaded++]=new C3dObject(i-5,0,j-5,1,0.1,1,2);
		}
	}


	


	//tree
	m_p3dObjects[m_i3dObjectsLoaded++]=new CBillboard(0,2,-5,4,4,1,14);

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

	
}


CCamera * 
CGame::GetCamera()
{
	return m_pCamera;
}

void
CGame::HandleMouseMove(float xrel_,float yrel_)
{
//yaw camera according to distance from centre
	//m_pCamera->IncrementYaw(25*(xrel_- 0.5));
	
	// look up and down
	m_pCamera->IncrementPitch(8*(0.5 - yrel_));

	// look left and right
	m_pCamera->IncrementYaw (-8*(0.5-xrel_ ));


}