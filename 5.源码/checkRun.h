// checkRun.h : main header file for the CHECKRUN application
//

#if !defined(AFX_CHECKRUN_H__AB50C42D_F8A1_45E3_B781_B982146D77F0__INCLUDED_)
#define AFX_CHECKRUN_H__AB50C42D_F8A1_45E3_B781_B982146D77F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCheckRunApp:
// See checkRun.cpp for the implementation of this class
//

class CCheckRunApp : public CWinApp
{
public:
	CCheckRunApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckRunApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCheckRunApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKRUN_H__AB50C42D_F8A1_45E3_B781_B982146D77F0__INCLUDED_)
