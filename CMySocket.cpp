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

//调用连接
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("####OnConnect");
	//获取主对话框
	CCchartClientDlg* dlg = (CCchartClientDlg *)AfxGetApp()->GetMainWnd();
	CString str;

	//获取当前实时时间,并且打印连接
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%x");
	str += _T("与服务器连接成功");
	//在 历史对话框中显示
	dlg->m_list.AddString(str);


}

//收到连接
void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####OnConnect");
}
