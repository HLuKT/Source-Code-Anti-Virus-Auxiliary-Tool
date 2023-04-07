// DynamicLoadDlg.cpp: 实现文件
//

#include "pch.h"
#include "Source Code Anti-Virus Auxiliary Tool.h"
#include "afxdialogex.h"
#include "DynamicLoadDlg.h"
#include "Common.h"

// DynamicLoadDlg 对话框

IMPLEMENT_DYNAMIC(DynamicLoadDlg, CDialogEx)

DynamicLoadDlg::DynamicLoadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DYNAMIC_LOAD_DIALOG, pParent)
	, m_Function(_T(""))
	, m_DynamicLoad(_T(""))
{

}

DynamicLoadDlg::~DynamicLoadDlg()
{
}

void DynamicLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FUNCTIONEDIT, m_Function);
	DDX_Text(pDX, IDC_DYNAMICLOADEDIT, m_DynamicLoad);
}


BEGIN_MESSAGE_MAP(DynamicLoadDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DYNAMICLOADBUT, &DynamicLoadDlg::OnBnClickedDynamicloadbut)
END_MESSAGE_MAP()


// DynamicLoadDlg 消息处理程序
wchar_t cDlls[][255] = { L"Kernel32.dll",L"User32.dll",L"ADVAPI32.dll",L"SHLWAPI.dll",L"SHELL32.dll",L"Winmm.dll",L"WS2_32.dll",L"IMM32.dll",L"WININET.dll",L"AVICAP32.dll",L"MSVFW32.dll",L"PSAPI.DLL",L"WTSAPI32.dll" ,L"Mpr.dll",L"Dnsapi.dll",L"advapi32.dll" };

void DynamicLoadDlg::OnBnClickedDynamicloadbut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csFunctionName;
	GetDlgItemText(IDC_FUNCTIONEDIT, csFunctionName);
	USES_CONVERSION;
	char* cFunctionName = T2A(csFunctionName);
	CString szModName = GetMoudleNameByFunctionName(cFunctionName); 
	if (szModName != L"")
	{
		//SetDlgItemText(IDC_DYNAMICLOADEDIT, szModName);//直接返回也是可以的
		for (int i = 0; i < sizeof(cDlls) / sizeof(cDlls[0]); i++)
		{
			if (!szModName.CollateNoCase(cDlls[i]))
			{
				SetDlgItemText(IDC_DYNAMICLOADEDIT, cDlls[i]);
			}
		}
	}
	else
	{
		SetDlgItemText(IDC_DYNAMICLOADEDIT, L"该函数无效或不支持");
	}
}
