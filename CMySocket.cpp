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

	//����յ�����Ϣ����,����ʾ���Ի�����
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);

	//ѡ�е�ѡ�ؼ���ť
	if (((CButton*)dlg->GetDlgItem(IDC_AOUTSEND_CHECK))->GetCheck()) {

		CString  strAoutSendMsg;
		CString  strName;
		//��ȡ�Զ��ظ��༭���е�����
		dlg->GetDlgItemText(IDC_OUTSENDMASG_EDIT, strAoutSendMsg);
		//��ȡ�ǳ�
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);

		//�ǳ�+[�Զ��ظ�] + ����
		CString  strMsg =strName + _T("�Զ��ظ�") + strAoutSendMsg;

		//��ȡ�������ݵĵ�ַ
		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf , SEND_CLINE_BUF, 0);

		//ʱ�� +���ݲ�����ʾ���б�ؼ���
		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);

	}


	CAsyncSocket::OnReceive(nErrorCode);
}
