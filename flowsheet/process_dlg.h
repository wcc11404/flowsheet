#pragma once
#include <string>

// process_dlg �Ի���

class process_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(process_dlg)

public:
	process_dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~process_dlg();
	BOOL OnInitDialog();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = PROCESS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	std::string* str;
};
