#if !defined(AFX_FULLSCREENSHOWDLG_H__4DA2BD35_B677_444F_8C50_F9516B5C761B__INCLUDED_)
#define AFX_FULLSCREENSHOWDLG_H__4DA2BD35_B677_444F_8C50_F9516B5C761B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FullScreenShowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFullScreenShowDlg dialog

class CFullScreenShowDlg : public CDialog
{
// Construction
public:
	CFullScreenShowDlg(CWnd* pParent = NULL);   // standard constructor

	void OnUpdateTransparent(int iTransparent);
	void FullScreenShow(BOOL flag);

// Dialog Data
	//{{AFX_DATA(CFullScreenShowDlg)
	enum { IDD = IDD_FULLSCREENSHOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullScreenShowDlg)
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFullScreenShowDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLSCREENSHOWDLG_H__4DA2BD35_B677_444F_8C50_F9516B5C761B__INCLUDED_)
