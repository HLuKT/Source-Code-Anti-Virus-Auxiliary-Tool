#pragma once
#include "afxdialogex.h"


// AsciiToHashStringDlg 对话框

class AsciiToHashStringDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AsciiToHashStringDlg)

public:
	AsciiToHashStringDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AsciiToHashStringDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HASH_STRINGDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_AsciiString1;
	CString m_HashString;
	afx_msg void OnBnClickedAsciitohashbut();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusAsciiedit1();
};
