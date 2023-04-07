// AsciiToHashStringDlg.cpp: 实现文件
//

#include "pch.h"
#include "Source Code Anti-Virus Auxiliary Tool.h"
#include "afxdialogex.h"
#include "AsciiToHashStringDlg.h"
#include "Common.h"

// AsciiToHashStringDlg 对话框

IMPLEMENT_DYNAMIC(AsciiToHashStringDlg, CDialogEx)

AsciiToHashStringDlg::AsciiToHashStringDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HASH_STRINGDIALOG, pParent)
	, m_AsciiString1(_T(""))
	, m_HashString(_T(""))
{

}

AsciiToHashStringDlg::~AsciiToHashStringDlg()
{
}

void AsciiToHashStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ASCIIEDIT1, m_AsciiString1);
	DDX_Text(pDX, IDC_HASHEDIT, m_HashString);
}


BEGIN_MESSAGE_MAP(AsciiToHashStringDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ASCIITOHASHBUT, &AsciiToHashStringDlg::OnBnClickedAsciitohashbut)
	ON_EN_SETFOCUS(IDC_ASCIIEDIT1, &AsciiToHashStringDlg::OnSetfocusAsciiedit1)
END_MESSAGE_MAP()


// AsciiToHashStringDlg 消息处理程序

BOOL AsciiToHashStringDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str = L"输入函数名或DLL名称,点击 Run>> 将Ascii字符串转换为Hash字符串……";
	GetDlgItem(IDC_ASCIIEDIT1)->SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void AsciiToHashStringDlg::OnBnClickedAsciitohashbut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csGenerateStr = GenerateString(6);
	//获取要转换的字符串
	GetDlgItemText(IDC_ASCIIEDIT1, m_AsciiString1);
	if (m_AsciiString1.IsEmpty())
	{
		return;
	}
	// 如果是DLL
	CString data = m_AsciiString1;
	if (m_AsciiString1.Right(4) == ".dll")
	{
		m_HashString.Format(L"HMODULE mod = getModule(", csGenerateStr);
	}
	// 如果是函数
	else
	{
		m_HashString.Format(L"LPVOID addr = getAPIAddr(mod,", csGenerateStr);
	}
	// 将数据转换为十六进制字符串
	CStringA dataA(data);
	LPSTR lpBuffer = dataA.GetBufferSetLength(data.GetLength());
	LONGLONG temp = HexToHash(lpBuffer);
	CString result;
	result.Format(TEXT("%lld"), temp);
	m_HashString += result;
	dataA.ReleaseBuffer();
	m_HashString += L");\r\n";
	SetDlgItemText(IDC_HASHEDIT, m_HashString);
}

void AsciiToHashStringDlg::OnSetfocusAsciiedit1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Input;
	GetDlgItemText(IDC_ASCIIEDIT1, Input);
	if (Input != L"输入函数名或DLL名称,点击 Run>> 将Ascii字符串转换为Hash字符串……")return;
	SetDlgItemText(IDC_ASCIIEDIT1, L"");
	UpdateData(FALSE);
}
