#if !defined( AFX_GEN_FIDO_H__520459A6_1253_11D5_99FA_AAAAD4F6AE39__INCLUDED_ )
#define AFX_GEN_FIDO_H__520459A6_1253_11D5_99FA_AAAAD4F6AE39__INCLUDED_

//----------------------------------------------------------------------------------------------

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//----------------------------------------------------------------------------------------------

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif // __AFXWIN_H__

//----------------------------------------------------------------------------------------------

#include "resource.h"
#include "Gen.h"

//----------------------------------------------------------------------------------------------

typedef struct
{
    INT   nCfgVer;
    BOOL  bActive;
    BOOL  bCutStr;
    BOOL  bPaused;
    BOOL  bStopped;
    BOOL  bToDOS;
    INT   nCutSymbs;
    TCHAR szError[257];
    TCHAR szFile[MAX_PATH + 1];
    TCHAR szNoWamp[257];
    TCHAR szPaused[257];
    TCHAR szPlaying[257];
    TCHAR szStopped[257];
    TCHAR szTpl[257];

    BOOL  bAddDots;

} GENFIDOCFG;

//----------------------------------------------------------------------------------------------

#define V20CFG 0x20
#define CFGVER 0x21

//----------------------------------------------------------------------------------------------

class CGen_FidoApp : public CWinApp
{
public:
	CGen_FidoApp();

//----------------------------------------------------------------------------------------------

    //{{AFX_VIRTUAL(CGen_FidoApp)
	//}}AFX_VIRTUAL

//----------------------------------------------------------------------------------------------

	//{{AFX_MSG(CGen_FidoApp)
	//}}AFX_MSG

//----------------------------------------------------------------------------------------------

	DECLARE_MESSAGE_MAP()

}; // class CGen_FidoApp

//----------------------------------------------------------------------------------------------

//{{AFX_INSERT_LOCATION}}

//----------------------------------------------------------------------------------------------

#endif // !defined( AFX_GEN_FIDO_H__520459A6_1253_11D5_99FA_AAAAD4F6AE39__INCLUDED_ )
