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
	CComboBox* m_cbExamble = (CComboBox*)GetDlgItem(combo1);
	m_cbExamble->AddString("空");
	m_cbExamble->AddString("否");
	m_cbExamble->AddString("是");
	m_cbExamble->SetCurSel(judge[0]);

	m_cbExamble = (CComboBox*)GetDlgItem(combo2);
	m_cbExamble->AddString("空");
	m_cbExamble->AddString("否");
	m_cbExamble->AddString("是");
	m_cbExamble->SetCurSel(judge[1]);

	m_cbExamble = (CComboBox*)GetDlgItem(combo3);
	m_cbExamble->AddString("空");
	m_cbExamble->AddString("否");
	m_cbExamble->AddString("是");
	m_cbExamble->SetCurSel(judge[2]);

	m_cbExamble = (CComboBox*)GetDlgItem(combo4);
	m_cbExamble->AddString("空");
	m_cbExamble->AddString("否");
	m_cbExamble->AddString("是");
	m_cbExamble->SetCurSel(judge[3]);
	
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

	CComboBox* m_cbExamble = (CComboBox*)GetDlgItem(combo1);
	judge[0] = m_cbExamble->GetCurSel();
	m_cbExamble = (CComboBox*)GetDlgItem(combo2);
	judge[1] = m_cbExamble->GetCurSel();
	m_cbExamble = (CComboBox*)GetDlgItem(combo3);
	judge[2] = m_cbExamble->GetCurSel();
	m_cbExamble = (CComboBox*)GetDlgItem(combo4);
	judge[3] = m_cbExamble->GetCurSel();
}
