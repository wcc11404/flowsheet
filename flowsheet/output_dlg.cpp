// output_dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "flowsheet.h"
#include "output_dlg.h"
#include "afxdialogex.h"


// output_dlg �Ի���

IMPLEMENT_DYNAMIC(output_dlg, CDialogEx)

output_dlg::output_dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(OUTPUT_DLG, pParent)
{

}

output_dlg::~output_dlg()
{
}

void output_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL output_dlg::OnInitDialog() {
	CDialog::OnInitDialog();

	GetDlgItem(variable_name_o)->SetWindowTextA(str->c_str());

	return true;
}
BEGIN_MESSAGE_MAP(output_dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &output_dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// output_dlg ��Ϣ�������


void output_dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char temp[80];
	GetDlgItem(variable_name_o)->GetWindowTextA(temp, sizeof(temp));
	(*str) = temp;
}
