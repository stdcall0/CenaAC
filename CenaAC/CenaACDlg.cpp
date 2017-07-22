
// CenaACDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CenaAC.h"
#include "CenaACDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void AddLog(CEdit &log, const CString &Text) {
	CString t;
	log.GetWindowTextW(t);
	log.SetWindowTextW(t + Text);
}
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
public:
	int chs;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	chs = 0;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCenaACDlg 对话框



CCenaACDlg::CCenaACDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CENAAC_DIALOG, pParent)
	, m_log()
	, m_uname()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

inline void CCenaACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SAVEAS, m_floder);
	//  DDX_Control(pDX, IDC_USERNAME, m_uname);
	//  DDX_Control(pDX, IDC_LOG, m_log);
	//  DDX_Text(pDX, IDC_LOG, m_log);
	//  DDX_Text(pDX, IDC_USERNAME, m_uname);
	//  DDX_Control(pDX, IDC_LOG, m_log);
	//  DDX_Control(pDX, IDC_USERNAME, m_uname);
	DDX_Control(pDX, IDC_LOG2, m_log);
	//  DDX_Control(pDX, IDC_USERNAME, m_uname);
	//  DDX_Control(pDX, IDC_LOG2, m_prob);
	//  DDX_Control(pDX, IDC_PROb, m_prov);
	DDX_Control(pDX, IDC_PROb, m_prob);
	DDX_Control(pDX, IDC_CHECK1, m_chk);
	DDX_Control(pDX, IDC_LOG2, m_log);
	DDX_Control(pDX, IDOK, m_b);
	DDX_Control(pDX, IDC_CHECK3, m_sub);
	DDX_Control(pDX, IDC_USERNAME3, m_in);
	//  DDX_Control(pDX, IDCANCEL, m_out);
	DDX_Control(pDX, IDC_USERNAME2, m_uname);
	DDX_Control(pDX, IDC_USERNAME, m_out);
}

BEGIN_MESSAGE_MAP(CCenaACDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CCenaACDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCenaACDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_SAVEAS, &CCenaACDlg::OnEnChangeMfceditbrowse1)
	ON_EN_CHANGE(IDC_SAVEAS, &CCenaACDlg::OnEnChangeSaveas)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_LOG2, &CCenaACDlg::OnEnChangeLog2)
	ON_EN_UPDATE(IDC_LOG2, &CCenaACDlg::OnUpdateLog2)
END_MESSAGE_MAP()


// CCenaACDlg 消息处理程序

BOOL CCenaACDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	m_log.SetWindowTextW(CString("[CenaAC 2.0 By 马晨航]\r\n初始化程序...完毕。\r\n"));
	m_uname.SetWindowTextW(CString("CxjyAcOIer"));
	m_floder.SetWindowTextW(CString("C:\\"));
	m_prob.SetWindowTextW(CString("test1;test2"));
	m_chk.SetCheck(1);
	m_chk.EnableWindow(0);
	m_sub.SetCheck(1);
	m_in.SetWindowTextW(CString("in"));
	m_out.SetWindowTextW(CString("out"));
	gen = false;
	SetTimer(2, 5, nullptr);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCenaACDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCenaACDlg::OnPaint()
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
HCURSOR CCenaACDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCenaACDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CCenaACDlg::Process() {}
BOOL WStringToString(const std::wstring &wstr, std::string &str)
{
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');

	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);

	if (nResult == 0)
	{
		return FALSE;
	}

	return TRUE;
}

DWORD _stdcall Process(LPVOID pParam){
	CCenaACDlg* p = (CCenaACDlg*)pParam;
	p->m_b.SetWindowTextW(CString("执行中..."));
	CString dir, x, pl,f; int chs;
	chs = p->m_sub.GetCheck();
	p->m_floder.GetWindowTextW(dir); 
	p->m_uname.GetWindowTextW(x);
	p->m_prob.GetWindowTextW(pl);
	if (pl[pl.GetLength() - 1] == ';') pl.Delete(pl.GetLength() - 1); //Issue #1
	if (dir[dir.GetLength() - 1] != '\\') dir += '\\';
	dir += x;
	AddLog(p->m_log, CString("\r\n[生成日志]\r\n\t保存到：") + dir + "\r\n");
	Sleep(500);
	AddLog(p->m_log, CString("\t题目列表：") + pl + "\r\n");
	Sleep(700);
	AddLog(p->m_log, CString("\t正在解析题目列表"));
	for (int i = 1; i <= 3; i++) {
		Sleep(500);
		AddLog(p->m_log, CString("."));
	}
	AddLog(p->m_log, CString("解析成功！\r\n"));
	Sleep(700);
	CString plist[500], cur = ""; int cnt = 0;
	pl += ";";
	for (int i = 0; i < pl.GetLength(); i++) {
		if (pl[i] == ';') {
			plist[++cnt] = cur;
			cur = "";
		}
		else cur += pl[i];
	}
	AddLog(p->m_log, CString("\t正在创建目录：") + dir);
	for (int i = 1; i <= 3; i++) {
		Sleep(500);
		AddLog(p->m_log, CString("."));
	}
	CString TT = (CString("mkdir \"") + dir + CString("\""));
	std::wstring temp = TT.GetBuffer(0);
	std::string cmd;
	WStringToString(temp, cmd);
	CString inf, ouf;
	p->m_in.GetWindowTextW(inf);
	p->m_out.GetWindowTextW(ouf);
	system((cmd.c_str()));
	AddLog(p->m_log, CString("成功！\r\n"));
	for (int i = 1; i <= cnt; i++) {
		AddLog(p->m_log, CString("\t正在处理题目[") + plist[i] + CString("]"));
		for (int j = 1; j <= 3; j++) {
			Sleep(500);
			AddLog(p->m_log, CString("."));
		}
		CString tmp = "const",fpath="";
		if (chs) tmp += "  SourcePath:string='" + plist[i] + "\\" + plist[i] + "';", fpath = dir + "\\" + plist[i] + "\\" + plist[i] + ".pas";
		else tmp += "  SourcePath:string='" + plist[i] + "';", fpath = dir + "\\" + plist[i] + ".pas";
		tmp += "  InputFile:string='" + plist[i] + "." + inf + "'; OutputFile:string='" + plist[i] + "." + ouf + "';";
		if (chs) {
			CString tdir = dir + "\\" + plist[i];
			string f;
			WStringToString(wstring(tdir), f);
			f = "mkdir \"" + f+"\"";
			system(f.c_str());
		}
		CString code = tmp + p->m_pascode;
		CStdioFile fl;
		fl.Open(fpath, CFile::typeText | CFile::modeCreate | CFile::modeWrite);
		fl.WriteString(code);
		fl.Close();
		AddLog(p->m_log, CString("成功！\r\n"));
	}
	AddLog(p->m_log, CString("生成完毕！\r\n"));
	p->m_b.SetWindowTextW(CString("生成！"));
	p->gen = false;
	return 0;
}
void CCenaACDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (gen) {
		MessageBox(CString("已经开始生成操作！"));
		return;
	}
	gen = true;
	proc = CreateThread(NULL, 0, ::Process, this, 0, NULL);
}


void CCenaACDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCenaACDlg::OnEnChangeSaveas()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}




void CCenaACDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 2) {
		//CEdit * pEdit = &m_log;
		m_log.SetSel(-1);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CCenaACDlg::OnEnChangeLog2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	m_log.SetSel(-1); //MOVE POINTER TO THE LAST
}


void CCenaACDlg::OnUpdateLog2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
	m_log.SetSel(-1);
}
