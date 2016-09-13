// checkRun.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "checkRun.h"
#include "checkRunDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE hMutex;
/////////////////////////////////////////////////////////////////////////////
// CCheckRunApp

BEGIN_MESSAGE_MAP(CCheckRunApp, CWinApp)
	//{{AFX_MSG_MAP(CCheckRunApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckRunApp construction

CCheckRunApp::CCheckRunApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCheckRunApp object

CCheckRunApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCheckRunApp initialization

BOOL CCheckRunApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//创建混杂模式实例,防止程序被重复运行
 	HANDLE m_hMutex = CreateMutex(NULL, FALSE, "uwinArmour");// 检查错误代码
 	if (GetLastError() == ERROR_ALREADY_EXISTS)
 	{
 		AfxMessageBox("检测到已经有另一个进程正在启动运行，请不要多次打开!");
 		CloseHandle(m_hMutex);	// 如果已有互斥量存在则释放句柄并复位互斥量
 		m_hMutex = NULL;		// 程序退出 　　
 		return FALSE; 
 	}
	
	CCheckRunDlg dlg;

	//读取配置文件，如果没有配置文件，则不启动
	dlg.GetProcessPath();
	if(dlg.ReadConfig(0) == 0)			//读配置文件失败
	{
		MessageBox(NULL, "因配置文件丢失，程序保护机制未能启动！", "警告", MB_OK);
		return FALSE;
	}
	
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
