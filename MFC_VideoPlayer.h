
// MFC_VideoPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_VideoPlayerApp: 
// �йش����ʵ�֣������ MFC_VideoPlayer.cpp
//

class CMFC_VideoPlayerApp : public CWinApp
{
public:
	CMFC_VideoPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_VideoPlayerApp theApp;