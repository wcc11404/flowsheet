
// flowsheet.h : flowsheet Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CflowsheetApp:
// �йش����ʵ�֣������ flowsheet.cpp
//

class CflowsheetApp : public CWinAppEx
{
public:
	CflowsheetApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CflowsheetApp theApp;
