
// HIDUSB.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHIDUSBApp: 
// �йش����ʵ�֣������ HIDUSB.cpp
//

class CHIDUSBApp : public CWinApp
{
public:
	CHIDUSBApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHIDUSBApp theApp;