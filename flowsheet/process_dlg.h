#pragma once
#include <string>

// process_dlg 对话框

class process_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(process_dlg)

public:
	process_dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~process_dlg();
	BOOL OnInitDialog();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PROCESS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	std::string* str;
};
