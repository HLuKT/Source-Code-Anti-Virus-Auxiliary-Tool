
// Source Code Anti-Virus Auxiliary ToolDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Source Code Anti-Virus Auxiliary Tool.h"
#include "Source Code Anti-Virus Auxiliary ToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSourceCodeAntiVirusAuxiliaryToolDlg 对话框



CSourceCodeAntiVirusAuxiliaryToolDlg::CSourceCodeAntiVirusAuxiliaryToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOURCE_CODE_ANTIVIRUS_AUXILIARY_TOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSourceCodeAntiVirusAuxiliaryToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABLIST, m_TableList);
}

BEGIN_MESSAGE_MAP(CSourceCodeAntiVirusAuxiliaryToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABLIST, &CSourceCodeAntiVirusAuxiliaryToolDlg::OnSelchangeTablist)
//	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSourceCodeAntiVirusAuxiliaryToolDlg 消息处理程序

BOOL CSourceCodeAntiVirusAuxiliaryToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_TableList.InsertItem(0, L"HEX String");
	m_TableList.InsertItem(1, L"HASH String");
	m_TableList.InsertItem(2, L"Dynamic Load");

	m_AsciiToHexStringTable.Create(IDD_HEX_STRINGDIALOG,&m_TableList);
	m_AsciiToHashStringTable.Create(IDD_HASH_STRINGDIALOG, &m_TableList);
	m_DynamicLoadTable.Create(IDD_DYNAMIC_LOAD_DIALOG, &m_TableList);

	CRect rc;
	m_TableList.GetClientRect(&rc);
	rc.DeflateRect(2, 22, 3, 2);
	m_AsciiToHexStringTable.MoveWindow(&rc);
	m_AsciiToHashStringTable.MoveWindow(&rc);
	m_DynamicLoadTable.MoveWindow(&rc);

	m_AsciiToHexStringTable.ShowWindow(SW_SHOW);
	m_AsciiToHashStringTable.ShowWindow(SW_HIDE);
	m_DynamicLoadTable.ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSourceCodeAntiVirusAuxiliaryToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSourceCodeAntiVirusAuxiliaryToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSourceCodeAntiVirusAuxiliaryToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSourceCodeAntiVirusAuxiliaryToolDlg::OnSelchangeTablist(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int CurSel = m_TableList.GetCurSel();
	switch (CurSel)
	{
	case 0:
		m_AsciiToHexStringTable.ShowWindow(true);
		m_AsciiToHashStringTable.ShowWindow(false);
		m_DynamicLoadTable.ShowWindow(false);
		break;
	case 1:
		m_AsciiToHexStringTable.ShowWindow(false);
		m_AsciiToHashStringTable.ShowWindow(true);
		m_DynamicLoadTable.ShowWindow(false);
		break;
	case 2:
		m_AsciiToHexStringTable.ShowWindow(false);
		m_AsciiToHashStringTable.ShowWindow(false);
		m_DynamicLoadTable.ShowWindow(true);
		break;
	default:
		break;
	}
}

