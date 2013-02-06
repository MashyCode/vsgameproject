// input.cpp: implementation of the Cinput class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Input.h"

#include <windows.h>
#include <OBJBASE.H>


extern HWND  g_hWnd;
extern HINSTANCE hInst;

LPDIRECTINPUT lpdi; //pointer to direct input object

LPDIRECTINPUTDEVICE lpdikey; //the keyboard device

//storage for keyboard state
UCHAR keystate[256];
UCHAR oldkeystate[256];
bool keydown[256];


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInput::CInput()
{


if (DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&lpdi, NULL)) //DirectInput8Create(hInst, DIRECTINPUT_VERSION, &lpdi, NULL)!=DI_OK)
    {
    // DirectInput not available; take appropriate action
    } 




//create keyboard device
if(lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL)!=DI_OK)
	{
	//error
	}

//set cooperation level
if(lpdikey->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)!=DI_OK)
	{
	//error
	}

//set data format
if(lpdikey->SetDataFormat(&c_dfDIKeyboard)!=DI_OK)
	{
	//error
	}

//acquire the keyboard device
if(lpdikey->Acquire()!=DI_OK)
	{
	//error
	}



}

CInput::~CInput()
{
//unaquire keyboard
lpdikey->Unacquire();

lpdi->Release();
}

//this method refreshes the CInput class's data on which keys are currently down
//this data is stored in an array called keystate[ ]

void
CInput::GetInput()
{
//copy old keystate array
int i;
for (i=0;i<256;i++)
	{
	oldkeystate[i]=keystate[i];
	}


if (lpdikey->GetDeviceState(256,keystate)!=DI_OK)
	{
	//error
	}
//now check which keys are now down that weren't down last time

for (i=0;i<256;i++)
{
if ((keystate[i]>0)&&(oldkeystate[i]==0))
	{
	//key is now down and it wasn't before
	keydown[i]=1;
	}
else
	{
	keydown[i]=0;
	}
}
}


//use this method with DirectX character constants
//which are defined in dinput.h  such as DIK_SPACE
//relies on the GetInput( ) method being called first to
//update the data on which keys are currently down
//if this method doesn't seem to work then make sure you
//are calling GetInput( ) first!!!

bool 
CInput::GetIfKeyDown(int whichkey)
{
if ((whichkey>256)|(whichkey<0)) return 0;
return (bool)(keystate[whichkey] & 0x80);
}

//method returns 1 or 0 depending on whether
//specified key has just been pressed

bool
CInput::GetIfKeyDownEvent(int whichkey)
{
if ((whichkey>256)|(whichkey<0)) return 0;
return (bool)(keydown[whichkey]);

}

CInput * CInput::Instance()
{
	if (0==_instance)
	{_instance=new CInput();
	}
	return _instance;
}
CInput * CInput::_instance=0;