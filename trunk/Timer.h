// Timer.h: interface for the CTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMER_H__C6029AAD_5261_4A99_96FB_6E97037A6E6A__INCLUDED_)
#define AFX_TIMER_H__C6029AAD_5261_4A99_96FB_6E97037A6E6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTimer  
{
public:
	CTimer();
	virtual ~CTimer();
	static CTimer * Instance();
	double Getdt();
	static void Destroy();
	double GetTime();
private:
	static CTimer * _timer;
	double _timeLastAsk;
	double _timeNow;

};

#endif // !defined(AFX_TIMER_H__C6029AAD_5261_4A99_96FB_6E97037A6E6A__INCLUDED_)
