
// Delay_Composition_VHF.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDelay_Composition_VHFApp:
// �� Ŭ������ ������ ���ؼ��� Delay_Composition_VHF.cpp�� �����Ͻʽÿ�.
//

class CDelay_Composition_VHFApp : public CWinAppEx
{
public:
	CDelay_Composition_VHFApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CDelay_Composition_VHFApp theApp;