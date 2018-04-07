
// HIDUSBDlg.h : ͷ�ļ�
//
#include "USBClass.h"

#include "JsonClass.h"


#if !defined(AFX_HIDRWDLG_H__5016B8A1_D9D7_42B7_B2A2_945968CD436E__INCLUDED_)
#define AFX_HIDRWDLG_H__5016B8A1_D9D7_42B7_B2A2_945968CD436E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// CHIDUSBDlg �Ի���
class CHIDUSBDlg : public CDialogEx
{
// ����
public:
	CHIDUSBDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIDUSB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboDevice;
	USBClass m_usb;
	JsonClass m_json;
	BOOL m_threadFlag;

	static  DWORD  WINAPI MyThreadReadUSB(LPVOID pParam);
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonClose();
	BOOL ThreadReadUSB();
};

#endif