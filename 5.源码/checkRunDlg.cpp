// checkRunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "checkRun.h"
#include "checkRunDlg.h"
#include <imagehlp.h>
#include <TlHelp32.h>
#include "Psapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#define	WDT_FEED		(WM_USER + 1)	//ι����Ϣ
#define	WDT_CLOSE		(WM_USER + 2)	//�˳���Ϣ

double	m_ImageSize = 0;
int		m_FontSize = 0;
int		m_FontWidth = 0;

CString m_DeletePath;

int	m_IniChanged = 0;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckRunDlg dialog

CCheckRunDlg::CCheckRunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckRunDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckRunDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iTransparent = 255;

	m_ImageSize = 1;
	m_FontSize = 72;
	m_FontWidth = 500;

	pFloatWnd = NULL;
	pFullDlg = NULL;
}



void CCheckRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckRunDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckRunDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckRunDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCheckRunDlg::OnBnClickedOk)
END_MESSAGE_MAP()



DWORD   FindProcess(char   *strProcessName)   
{   
	DWORD     aProcesses[1024],   cbNeeded,   cbMNeeded;   
	HMODULE   hMods[1024];   
	HANDLE    hProcess;   
	char      szProcessName[MAX_PATH];   
    
	if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) return 0;

	for(int   i=0;   i<   (int)   (cbNeeded   /   sizeof(DWORD));   i++)   
	{         
		hProcess   =   OpenProcess(     PROCESS_QUERY_INFORMATION   |   PROCESS_VM_READ,   FALSE,   aProcesses[i]);   
		EnumProcessModules(hProcess,   hMods,   sizeof(hMods),   &cbMNeeded);   
		GetModuleFileNameEx(   hProcess,   hMods[0],   szProcessName,sizeof(szProcessName));   
		
		if(strstr(szProcessName,   strProcessName))   
		{   
			return(aProcesses[i]);   
		}   
	}   
    
	return   0;   
}

VOID   KillProcess(char   *strProcessName)   
{   
	//   When   the   all   operation   fail   this   function   terminate   the   "winlogon"   Process   for   force   exit   the   system.   
	HANDLE   hYourTargetProcess   =   OpenProcess(PROCESS_QUERY_INFORMATION   |       //   Required   by   Alpha   
		PROCESS_CREATE_THREAD           |       //   For   CreateRemoteThread   
		PROCESS_VM_OPERATION             |       //   For   VirtualAllocEx/VirtualFreeEx   
		PROCESS_TERMINATE | //   For   Kill   the   process   
		PROCESS_VM_WRITE,                           //   For   WriteProcessMemory   
		FALSE,   FindProcess(strProcessName));   
    
	if(hYourTargetProcess   ==   NULL)     
	{   

		return;   
	}   
    
	DWORD DD1 = GetLastError();
	BOOL iii = TerminateProcess(hYourTargetProcess,   0); 

	DWORD DD = GetLastError();
    
    
	return;   
}

// �õ���������Ŀ¼���ŵ�g_TheAppPath��
void	CCheckRunDlg::GetProcessPath()
{
    int  len = 0;
    int  index = 0;
    int  i;
	char AppPathName[MAX_PATH]; 

	GetModuleFileName(NULL,AppPathName,MAX_PATH); 
    len = strlen(AppPathName); 
    for(i=0; i<len; i++)
    {
        if(AppPathName[i] == '\\')
            index = i;
    }
	memset(m_AppPath,0,MAX_PATH);
    memcpy(m_AppPath, AppPathName, index);  
}


//�ݹ�ɾ��Ŀ¼�������ļ���������Ŀ¼
//DirName    ��������Ŀ¼��
//DirInList  ���б����ļ�ǰ��ʾ��Ŀ¼���硰test/img00009.jpg���е�test��
void DeleteAllFiles(CString	DirName, CString DirInList)
{
	CString  str, name, tmp;
	CFileFind find;
	BOOL have;

	//ԭΪ������JPG��Ϊ�����¼�Ŀ¼����Ϊ���������ļ� DRK 2006-4-26
	have = find.FindFile(DirName+"\\*");

	while(have)
	{
		have = find.FindNextFile();
		str = find.GetFilePath();
		name = find.GetFileName();

		if(find.IsDots())
			continue;

		if (find.IsDirectory())   //�����Ŀ¼��������Ŀ¼
		{
			if (DirInList.IsEmpty())
				DeleteAllFiles(DirName+"\\"+name, name);
			else
				DeleteAllFiles(DirName+"\\"+name, DirInList+"\\"+name);
		}
		else
		{
			DeleteFile(DirName+"\\"+name);
		}
	}	
}

/////////////////////////////////////////////////////////////////////////////
// CCheckRunDlg message handlers

