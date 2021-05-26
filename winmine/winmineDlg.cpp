
// winmineDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "winmine.h"
#include "winmineDlg.h"
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


// CwinmineDlg 对话框



CwinmineDlg::CwinmineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINMINE_DIALOG, pParent)
	, m_showdata(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwinmineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT2, m_showdata);
}

BEGIN_MESSAGE_MAP(CwinmineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CwinmineDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CwinmineDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CwinmineDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CwinmineDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CwinmineDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDOK, &CwinmineDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON6, &CwinmineDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CwinmineDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CwinmineDlg 消息处理程序

BOOL CwinmineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	m_winmineHD = ::FindWindow(NULL, _T("扫雷"));
	if (NULL == m_winmineHD) {
		MessageBox(_T("请先打开扫雷游戏再开该软件"), _T("错误"), MB_OK);
		SendMessage(WM_CLOSE);
	}

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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CwinmineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CwinmineDlg::OnPaint()
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
HCURSOR CwinmineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CwinmineDlg::OnBnClickedButton1()
{
	DWORD pid;
	GetWindowThreadProcessId(m_winmineHD, &pid);
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (NULL == hprocess) {
		MessageBox(TEXT("获取进程失败"), TEXT("错误"), MB_OK);
		SendMessage(WM_CLOSE);
	}
	int lpBuffer;
	ReadProcessMemory(hprocess, (LPCVOID)0x01005194, &lpBuffer, sizeof(lpBuffer), &pid);
	CString str;
	str.Format(_T("%d"), lpBuffer);
	m_edit.SetWindowTextW(str);
}

void CwinmineDlg::OnBnClickedButton4()
{
	this->ToLevel(0x209);
}


void CwinmineDlg::OnBnClickedButton2()
{
	this->ToLevel(0x20A);
}

void CwinmineDlg::OnBnClickedButton3()
{
	this->ToLevel(0x20B);
}


void CwinmineDlg::ToLevel(WPARAM p)
{

	::SendMessage(m_winmineHD, 0x111, p, 0);
}




void CwinmineDlg::OnBnClickedButton5()
{
	DWORD pid;
	GetWindowThreadProcessId(m_winmineHD, &pid);
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (NULL == hprocess) {
		MessageBox(TEXT("获取进程失败"), TEXT("错误"), MB_OK);
		SendMessage(WM_CLOSE);
	}
	CString str;
	m_edit.GetWindowTextW(str);
	int s = _ttoi(str);
	WriteProcessMemory(hprocess, (LPVOID)0x01005194, &s, sizeof(s), &pid);
	m_edit.SetWindowTextW(str);
}


void CwinmineDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CwinmineDlg::OnBnClickedButton6()
{
	DWORD pid;
	unsigned char gameData[24][32] = { 0 };
	HANDLE hprocess;
	CString strtemp = _T("");
	DWORD dwHigth = 0;
	m_showdata = _T("");
	GetWindowThreadProcessId(m_winmineHD, &pid);
	hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (NULL == hprocess) {
		MessageBox(TEXT("获取进程失败"), TEXT("错误"), MB_OK);
		SendMessage(WM_CLOSE);
	}

	if (!ReadProcessMemory(hprocess, (LPVOID)0x01005338, &dwHigth, sizeof(dwHigth), &pid)) {
		MessageBox(TEXT("读取雷区数据错误"), TEXT("错误"), MB_OK);
		return;
	}


	// 扫雷最大24行。32列
	if (!ReadProcessMemory(hprocess, (LPVOID)0x01005361, &gameData, 32 * 24, &pid)) {
		MessageBox(TEXT("读取雷区数据错误"), TEXT("错误"), MB_OK);
		return;
	}


	for (int i = 0; i < dwHigth; ++i) {
		for (int j = 0; i < 32; ++j) {
			if (0x10 == gameData[i][j])
				break;
			strtemp.Format(_T("%02X "), gameData[i][j]);
			m_showdata += strtemp;
		}
		m_showdata += _T("\r\n");
	}

	UpdateData(FALSE);

}


void CwinmineDlg::OnBnClickedButton7()
{
	DWORD pid;
	unsigned char gameData[24][32] = { 0 };
	HANDLE hprocess;
	CString strtemp = _T("");
	DWORD dwHigth = 0;
	m_showdata = _T("");
	short gameX = 20;
	short gameY = 60;
	unsigned short xypos[2] = { 0 };

	GetWindowThreadProcessId(m_winmineHD, &pid);
	hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (NULL == hprocess) {
		MessageBox(TEXT("获取进程失败"), TEXT("错误"), MB_OK);
		SendMessage(WM_CLOSE);
	}

	if (!ReadProcessMemory(hprocess, (LPVOID)0x01005338, &dwHigth, sizeof(dwHigth), &pid)) {
		MessageBox(TEXT("读取雷区数据错误"), TEXT("错误"), MB_OK);
		return;
	}


	// 扫雷最大24行。32列
	if (!ReadProcessMemory(hprocess, (LPVOID)0x01005361, &gameData, 32 * 24, &pid)) {
		MessageBox(TEXT("读取雷区数据错误"), TEXT("错误"), MB_OK);
		return;
	}


	for (int i = 0; i < dwHigth; ++i) {
		for (int j = 0; i < 32; ++j) {
			if (0x10 == gameData[i][j])
				break;

			xypos[0] = gameX + j * 16;
			xypos[1] = gameY + i * 16;
			int p = *(int*)xypos;
			if (0x8F != gameData[i][j]){
				::PostMessage(m_winmineHD, WM_LBUTTONDOWN, MK_LBUTTON, p);
				::PostMessage(m_winmineHD, WM_LBUTTONUP, 0, p);
			}
			strtemp.Format(_T("%02X "), gameData[i][j]);
			m_showdata += strtemp;
		}
		m_showdata += _T("\r\n");
	}

	UpdateData(FALSE);
}
