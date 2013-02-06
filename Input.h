// input.h: interface for the Cinput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUT_H__9F947E83_2A3B_4B63_8675_83B41506943E__INCLUDED_)
#define AFX_INPUT_H__9F947E83_2A3B_4B63_8675_83B41506943E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


class CInput  
{
private:
	static CInput * _instance;
protected:
	CInput();
public:
	static CInput * Instance();
	virtual ~CInput();
	void GetInput();
	bool GetIfKeyDown(int whichkey); //true as long as key still down
	bool GetIfKeyDownEvent(int whichkey); //occurs only when key first pressed

};

#endif // !defined(AFX_INPUT_H__9F947E83_2A3B_4B63_8675_83B41506943E__INCLUDED_)
