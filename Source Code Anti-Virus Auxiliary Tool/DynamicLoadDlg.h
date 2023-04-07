#pragma once
#include "afxdialogex.h"


// DynamicLoadDlg 对话框

class DynamicLoadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DynamicLoadDlg)

public:
	DynamicLoadDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DynamicLoadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMIC_LOAD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Function;
	CString m_DynamicLoad;
	afx_msg void OnBnClickedDynamicloadbut();
};
