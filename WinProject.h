
// WinProject.h: WinProject 응용 프로그램의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 주 기호입니다.


// CWinProjectApp:
// 이 클래스의 구현에 대해서는 WinProject.cpp을(를) 참조하세요.
//

class CWinProjectApp : public CWinAppEx
{
public:
	CWinProjectApp() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWinProjectApp theApp;
