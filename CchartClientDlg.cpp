
// CchartClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CchartClient.h"
#include "CchartClientDlg.h"
#include "afxdialogex.h"
#include <atlbase.h>


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


// CCchartClientDlg 对话框



CCchartClientDlg::CCchartClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CCHARTCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCchartClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SENDMASG_EDIT, m_input);
}

BEGIN_MESSAGE_MAP(CCchartClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND() 
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BNT, &CCchartClientDlg::OnBnClickedConnectBnt)
	ON_BN_CLICKED(IDC_DISCONECT_BNT, &CCchartClientDlg::OnBnClickedDisconectBnt)
	ON_EN_CHANGE(IDC_PORT_EDIT, &CCchartClientDlg::OnEnChangePortEdit)
END_MESSAGE_MAP()
//mark

// CCchartClientDlg 消息处理程序

BOOL CCchartClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	AfxSocketInit();		//套接字初始化

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	//端口文本编辑框控件
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	//IP文本编辑库控件
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCchartClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCchartClientDlg::OnPaint()
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
HCURSOR CCchartClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCchartClientDlg::OnBnClickedConnectBnt()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPort, strIP;		//存储端口和ip
	//TRACE("##################################m_client Create Success");
	//获取端口和IP文本中的内容控件中的内容	//SetWindowTextW
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	//CString 转 char * ; uses conversion
	USES_CONVERSION;
	LPCSTR szPort = (LPSTR)T2A(strPort);
	LPCSTR szIP = (LPSTR)T2A(strIP);
	TRACE("szPORT=%S, IP=%S", szPort, szIP);

	//将IP地址字符串转换为数字
	int iPort = _ttoi(strPort);
	//int iIP = _ttoi(strIP);

	//创建socket 对象
	m_client = new CMySocket;

	//创建套接字
	if (!m_client->Create()) {
		TRACE("#######################################\n");
		TRACE("\nm_client Create error %d", GetLastError() );
		return;
	}
	else {

		TRACE("#######################################\n m_client   Create  Success  OK");
	}

	//建立连接
	m_client->Connect(strIP, iPort);
	TRACE("#######################################\n  Connect endl ");

}

//mark

void CCchartClientDlg::OnBnClickedDisconectBnt()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCchartClientDlg::OnEnChangePortEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
