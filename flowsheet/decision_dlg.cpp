// decision_dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "flowsheet.h"
#include "decision_dlg.h"
#include "afxdialogex.h"


// decision_dlg �Ի���

IMPLEMENT_DYNAMIC(decision_dlg, CDialogEx)

decision_dlg::decision_dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DECISION_DLG, pParent)
{

}

decision_dlg::~decision_dlg()
{
}

void decision_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL decision_dlg::OnInitDialog() {
	CDialog::OnInitDialog();

	GetDlgItem(judge_code)->SetWindowTextA(str->c_str());

	return true;
}

BEGIN_MESSAGE_MAP(decision_dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &decision_dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// decision_dlg ��Ϣ�������


void decision_dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char temp[80];
	GetDlgItem(judge_code)->GetWindowTextA(temp, sizeof(temp));
	(*str) = temp;
}
