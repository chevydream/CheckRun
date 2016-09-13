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

	//��������ģʽʵ��,��ֹ�����ظ�����
 	HANDLE m_hMutex = CreateMutex(NULL, FALSE, "uwinArmour");// ���������
 	if (GetLastError() == ERROR_ALREADY_EXISTS)
 	{
 		AfxMessageBox("��⵽�Ѿ�����һ�����������������У��벻Ҫ��δ�!");
 		CloseHandle(m_hMutex);	// ������л������������ͷž������λ������
 		m_hMutex = NULL;		// �����˳� ����
 		return FALSE; 
 	}
	
	CCheckRunDlg dlg;

	//��ȡ�����ļ������û�������ļ���������
	dlg.GetProcessPath();
	if(dlg.ReadConfig(0) == 0)			//�������ļ�ʧ��
	{
		MessageBox(NULL, "�������ļ���ʧ�����򱣻�����δ��������", "����", MB_OK);
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
