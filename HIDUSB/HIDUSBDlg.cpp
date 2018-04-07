
// HIDUSBDlg.cpp : 实现文件
//


// ReadFile 还存在如果没有数据继续的话就花死掉，需要避开这个，或者解决这个问题

#include "stdafx.h"
#include "HIDUSB.h"
#include "HIDUSBDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHIDUSBDlg 对话框



CHIDUSBDlg::CHIDUSBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HIDUSB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHIDUSBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_cboDevice);
}

BEGIN_MESSAGE_MAP(CHIDUSBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CHIDUSBDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CHIDUSBDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CHIDUSBDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CHIDUSBDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CHIDUSBDlg 消息处理程序

BOOL CHIDUSBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//Json::Value myjson = m_json.GetJsonFromFile("init.json");
	//CString strip = myjson["httpip"].asCString();
	//MessageBox(strip);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHIDUSBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHIDUSBDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHIDUSBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//bool GetStringMid(CString strData, int iDataIndex, int iDataLong, CString strBuf)
//{
//	strBuf = strData.Mid(iDataIndex, iDataLong);
//	return TRUE;
//}


void CHIDUSBDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cboDevice.ResetContent();

	std::vector<CString> vStr;
	if (!m_usb.SearchUSB(vStr))
	{
		MessageBox("搜索失败");
		return ;
	}

	GetDlgItem(IDC_EDIT_READ_DATA)->SetWindowText("");
	GetDlgItem(IDC_EDIT_ANLY)->SetWindowText("");

	for (int i = 0; i < vStr.size(); i++)
	{	
		// \\ ? \hid#vid_17ef&pid_6050#
		m_cboDevice.AddString(vStr[i]);				 // 把收索到的数据列举出来
		CString strTemp = vStr[i].Mid(12, 4);
		CString strTemp2 = vStr[i].Mid(21, 4);
		if (strTemp == "0483" && strTemp2 == "5750") // vid pid 把
		{
			m_cboDevice.SetCurSel(i);			     // 设置收索到的路径名字

			OnBnClickedButtonConnect();
			//GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
			CString strName;
			GetDlgItem(IDC_COMBO_DEVICE)->GetWindowTextA(strName);
			if (1 != m_usb.ConnectUSB(strName))
			{
				MessageBox("连接失败");
				return;
			}
			OnBnClickedButtonSend();


			return ;
		}


	}

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);

}


void CHIDUSBDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码



	CString strName;
	GetDlgItem(IDC_COMBO_DEVICE)->GetWindowTextA(strName);
	if (1 != m_usb.ConnectUSB(strName))
	{
		MessageBox("连接失败");
		return ;
	}

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);

}


void CHIDUSBDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CHAR	OutputReport[64] = {0x00,0x7b,0x22,0x43, 0x4d,0x44,0x22,0x3a,
								 0x31,0x30, 0x2c,0x22, 0x44,0x41,0x54,0x41,
								 0x22,0x3a, 0x31,0x7d, 0x00,0x00};
	
	if (!m_usb.WriteUSB(OutputReport))
	{
		MessageBox("写入失败");
		return ;
	}

	HANDLE hThread = CreateThread(NULL, 0, MyThreadReadUSB, this, 0, NULL);
	SetThreadPriority(hThread, THREAD_PRIORITY_BELOW_NORMAL);
	if (hThread)
	{
		CloseHandle(hThread);
		hThread = NULL;
	}
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
}

DWORD  CHIDUSBDlg::MyThreadReadUSB(LPVOID pParam)
{
	CHIDUSBDlg *p = (CHIDUSBDlg*)pParam;
	p->ThreadReadUSB();
	return 0;
}

BOOL CHIDUSBDlg::ThreadReadUSB()
{
	CString strReadBuf, strTestBuf, strShowRead, strShowAnly;
	for (int i = 0; i<8; i++)   //读第九个读不了也不回返回
	{
		m_usb.ReadUSB(strReadBuf);
		strShowRead += strReadBuf;
		GetDlgItem(IDC_EDIT_READ_DATA)->SetWindowText(strShowRead);

		USES_CONVERSION;
		std::string strData = T2A(strReadBuf.GetBuffer(0));
		Json::Value value = m_json.ReadJson(strData);		//"{ \"CMD\":2 , \"DATA\" : 3 }"
		int iCmd = value["CMD"].asInt();
		int iData = value["DATA"].asInt();
		strTestBuf.Format("%d,%d, ", iCmd, iData);
		strShowAnly += strTestBuf;
		GetDlgItem(IDC_EDIT_ANLY)->SetWindowText(strShowAnly);

	}
	OnBnClickedButtonClose();
	return 0;
}


void CHIDUSBDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_usb.CloseUSB())
	{
		MessageBox("关闭失败");
		return ;
	}
	//m_threadFlag = TRUE;
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	/*GetDlgItem(IDC_EDIT_READ_DATA)->SetWindowText("");
	GetDlgItem(IDC_EDIT_ANLY)->SetWindowText("");*/

}



