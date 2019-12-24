
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
	DDX_Control(pDX, IDC_COLOR_COMBO, m_CwordColor);
}

BEGIN_MESSAGE_MAP(CCchartClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND() 
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BNT, &CCchartClientDlg::OnBnClickedConnectBnt)
	ON_BN_CLICKED(IDC_DISCONECT_BNT, &CCchartClientDlg::OnBnClickedDisconectBnt)
	ON_EN_CHANGE(IDC_PORT_EDIT, &CCchartClientDlg::OnEnChangePortEdit)
	ON_BN_CLICKED(IDC_SEND_BTN, &CCchartClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CCchartClientDlg::OnBnClickedSaveBtn)
	//ON_BN_CLICKED(IDC_AOUTSEND, &CCchartClientDlg::OnBnClickedAoutsend)
	ON_BN_CLICKED(IDC_CLEARMASG_BNT, &CCchartClientDlg::OnBnClickedClearmasgBnt)
	ON_BN_CLICKED(IDC_AOUTSEND_CHECK, &CCchartClientDlg::OnBnClickedAoutsendCheck)
	ON_WM_CTLCOLOR()
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

	//从配置文件中获取昵称
	WCHAR wszName[MAX_PATH] = { 0 };	//昵称
	//当前路劲保存,MAX_PATH为微软系统最大路径
	WCHAR strPath[MAX_PATH] = { 0 };

	//获取当前程序路径并且保存到字符串中
	GetCurrentDirectoryW(MAX_PATH, strPath);
	TRACE("###strPath = %ls", strPath);

	CString strFilePath;	//文件路径字符串
	strFilePath.Format(L"%ls//Test.ini", strPath);	//配置文件路径

	//获取配置文件的昵称和内容 参数: 项名  见名  NULL, 文件内容	存储变量  路径最大长度  文件路径
	DWORD dwNum = GetPrivateProfileStringW(_T("Client"), _T("NAME"), NULL, 
		wszName, MAX_PATH, strFilePath);

	TRACE("### wszName = %ls", wszName);
	//如果未读取到内容
	if (dwNum > 0) {
		//将读取到的昵称写到编辑控件中
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);

	}	//则设置一个内容
	else {
		WritePrivateProfileStringW(_T("CLINET"), _T("NAME"), L"客户端: ", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端: ");
		UpdateData(FALSE);
	}
	
	//初始化无效控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);	//发送按钮
	GetDlgItem(IDC_DISCONECT_BNT)->EnableWindow(FALSE); //断开连接
	GetDlgItem(IDC_AOUTSEND_CHECK)->EnableWindow(FALSE); //自动回复
	GetDlgItem(IDC_CLEARMASG_BNT)->EnableWindow(TRUE);	//连接按钮

	m_CwordColor.AddString(_T("黑色"));
	m_CwordColor.AddString(_T("红色"));
	m_CwordColor.AddString(_T("蓝色"));
	m_CwordColor.AddString(_T("绿色"));

	m_CwordColor.SetCurSel( 0 );	//设置该控件当前的选择
	SetDlgItemText(IDC_COLOR_COMBO, _T("黑色"));


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
	//连接成功时反置灰
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);	//发送按钮
	GetDlgItem(IDC_DISCONECT_BNT)->EnableWindow(TRUE); //断开连接
	GetDlgItem(IDC_AOUTSEND_CHECK)->EnableWindow(TRUE); //自动回复
	GetDlgItem(IDC_CONNECT_BNT)->EnableWindow(FALSE);	//连接按钮

	// TODO: 在此添加控件通知处理程序代码
	CString strPort, strIP;		//存储端口和ip
	//TRACE("##################################m_client Create Success");
	//获取端口和IP文本中的内容控件中的内容	//SetWindowTextW
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	//CString 转 char * ; uses conversion
	USES_CONVERSION;	//宏声明
	// LPCSTR 声明  typedef const CHAR * LPSTR
	LPCSTR szPort = (LPSTR)T2A(strPort);
	LPCSTR szIP = (LPSTR)T2A(strIP);
	TRACE("szPORT=%S, IP=%S", szPort, szIP);

	//将IP地址字符串转换为数字
	int iPort = _ttoi(strPort);
	//int iIP = _ttoi(strIP);


	//SOCKET
	//创建socket 对象
	m_client = new CMySocket;

	//创建套接字
	if (!m_client->Create()) {
		TRACE("###  m_client Create error %d", GetLastError() );
		return;
	}
	else {

		TRACE("###  m_client   Create  Success  OK");
	}

	//建立连接
	if (m_client->Connect(strIP, iPort) != SOCKET_ERROR ) {
		TRACE("m_client Connect error %d", GetLastError());
		return;
	}


}

