// process_dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "flowsheet.h"
#include "process_dlg.h"
#include "afxdialogex.h"


// process_dlg 对话框

IMPLEMENT_DYNAMIC(process_dlg, CDialogEx)

process_dlg::process_dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PROCESS_DLG, pParent)
{

}

process_dlg::~process_dlg()
{
}

void process_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL process_dlg::OnInitDialog() {
	CDialog::OnInitDialog();

	GetDlgItem(code_edit)->SetWindowTextA(str->c_str());

	return true;
}

BEGIN_MESSAGE_MAP(process_dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &process_dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// process_dlg 消息处理程序


void process_dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	char temp[80];
	GetDlgItem(code_edit)->GetWindowTextA(temp, sizeof(temp));
	(*str) = temp;
}
