// FullScreenShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "checkrun.h"
#include "FullScreenShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullScreenShowDlg dialog


CFullScreenShowDlg::CFullScreenShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFullScreenShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFullScreenShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFullScreenShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFullScreenShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFullScreenShowDlg, CDialog)
	//{{AFX_MSG_MAP(CFullScreenShowDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFullScreenShowDlg message handlers


void CFullScreenShowDlg::FullScreenShow(BOOL flag)
{	
	LONG style = ::GetWindowLong(this->m_hWnd,GWL_STYLE);

	if(flag != 0)//全屏显示
	{
		style &= ~(WS_DLGFRAME | WS_THICKFRAME);
		SetWindowLong(this->m_hWnd,GWL_STYLE, style);
		this->ShowWindow(SW_SHOWMAXIMIZED);
		
		CRect rect;
		this->GetWindowRect(&rect);
		::SetWindowPos(this->m_hWnd,HWND_TOPMOST,
			rect.left-1, rect.top+1, rect.Width()+2, rect.Height()+2,
			SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}
	else
	{
		style |= WS_DLGFRAME | WS_THICKFRAME;
		SetWindowLong(this->m_hWnd, GWL_STYLE, style);
		this->ShowWindow(SW_NORMAL);
	}	
}


BOOL CFullScreenShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FullScreenShow(1);
		
	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CFullScreenShowDlg::OnUpdateTransparent(int iTransparent)
{
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	if(hInst)
	{
		typedef BOOL (WINAPI *SLWA)(HWND,COLORREF,BYTE,DWORD);
		SLWA pFun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		pFun = (SLWA)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if(pFun)
		{
			pFun(m_hWnd,0,iTransparent,2);
		}
		FreeLibrary(hInst); 
	}
}

//屏蔽回车和ESC键，防止按回车和ESC键时窗口退出
BOOL CFullScreenShowDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == 13 || pMsg->wParam == 27)
			return false;
	}
	return CDialog::PreTranslateMessage(pMsg);
}