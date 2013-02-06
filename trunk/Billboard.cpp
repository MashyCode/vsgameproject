// Billboard.cpp: implementation of the CBillboard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Billboard.h"
#include "gl.h"
//#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include "math.h"
#include "Timer.h"

//#include "BoundingSphere.h"
extern CGame gGame;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBillboard::CBillboard(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_, bool bUseSpriteSheet_, int cols_, int rows_, int fps_, bool additive_)
:C3dObject(x_,y_,z_,w_,h_,d_,textureID_)
{

bUseSpriteSheet=bUseSpriteSheet_;
m_nFPS=fps_;

m_nCols=cols_; //default setting
m_nRows=rows_;
m_nFrames=m_nRows*m_nCols;
m_dTimeToAdvanceAnimation=CTimer::Instance()->GetTime();
bAdditiveBlending=additive_;

if (bUseSpriteSheet)
	{
		SetAnimFrame(0);
	}
	else
	{
		m_fULeft=0.01;
		m_fURight=0.99f;
		m_fVTop=0.99f;
		m_fVBottom=0.01f;
	}


}

CBillboard::~CBillboard()
{

}

void
CBillboard::Render()
{

	glPushMatrix();
	glFrontFace(GL_CCW);
	glTranslatef(m_fX,m_fY,m_fZ);

	//yaw or heading is rotation about y axis
	glRotatef(m_fYaw,0.0f,1.0f,0.0f);
	glScalef(m_fW,m_fH,m_fD);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_iTextureID);
	glEnable(GL_DEPTH_TEST);

	//we won't use lighting for the billboards
	glEnable (GL_BLEND);
	glDisable (GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, m_iTextureID);

	if (bAdditiveBlending)
	{
		glBlendFunc( GL_SRC_ALPHA, GL_ONE);
	}
	else
	{
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
	

		glBegin(GL_POLYGON);
			glNormal3f(0.0f, 0.0f, 1.0f);	// a single face
			glTexCoord2f(m_fURight, m_fVTop);
			glVertex3f(0.5f, 0.5f, 0.0f);	
			glTexCoord2f(m_fULeft, m_fVTop);
			glVertex3f(-0.5f, 0.5f, 0.0f);
			glTexCoord2f(m_fULeft, m_fVBottom);
			glVertex3f(-0.5f, -0.5f, 0.0f);
			glTexCoord2f(m_fURight, m_fVBottom);
			glVertex3f(0.5f, -0.5f, 0.0f);
		glEnd();
		
	glPopMatrix();

}

void
CBillboard::Update(float dt_)
{
	//rotate to face camera
	//get camera pos
	
	float camx=gGame.GetCamera()->Getx();
	float camz=gGame.GetCamera()->Getz();

	float dx=camx-this->m_fX;
	float dz=camz-this->m_fZ;

	double thetaradians=atan2(dx,dz);
	double thetadegrees=180*thetaradians/3.142;
	this->SetYaw(thetadegrees);

	if (m_nFPS)
	{
		if (CTimer::Instance()->GetTime() > m_dTimeToAdvanceAnimation)
		{
		//it is time to advance animation
		m_nCurrentFrame++;
		SetAnimFrame(m_nCurrentFrame);
		//calc time for next change
		m_dTimeToAdvanceAnimation=CTimer::Instance()->GetTime() + 1.0f/(float)m_nFPS;
		}

	}
}


void
CBillboard::SetAnimFrame(int frame_)
{
m_nCurrentFrame=frame_;
if (m_nCurrentFrame> (m_nFrames-1)) m_nCurrentFrame=0;
//calc row
int row = m_nCurrentFrame/m_nCols;
int col = m_nCurrentFrame % m_nCols;

float rowWidth=1.0f/(float)m_nCols;
float colHeight=1.0f/(float)m_nRows;

m_fULeft=row * rowWidth + 0.01;
m_fURight=(row +1)* rowWidth -0.01;
m_fVTop= (col+1) * colHeight -0.01;
m_fVBottom= col * colHeight + 0.01;
}