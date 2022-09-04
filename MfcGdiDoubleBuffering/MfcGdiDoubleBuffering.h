#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"

class CMfcGdiDoubleBufferingApp : public CWinApp
{
public:
	CMfcGdiDoubleBufferingApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CMfcGdiDoubleBufferingApp theApp;