BOOL CCheckRunDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	SetTimer(0, 1, NULL);

	//�����ػ�������������
	HANDLE	hFind;
	char	FileName[MAX_PATH];
	WIN32_FIND_DATA	data;
	sprintf(FileName, "%s\\%s", m_AppPath, m_ObjectApp);
	//�����ļ�FileName������������������û�����Լ��˳�
	hFind = ::FindFirstFile(FileName, &data);
	if(hFind != INVALID_HANDLE_VALUE)		//�У�����
	{
		ShellExecute(NULL, NULL, m_ObjectApp, NULL, m_AppPath, SW_SHOWNORMAL);
		FindClose(hFind);
	}

	pFloatWnd = new CFloatWnd;
	pFloatWnd->Create(IDD_FLOATWND,this);
	pFloatWnd->ShowWindow(SW_HIDE);
	pFloatWnd->OnUpdateTransparent(m_iTransparent);

	pFullDlg = new CFullScreenShowDlg;
	pFullDlg->Create(IDD_FULLSCREENSHOW,this);
	pFullDlg->ShowWindow(SW_HIDE);
	pFullDlg->OnUpdateTransparent(m_iTransparent);

	SetTimer(1, 2000, NULL);

	SetTimer(2, 300, NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCheckRunDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCheckRunDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCheckRunDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




void CCheckRunDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

//��ʱ������������س����Ѿ��ر��ˣ����Լ��˳�
void CCheckRunDlg::DealOverTime()
{
	CTime t = CTime::GetCurrentTime();

	//1 ��ȡ����
	ReadConfig(1);

	//2 �Ƿ񵯿�(��ʱ��������ļ����򿪹�)
	if(m_ShowTime < t || m_IniChanged != 0)
	{
		pFullDlg->ShowWindow(SW_SHOW);
		pFloatWnd->ShowWindow(SW_SHOW);

		//�����ļ����򿪹�
		if (m_IniChanged == 1)
		{
			m_IniChanged = 2;
			DeleteAllFiles(m_DeletePath, "");
		}
	}else{
		pFullDlg->ShowWindow(SW_HIDE); 
		pFloatWnd->ShowWindow(SW_HIDE); 
	}

	//3 ���ô��ڵ�����
	pFullDlg->OnUpdateTransparent(m_iTransparent);

	CFont font;  
	font.CreateFont(m_FontSize,0,0,0,700,0,0,0,  
    ANSI_CHARSET,OUT_DEFAULT_PRECIS,  
    CLIP_DEFAULT_PRECIS,  
    DEFAULT_QUALITY,  
    DEFAULT_PITCH|FF_DONTCARE,  
    "Times New Roman");  
	pFloatWnd->GetDlgItem(IDC_SHOWINFO)->SetFont(&font); 
	pFloatWnd->m_STA_ShowInfo.SetWindowText(m_ShowInfo);
	pFloatWnd->OnUpdateTransparent(m_iTransparent);


	//4 �˳�����
	HANDLE handle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 pce;
	pce.dwSize = sizeof(PROCESSENTRY32);
	
	DWORD dwPID;
	
	if( Process32First(handle, &pce) )
	{
		if( GetLastError() == ERROR_NO_MORE_FILES )
		{
			return;
		}
		else
		{
			dwPID = pce.th32ProcessID;
			
			if( _tcscmp(pce.szExeFile, m_ObjectApp) == 0 )
			{
				return;
			}//( _tcscmp(pce->szExeFile, m_ObjectApp) == 0 )
			
			//��������
			CString strProgramPath = "";
			while( Process32Next(handle,&pce) != FALSE )
			{
				dwPID = pce.th32ProcessID;	
				if( _tcscmp(pce.szExeFile, m_ObjectApp) == 0 )
				{
					//��ȡ���г������ȫ·��
					char szModuleFile[MAX_PATH] = "";
					HMODULE hModule = GetModuleHandle(m_ObjectApp);
					HANDLE hProcess = OpenProcess(PROCESS_VM_READ|PROCESS_QUERY_INFORMATION, FALSE, dwPID);  
					GetModuleFileNameEx(hProcess, hModule, szModuleFile, MAX_PATH);  
					strProgramPath = szModuleFile;
					CloseHandle(hProcess);
					
					return;
				}
			}//while(Process32Next(handle,pce) != FALSE)

			//�Լ��˳�
			if(strProgramPath.GetLength() <= 0)
			{
				::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
			}
		}
	}
	
	CloseHandle(handle);
	
	return;
}

void CCheckRunDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	switch(nIDEvent) 
	{
	case 0:						//Ϊ�����ش��ڶ����Ķ�ʱ��
		ShowWindow(SW_HIDE);    //���ش���
		KillTimer(0);
		break;
	case 1:						//����ȡ�������Ƿ񵯿��˳������Ƿ��˳��Ķ�ʱ��
		DealOverTime();
		break;
	case 2:						//ȫ�������ö�����
		//pFullDlg->FullScreenShow(1);
		//pFloatWnd->ShowWindow(SW_SHOWNA);
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}



//��Ϣ����
LRESULT CCheckRunDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) 
	{
	case WDT_FEED:			//ι����Ϣ

		break;

	case WDT_CLOSE:			//�˳���Ϣ

		::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
		break;

	}
	return CDialog::WindowProc(message, wParam, lParam);
}


