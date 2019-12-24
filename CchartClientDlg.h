
// CchartClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"
#define  SEND_CLINE_BUF  1024

// CCchartClientDlg 对话框
class CCchartClientDlg : public CDialogEx
{
// 构造
public:
	CCchartClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCHARTCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnectBnt();
	afx_msg void OnBnClickedDisconectBnt();
	CMySocket* m_client;	//Sock 对象
	CListBox m_list;		//历史记录控件
	CEdit   m_input;		//编辑发送控件
	afx_msg void OnEnChangePortEdit();
	afx_msg void OnBnClickedSendBtn();
	CString CatShowString(CString strInfo, CString strMsg); //消息发送
	afx_msg void OnBnClickedSaveBtn();
	//afx_msg void OnBnClickedAoutsend();
	afx_msg void OnBnClickedClearmasgBnt();
	afx_msg void OnBnClickedAoutsendCheck();
	CComboBox m_CwordColor;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
