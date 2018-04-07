
// HIDUSBDlg.cpp : ʵ���ļ�
//


// ReadFile ���������û�����ݼ����Ļ��ͻ���������Ҫ�ܿ���������߽���������

#include "stdafx.h"
#include "HIDUSB.h"
#include "HIDUSBDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CHIDUSBDlg �Ի���



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


// CHIDUSBDlg ��Ϣ�������

BOOL CHIDUSBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//Json::Value myjson = m_json.GetJsonFromFile("init.json");
	//CString strip = myjson["httpip"].asCString();
	//MessageBox(strip);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHIDUSBDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cboDevice.ResetContent();

	std::vector<CString> vStr;
	if (!m_usb.SearchUSB(vStr))
	{
		MessageBox("����ʧ��");
		return ;
	}

	GetDlgItem(IDC_EDIT_READ_DATA)->SetWindowText("");
	GetDlgItem(IDC_EDIT_ANLY)->SetWindowText("");

	for (int i = 0; i < vStr.size(); i++)
	{	
		// \\ ? \hid#vid_17ef&pid_6050#
		m_cboDevice.AddString(vStr[i]);				 // ���������������оٳ���
		CString strTemp = vStr[i].Mid(12, 4);
		CString strTemp2 = vStr[i].Mid(21, 4);
		if (strTemp == "0483" && strTemp2 == "5750") // vid pid ��
		{
			m_cboDevice.SetCurSel(i);			     // ������������·������

			OnBnClickedButtonConnect();
			//GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
			CString strName;
			GetDlgItem(IDC_COMBO_DEVICE)->GetWindowTextA(strName);
			if (1 != m_usb.ConnectUSB(strName))
			{
				MessageBox("����ʧ��");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������



	CString strName;
	GetDlgItem(IDC_COMBO_DEVICE)->GetWindowTextA(strName);
	if (1 != m_usb.ConnectUSB(strName))
	{
		MessageBox("����ʧ��");
		return ;
	}

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);

}


void CHIDUSBDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CHAR	OutputReport[64] = {0x00,0x7b,0x22,0x43, 0x4d,0x44,0x22,0x3a,
								 0x31,0x30, 0x2c,0x22, 0x44,0x41,0x54,0x41,
								 0x22,0x3a, 0x31,0x7d, 0x00,0x00};
	
	if (!m_usb.WriteUSB(OutputReport))
	{
		MessageBox("д��ʧ��");
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
	for (int i = 0; i<8; i++)   //���ھŸ�������Ҳ���ط���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_usb.CloseUSB())
	{
		MessageBox("�ر�ʧ��");
		return ;
	}
	//m_threadFlag = TRUE;
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	/*GetDlgItem(IDC_EDIT_READ_DATA)->SetWindowText("");
	GetDlgItem(IDC_EDIT_ANLY)->SetWindowText("");*/

}



