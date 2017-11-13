// decision_dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "flowsheet.h"
#include "decision_dlg.h"
#include "afxdialogex.h"


// decision_dlg 对话框

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


// decision_dlg 消息处理程序


void decision_dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	char temp[80];
	GetDlgItem(judge_code)->GetWindowTextA(temp, sizeof(temp));
	(*str) = temp;
}
