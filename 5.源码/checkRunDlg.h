// checkRunDlg.h : header file
//

#if !defined(AFX_CHECKRUNDLG_H__6FCF854B_C7ED_4D3D_8B3D_6ECCFDC7068E__INCLUDED_)
#define AFX_CHECKRUNDLG_H__6FCF854B_C7ED_4D3D_8B3D_6ECCFDC7068E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"		// main symbols
#include "FloatWnd.h"
#include "FullScreenShowDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckRunDlg dialog

class CCheckRunDlg : public CDialog
{
// Construction
public:
	CCheckRunDlg(CWnd* pParent = NULL);	// standard constructor

	char	m_ShowInfo[MAX_PATH];		//要显示的信息
	char	m_ObjectApp[MAX_PATH];		//要看程序的文件名（不能含路径）
	CTime	m_ShowTime;					//显示时间

	int		m_iTransparent;

	char	m_AppPath[MAX_PATH];		//工作路径	
	
	CFloatWnd *pFloatWnd;
	CFullScreenShowDlg *pFullDlg;

	//读配置文件，成功返回1，失败返回0
	int		ReadConfig(BOOL flag);

	void	GetProcessPath();

	void	DealOverTime();				//超时处理
	
// Dialog Data
	//{{AFX_DATA(CCheckRunDlg)
	enum { IDD = IDD_CHECKRUN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckRunDlg)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void AddIcon(HWND hWnd, HICON hIcon, UINT uCallbackMessage, char *title);
	void RemoveIcon();
	// Generated message map functions
	//{{AFX_MSG(CCheckRunDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKRUNDLG_H__6FCF854B_C7ED_4D3D_8B3D_6ECCFDC7068E__INCLUDED_)
