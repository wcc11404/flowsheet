#pragma once
#include <string>

// output_dlg �Ի���

class output_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(output_dlg)

public:
	output_dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~output_dlg();
	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = OUTPUT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	std::string* str;
};
