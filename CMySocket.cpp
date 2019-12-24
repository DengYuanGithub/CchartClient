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

	//组合收到的消息内容,并显示到对话框中
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);

	//选中单选控件按钮
	if (((CButton*)dlg->GetDlgItem(IDC_AOUTSEND_CHECK))->GetCheck()) {

		CString  strAoutSendMsg;
		CString  strName;
		//获取自动回复编辑框中的内容
		dlg->GetDlgItemText(IDC_OUTSENDMASG_EDIT, strAoutSendMsg);
		//获取昵称
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);

		//昵称+[自动回复] + 内容
		CString  strMsg =strName + _T("自动回复") + strAoutSendMsg;

		//获取发送内容的地址
		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf , SEND_CLINE_BUF, 0);

		//时间 +内容并且显示到列表控件中
		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);

	}


	CAsyncSocket::OnReceive(nErrorCode);
}
