// input_dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "flowsheet.h"
#include "input_dlg.h"
#include "afxdialogex.h"
#include <string>
#include <sstream>


// input_dlg 对话框

IMPLEMENT_DYNAMIC(input_dlg, CDialogEx)

input_dlg::input_dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(INPUT_DLG, pParent)
{
	
}

input_dlg::~input_dlg()
{
}

void input_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL input_dlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	for (std::map<std::string, double>::iterator it = iden->begin(); it != iden->end(); it++) {
		std::string str = (*it).first;
		GetDlgItem(variable_name_i)->SetWindowTextA(str.c_str());
		char temp[80];
		sprintf(temp, "%g", (*it).second);
		GetDlgItem(variable_value_i)->SetWindowTextA(temp);
	}

	return true;
}

void input_dlg::init(std::map<std::string, double>* i) {
	iden = i;
}

BEGIN_MESSAGE_MAP(input_dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &input_dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// input_dlg 消息处理程序

void input_dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//iden->clear();
	char temp[80];
	GetDlgItem(variable_name_i)->GetWindowTextA(temp, sizeof(temp));
	std::string strtemp = temp;
	GetDlgItem(variable_value_i)->GetWindowTextA(temp,sizeof(temp));
	std::string dbtemp = temp;
	std::stringstream ss(dbtemp);
	double db=0;
	ss >> db;
	(*iden)[strtemp] = db;
}
