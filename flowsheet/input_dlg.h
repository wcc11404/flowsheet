#pragma once
#include <map>
#include <string>

// input_dlg �Ի���

class input_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(input_dlg)

public:
	input_dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~input_dlg();
	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = INPUT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	std::map<std::string, double>* iden;
	void init(std::map<std::string, double>* i);
};