//mark

void CCchartClientDlg::OnBnClickedDisconectBnt()
{
	// TODO: 在此添加控件通知处理程序代码
	//1 控件置灰
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);	//发送按钮
	GetDlgItem(IDC_DISCONECT_BNT)->EnableWindow(FALSE); //断开连接
	GetDlgItem(IDC_AOUTSEND_CHECK)->EnableWindow(FALSE); //自动回复
	GetDlgItem(IDC_CLEARMASG_BNT)->EnableWindow(TRUE);	//连接按钮

	// 资源回收
	m_client->Close();
	if (m_client  != NULL) {	//如果还存在连接socket 对象,不等于空
		delete m_client;
		m_client = NULL;
	}

	//显示断开连接
	CString  strShow;
	strShow = CatShowString(_T(": 断开与服务器连接"), NULL);
	m_list.AddString(strShow);
	UpdateData(FALSE);

}


void CCchartClientDlg::OnEnChangePortEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//消息发送优化
CString CCchartClientDlg::CatShowString(CString strInfo, CString strMsg) {

	CTime tmNow;
	CString strTime;	//保存当前时间

	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X");

	CString strShow;		//返回内容
	// 时间  我: 内容
	strShow = strTime + strInfo;
	strShow += strMsg;

	return strShow;


}

//发送按钮
void CCchartClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取编辑对话框中的内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMASG_EDIT)->GetWindowTextW(strTmpMsg);

	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);

	strTmpMsg = strName + _T(":")+ strTmpMsg   ;


	//将获取的字符串内容转换成 char * 类型
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//发送消息
	m_client->Send(szSendBuf, SEND_CLINE_BUF, 0);

	//发送内容显示
	CString  strShow;
	//CString  strInfo = _T("我: ");
	
	strShow = CatShowString(_T(""), strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

	GetDlgItem(IDC_SENDMASG_EDIT)->SetWindowTextW(_T(" "));

}

//设置昵称
void CCchartClientDlg::OnBnClickedSaveBtn()
{

	// TODO: 在此添加控件通知处理程序代码
	
	CString strName;	//昵称
	// 读取编辑昵称的文本框内容读取
	GetDlgItemText(IDC_NAME_EDIT, strName);
	//如果获取的昵称字符长度为0
	if (strName.GetLength() <= 0) {
		MessageBox(_T("昵称不能为空哦"));
		return ;
	}

	if (IDOK == AfxMessageBox(_T("确认要修改昵称吗"), MB_OKCANCEL) ) {


		//当前路劲保存,MAX_PATH为微软系统最大路径
		WCHAR strPath[MAX_PATH] = { 0 };
		//获取当前程序路径并且保存到字符串中
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("###strPath = %ls", strPath);

		CString strFilePath;	//文件路径字符串
		strFilePath.Format(L"%ls//Test.ini", strPath);	//配置文件路径




		//创建配置文件和写入内容   参数(项名,见名,存储的内容, 配置文件的路径
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
		TRACE("###strFilePath = %ls", strFilePath);
	}


}

//单选框取消
/*
void CCchartClientDlg::OnBnClickedAoutsend()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果单选按钮选中状态
	if (((CButton*)GetDlgItem(IDC_AOUTSEND))->GetCheck()) {
		//设置为不选中
		((CButton*)GetDlgItem(IDC_AOUTSEND))->SetCheck(FALSE);
	}
	else {
		//设置为选中
		((CButton*)GetDlgItem(IDC_AOUTSEND))->SetCheck(TRUE);
	}
}
*/

void CCchartClientDlg::OnBnClickedClearmasgBnt()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CCchartClientDlg::OnBnClickedAoutsendCheck()
{
	// TODO: 在此添加控件通知处理程序代码
		//如果单选按钮选中状态
	if (((CButton*)GetDlgItem(IDC_AOUTSEND_CHECK))->GetCheck()) {
		//设置为不选中
		((CButton*)GetDlgItem(IDC_AOUTSEND_CHECK))->SetCheck(FALSE);
	}
	else {
		//设置为选中
		((CButton*)GetDlgItem(IDC_AOUTSEND_CHECK))->SetCheck(TRUE);
	}



}


HBRUSH CCchartClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strColor;
	m_CwordColor.GetWindowTextW(strColor);	//获取控件当前的内容到字符串中

	if (IDC_LIST1 == pWnd->GetDlgCtrlID() || IDC_SENDMASG_EDIT == pWnd->GetDlgCtrlID()  )
	{
		if (strColor == L"黑色") {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if(strColor == L"红色"){
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"蓝色") {
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"绿色") {
			pDC->SetTextColor(RGB(0, 255, 0));
		}

	}

	return hbr;
}
