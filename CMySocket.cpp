#include "pch.h"
#include "CMySocket.h"
#include "CchartClientDlg.h"
#include "CchartClient.h"

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

//连接回调
void CMySocket::OnConnect(int nErrorCode)
{	

	TRACE("###   Client sock OnConnect  OK");
	//获取主对话框
	CCchartClientDlg* dlg = (CCchartClientDlg *)AfxGetApp()->GetMainWnd();

	CString  strShow;
	CString  strInfo = _T("与服务器连接成功");

	strShow = dlg->CatShowString(strInfo, _T("") );

	dlg->m_list.AddString(strShow);

}

//收到连接
void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("###   Clinet  Receive OK ");
	CCchartClientDlg* dlg = (CCchartClientDlg*)AfxGetApp()->GetMainWnd();

	//接收数据
	char szRecvBuf[SEND_CLINE_BUF] = { 0 };
	Receive(szRecvBuf, SEND_CLINE_BUF, 0);

	//数据类型转换
	USES_CONVERSION;
	CString strRecvMsg = A2T(szRecvBuf);

	CString strShow;
	CString strInfo = _T("服务端: ");


	strShow = dlg->CatShowString(strInfo, strRecvMsg );

	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnReceive(nErrorCode);
}