//���λس���ESC������ֹ���س���ESC��ʱ�����˳�
BOOL CCheckRunDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == 13 || pMsg->wParam == 27)
			return false;
	}
	return CDialog::PreTranslateMessage(pMsg);
}



//�������ļ����ɹ�����1��ʧ�ܷ���0
int		CCheckRunDlg::ReadConfig(BOOL flag)
{
	int		ret;
	char	valBuf[MAX_PATH];
	char	FileName[MAX_PATH];
	
	//��ʼ��������Ϣ
	memset(valBuf,0,MAX_PATH);
	memset(FileName,0,MAX_PATH);
	
	//��֯�ļ�·��
	sprintf(FileName,"%s\\uwinArmour.ini",m_AppPath);
	
	//��ȡҪ��ʾ����Ϣ��
	ret = ::GetPrivateProfileString("CONFIG", "ShowInfo", NULL, valBuf, MAX_PATH, FileName);
	if(ret == 0)
		return 0;
	if (strcmp(m_ShowInfo, valBuf) != 0 && flag == TRUE) 
		m_IniChanged = 1;
	strcpy(m_ShowInfo, valBuf);
	

	//��ȡ�������͸���̶ȡ�
	ret = ::GetPrivateProfileString("CONFIG", "iTransparent", NULL, valBuf, MAX_PATH, FileName);
	if(ret == 0)
		return 0;
	if (m_iTransparent != atoi(valBuf) && flag == TRUE) 
		m_IniChanged = 1;
	m_iTransparent = atoi(valBuf);
	

	//��ȡҪ���ĳ������֣��ղ�����Ϣʱ�������������
	ret = ::GetPrivateProfileString("CONFIG", "ObjectApp", NULL, valBuf, MAX_PATH, FileName);
	if(ret == 0)
		return 0;
	if (strcmp(m_ObjectApp, valBuf) != 0 && flag == TRUE) 
		m_IniChanged = 1;
	//��س���·��������������ʱ���޸�,������Ч��
	if (flag == FALSE)
	{
		strcpy(m_ObjectApp, valBuf); 
	}


	//��ȡ��ʾ��Ϣ����ʾʱ��
	ret = ::GetPrivateProfileString("CONFIG", "ShowTime", NULL, valBuf, MAX_PATH, FileName);
	if(ret == 0)
		return 0;
	int nYear, nMonth, nDate, nHour, nMin, nSec;
	sscanf(valBuf, "%d-%d-%d %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);
	CTime t(nYear, nMonth, nDate, nHour, nMin, nSec);
	if (m_ShowTime != t && flag == TRUE) 
		m_IniChanged = 1;
	m_ShowTime = t;


	//��ȡͼ���С��
	ret = ::GetPrivateProfileString("CONFIG", "ImageSize", NULL, valBuf, MAX_PATH, FileName);
	if(ret == 0)
		return 0;
	double tempImageSize = 0.0f;
	tempImageSize = atof(valBuf);
	if(tempImageSize < 0.1) tempImageSize = 0.1;
	if(tempImageSize > 10)  tempImageSize = 10;
	if (abs(m_ImageSize - tempImageSize) > 0.0001 && flag == TRUE) 
		m_IniChanged = 1;
	m_ImageSize = tempImageSize;


	//��ȡ�����С��
	ret = ::GetPrivateProfileString("CONFIG", "FontSize", NULL, valBuf, MAX_PATH, FileName);
	if(ret == 0)
		return 0;
	int tempFontSize = 0;
	tempFontSize = atoi(valBuf);
	if(tempFontSize < 1) tempFontSize = 1;
	if(tempFontSize > 200)  tempFontSize = 200;
	if (m_FontSize != tempFontSize && flag == TRUE) 
		m_IniChanged = 1;
	m_FontSize = tempFontSize;


	//��ȡ�ַ���ȡ�
	ret = ::GetPrivateProfileString("CONFIG", "FontWidth", NULL, valBuf, MAX_PATH, FileName);
	if(ret == 0)
		return 0;
	int tempFontWidth = 0;
	tempFontWidth = atoi(valBuf);
	if(tempFontWidth < 100) tempFontWidth = 100;
	if(tempFontWidth > 2000)  tempFontWidth = 2000;
	if (m_FontWidth != tempFontWidth && flag == TRUE) 
		m_IniChanged = 1;
	m_FontWidth = tempFontWidth;


	//��ȡɾ��·����
	ret = ::GetPrivateProfileString("CONFIG", "DeletePath", NULL, valBuf, MAX_PATH, FileName);
	if(ret == 0)
		return 0;
	if (strcmp(m_DeletePath.GetBuffer(0), valBuf) != 0 && flag == TRUE) 
		m_IniChanged = 1;
	//��س���·��������������ʱ���޸�,������Ч��
	if (flag == FALSE)
	{
		m_DeletePath.Format("%s", valBuf);
	}

	return 1;
}


//�˳�����
void CCheckRunDlg::OnClose() 
{
	KillTimer(1);

	CDialog::OnClose();
}


void CCheckRunDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
