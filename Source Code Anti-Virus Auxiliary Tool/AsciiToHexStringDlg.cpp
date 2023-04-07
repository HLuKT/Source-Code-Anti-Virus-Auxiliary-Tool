// AsciiToHexStringDlg.cpp: 实现文件
//

#include "pch.h"
#include "Source Code Anti-Virus Auxiliary Tool.h"
#include "afxdialogex.h"
#include "AsciiToHexStringDlg.h"
#include <string>
#include "Common.h"
#define LEN 6

// AsciiToHexStringDlg 对话框

IMPLEMENT_DYNAMIC(AsciiToHexStringDlg, CDialogEx)

AsciiToHexStringDlg::AsciiToHexStringDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HEX_STRINGDIALOG, pParent)
	, m_AsciiString(_T(""))
	, m_HexString(_T(""))
{

}

AsciiToHexStringDlg::~AsciiToHexStringDlg()
{
}

void AsciiToHexStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ASCIIEDIT, m_AsciiString);
	DDX_Text(pDX, IDC_HEXEDIT, m_HexString);
}


BEGIN_MESSAGE_MAP(AsciiToHexStringDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ASCIITOHEXBUT, &AsciiToHexStringDlg::OnBnClickedAsciitohexbut)
	ON_EN_SETFOCUS(IDC_ASCIIEDIT, &AsciiToHexStringDlg::OnSetfocusAsciiedit)
END_MESSAGE_MAP()


// AsciiToHexStringDlg 消息处理程序

BOOL AsciiToHexStringDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str = L"输入函数名或DLL名称,点击 Run>> 将Ascii字符串转换为Hex字符串……";
	GetDlgItem(IDC_ASCIIEDIT)->SetWindowText(str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void AsciiToHexStringDlg::OnBnClickedAsciitohexbut()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取长度为6的随机字符串作为变量名
	CString csGenerateStr = GenerateString(6);
	//获取要转换的字符串
	GetDlgItemText(IDC_ASCIIEDIT,m_AsciiString);
	if (m_AsciiString.IsEmpty())
	{
		return;
	}

	CString data = m_AsciiString;

	// 将数据转换为十六进制字符串
	m_HexString.Format(L"char %s[] = {", csGenerateStr);
	CStringA dataA(data);
	LPSTR lpBuffer = dataA.GetBufferSetLength(data.GetLength());
	HexToAscii(reinterpret_cast<unsigned char*>(lpBuffer), m_HexString, data.GetLength());
	dataA.ReleaseBuffer();
	m_HexString += L" 0x00};\r\n";
	SetDlgItemText(IDC_HEXEDIT, m_HexString);
}

void AsciiToHexStringDlg::OnSetfocusAsciiedit()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Input;
	GetDlgItemText(IDC_ASCIIEDIT, Input);
	if (Input != L"输入函数名或DLL名称,点击 Run>> 将Ascii字符串转换为Hex字符串……")return;
	SetDlgItemText(IDC_ASCIIEDIT, L"");
	UpdateData(FALSE);
}