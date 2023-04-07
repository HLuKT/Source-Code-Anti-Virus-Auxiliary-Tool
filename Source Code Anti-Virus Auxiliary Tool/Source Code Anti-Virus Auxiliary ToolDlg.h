
// Source Code Anti-Virus Auxiliary ToolDlg.h: 头文件
//

#pragma once
#include "AsciiToHexStringDlg.h"
#include "AsciiToHashStringDlg.h"
#include "DynamicLoadDlg.h"

// CSourceCodeAntiVirusAuxiliaryToolDlg 对话框
class CSourceCodeAntiVirusAuxiliaryToolDlg : public CDialogEx
{
// 构造
public:
	CSourceCodeAntiVirusAuxiliaryToolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOURCE_CODE_ANTIVIRUS_AUXILIARY_TOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	AsciiToHexStringDlg m_AsciiToHexStringTable;
	AsciiToHashStringDlg m_AsciiToHashStringTable;
	DynamicLoadDlg m_DynamicLoadTable;
public:
	afx_msg void OnSelchangeTablist(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl m_TableList;
};
