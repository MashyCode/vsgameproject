#include "StdAfx.h"

#include <gl.h>
#include <glut.h>
#include <glaux.h>
#include "Sprite.h"


CSprite::CSprite( )
{
	m_fX=0.0f;
	m_fY=0.0f;
	m_fW=1.0f;
	m_fH=1.0f;
	m_fR=m_fG=m_fB=m_fA=1.0;
	m_iTextureID=0;
	m_fSpeed=0;
	bTaggedForDeletion=false;
	char message[]="**** Entering Sprite constructor ***\n";
	OutputDebugString(message);

}

CSprite::CSprite(float x_, float y_, float w_, float h_, int textureID_)
{
	
	m_fX=x_;
	m_fY=y_;
	m_fW=w_;
	m_fH=h_;
	m_fR=m_fG=m_fB=m_fA=1.0;
	m_iTextureID=textureID_;
	m_fSpeed=0;
	bTaggedForDeletion=false;

	char message[]="**** Entering Sprite constructor ***\n";
	OutputDebugString(message);

}

CSprite::~CSprite(void)
{
	char message[]="**** Sprite destroyed ***\n";
	OutputDebugString(message);
}

void
CSprite::render()
{
	glLoadIdentity();

	glEnable(GL_BLEND);// Turn Blending On
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(m_fX,m_fY,0);		// move to proper position
	glScalef(m_fW,m_fH,1);
	glColor4f(m_fR,m_fG,m_fB,m_fA);		// set color

	if (m_iTextureID)
	{
		//use texture
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_iTextureID); 
	}
	else
	{
		//zero for texture ID means don't use texture
		glDisable(GL_TEXTURE_2D);
	}

// Display a quad size 1 by 1, centred at origin
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-0.5, 0.5);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-0.5, -0.5);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(0.5, -0.5);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(0.5, 0.5);
	glEnd();

}

void
CSprite::update(float dt)
{

}

bool 
CSprite::bIsCollidingWith( CSprite * othersprite_)
{
	if ((this->m_fX+0.5*this->m_fW)< (othersprite_-> m_fX-0.5*othersprite_->m_fW) )
	{
		//right edge of our sprite is to 
		//the left of the other sprite
		return 0;
	}
	else if ((this->m_fX-0.5*this->m_fW)> (othersprite_-> m_fX+0.5*othersprite_->m_fW) )
	{
		//left edge of our sprite is to 
		//the right of the other sprite
		return 0;
	}
	else if ((this->m_fY+0.5*this->m_fH)< (othersprite_-> m_fY-0.5*othersprite_->m_fH) )
	{
		//top edge of our sprite is to 
		//the bottom of the other sprite
		return 0;
	}
	else if ((this->m_fY-0.5*this->m_fH)>(othersprite_-> m_fY+0.5*othersprite_->m_fH) )
	{
		//bottom edge of our sprite is to 
		//above the other sprite
		return 0;
	}
	return 1;
}



