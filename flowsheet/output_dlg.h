#pragma once
#include <string>

// output_dlg 对话框

class output_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(output_dlg)

public:
	output_dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~output_dlg();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = OUTPUT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	std::string* str;
};
