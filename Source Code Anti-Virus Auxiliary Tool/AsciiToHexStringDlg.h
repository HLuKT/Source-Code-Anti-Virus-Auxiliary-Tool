#pragma once
#include "afxdialogex.h"


// AsciiToHexStringDlg 对话框

class AsciiToHexStringDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AsciiToHexStringDlg)

public:
	AsciiToHexStringDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AsciiToHexStringDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HEX_STRINGDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_AsciiString;
	CString m_HexString;
	afx_msg void OnBnClickedAsciitohexbut();
	afx_msg void OnSetfocusAsciiedit();
	virtual BOOL OnInitDialog();
};
