#pragma once
#include <string>

// decision_dlg �Ի���

class decision_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(decision_dlg)

public:
	decision_dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~decision_dlg();
	BOOL OnInitDialog();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = DECISION_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	std::string* str;
	int* judge;
};
