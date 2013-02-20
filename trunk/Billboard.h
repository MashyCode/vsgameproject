// Billboard.h: interface for the CBillboard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BILLBOARD_H__E50A9B81_AE1F_4396_B994_C920B4DA6392__INCLUDED_)
#define AFX_BILLBOARD_H__E50A9B81_AE1F_4396_B994_C920B4DA6392__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3dObject.h"

class CBillboard : public C3dObject  
{
public:
	CBillboard(float x_,float y_,float z_,float w_,float h_,float d_, int textureID_, bool bUseSpriteSheet_=false, int cols_=2,int rows_=2,int fps=0, bool additive_=false);
	virtual ~CBillboard();
	void Update(float dt_);
	void Render();
	
	void SetAnimFrame(int frame_); //display particular frame of animation

private:
	float m_fULeft;
	float m_fURight; //u coordinates for  left,  right
	float m_fVTop;
	float m_fVBottom; //v coordinates for top and bottom
	bool m_bClampToTerrain;
	float m_fClampOffset;
	int m_nCurrentFrame;
	int m_nFPS;
	double m_dTimeToAdvanceAnimation;

	bool bAdditiveBlending;	
	bool bUseSpriteSheet;
	bool bAnimateSpriteSheet;
	
	int m_nFrames; //number of frames in animation - may be less than rows * cols
	int m_nCols, m_nRows; //number of sprites in sheet
};

#endif // !defined(AFX_BILLBOARD_H__E50A9B81_AE1F_4396_B994_C920B4DA6392__INCLUDED_)
