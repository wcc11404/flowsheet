#pragma once
#include <string>

// decision_dlg 对话框

class decision_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(decision_dlg)

public:
	decision_dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~decision_dlg();
	BOOL OnInitDialog();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DECISION_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	std::string* str;
	int* judge;
};
