#pragma once

#define MAXX 7
#define MINX -7
#define MAXY 5
#define MINY -5

class CSprite  
{
public:
	float m_fX;	//the position of the centre of the sprite
	float m_fY;
	float m_fW;	//width of the sprite in arbitrary units
	float m_fH;	//height of the sprite in arbitrary units
	int m_iTextureID; //which of the preloaded textures to use

	float m_fR;	//red component between 0 and 1
	float m_fG;	//green component between 0 and 1
	float m_fB;	//blue component between 0 and 1
	float m_fA;	//alpha value 0-1
	float m_fSpeed;
	bool bTaggedForDeletion;

public:
	CSprite();
	CSprite(float x_, float y_, float w_, float h_, int textureID_); 
//This new constructor is added to the Csprite.h header file.

	virtual ~CSprite();
	virtual void render();
	virtual void update(float dt_);
	bool bIsCollidingWith( CSprite * othersprite_);
}; 

