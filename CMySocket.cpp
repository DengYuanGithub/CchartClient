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

//���ӻص�
void CMySocket::OnConnect(int nErrorCode)
{	

	TRACE("###   Client sock OnConnect  OK");
	//��ȡ���Ի���
	CCchartClientDlg* dlg = (CCchartClientDlg *)AfxGetApp()->GetMainWnd();

	CString  strShow;
	CString  strInfo = _T("����������ӳɹ�");

	strShow = dlg->CatShowString(strInfo, _T("") );

	dlg->m_list.AddString(strShow);

}

//�յ�����
void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("###   Clinet  Receive OK ");
	CCchartClientDlg* dlg = (CCchartClientDlg*)AfxGetApp()->GetMainWnd();

	//��������
	char szRecvBuf[SEND_CLINE_BUF] = { 0 };
	Receive(szRecvBuf, SEND_CLINE_BUF, 0);

	//��������ת��
	USES_CONVERSION;
	CString strRecvMsg = A2T(szRecvBuf);

	CString strShow;
	CString strInfo = _T("�����: ");


	strShow = dlg->CatShowString(strInfo, strRecvMsg );

	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnReceive(nErrorCode);
}
