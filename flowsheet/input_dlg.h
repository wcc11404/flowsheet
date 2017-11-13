#pragma once
#include <map>
#include <string>

// input_dlg 对话框

class input_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(input_dlg)

public:
	input_dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~input_dlg();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = INPUT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	std::map<std::string, double>* iden;
	void init(std::map<std::string, double>* i);
};
