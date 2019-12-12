
// CchartClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"

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
	CTime	m_time;			//时间
	CEdit   m_input;		//编辑发送控件
	afx_msg void OnEnChangePortEdit();
};
