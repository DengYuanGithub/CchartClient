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

//��������
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("####OnConnect");
	//��ȡ���Ի���
	CCchartClientDlg* dlg = (CCchartClientDlg *)AfxGetApp()->GetMainWnd();
	CString str;

	//��ȡ��ǰʵʱʱ��,���Ҵ�ӡ����
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%x");
	str += _T("����������ӳɹ�");
	//�� ��ʷ�Ի�������ʾ
	dlg->m_list.AddString(str);


}

//�յ�����
void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("####OnConnect");
}
