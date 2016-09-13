// FloatWnd.cpp : implementation file
//

#include "stdafx.h"
#include "checkRunDlg.h"
#include "FloatWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd dialog


CFloatWnd::CFloatWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CFloatWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFloatWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFloatWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFloatWnd)
	DDX_Control(pDX, IDC_SHOWINFO, m_STA_ShowInfo);
	DDX_Control(pDX, IDC_LOGO, m_Logo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFloatWnd, CDialog)
	//{{AFX_MSG_MAP(CFloatWnd)	
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONUP()
	ON_WM_NCLBUTTONDBLCLK()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)//快捷键消息映射手动加入
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd message handlers

extern double m_ImageSize;
extern int 	m_FontSize;
extern int	m_FontWidth;


BOOL CFloatWnd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CBitmap m_Bitmap;
	HBITMAP hBitmap = m_Logo.GetBitmap();
	ASSERT(hBitmap);

	m_Bitmap.Attach(hBitmap);
	BITMAP bmp;
	m_Bitmap.GetBitmap(&bmp);

	int nX = (int)(bmp.bmWidth/m_ImageSize);
	int nY = (int)(bmp.bmHeight/m_ImageSize);

	MoveWindow(0,0,nX+m_FontWidth,nY);
	m_Logo.MoveWindow(0,0,nX,nY);
	m_STA_ShowInfo.MoveWindow(nX, 0, m_FontWidth, nY);

	CenterWindow();
	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

	m_Bitmap.Detach();
	
	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	

	RegisterHotKey(GetSafeHwnd(),1002,MOD_ALT,'1');//Alt+1键


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CFloatWnd::OnNcHitTest(CPoint pt)
{
	LRESULT nHitTest = CDialog::OnNcHitTest(pt);

	if (nHitTest == HTCLIENT &&
				::GetAsyncKeyState(MK_LBUTTON) < 0) // 如果鼠标左键按下，GetAsyncKeyState函数的返回值小于0
	{
		nHitTest = HTCAPTION;
	}

	return nHitTest;
}


void CFloatWnd::OnOK()
{
	// TODO: Add extra cleanup here

	//OnOK();
}

void CFloatWnd::OnCancel() 
{
	// TODO: Add extra cleanup here

	//	CDialog::OnCancel();
}

void CFloatWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonUp(nFlags, point);
}

void CFloatWnd::OnUpdateTransparent(int iTransparent)
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

void CFloatWnd::OnNcLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	//CWnd *pParent = GetParent();
	//ASSERT(pParent);
	
	//if(!pParent->IsWindowVisible())
	//	pParent->ShowWindow(SW_SHOW);

	//pParent->SetForegroundWindow();

	CDialog::OnNcLButtonDblClk(nFlags, point);
}

//屏蔽回车和ESC键，防止按回车和ESC键时窗口退出
BOOL CFloatWnd::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == 13 || pMsg->wParam == 27)
			return false;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//响应快捷键的消息映射
LRESULT CFloatWnd::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	if (wParam==1002)//Alt+1键
	{
		exit(0);
	}

	return 0;
}

//退出程序
void CFloatWnd::OnClose() 
{
	UnregisterHotKey(GetSafeHwnd(),1002);//注销Alt+1键

	CDialog::OnClose();
}