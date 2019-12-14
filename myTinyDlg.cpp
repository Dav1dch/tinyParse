
// myTinyDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "myTiny.h"
#include "myTinyDlg.h"
#include "afxdialogex.h"
#include<fstream>
#include<string>
#include "tiny.h"
using namespace std;

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
public:
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


// CmyTinyDlg 对话框



CmyTinyDlg::CmyTinyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYTINY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyTinyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, filePath);
	DDX_Control(pDX, IDC_EDIT2, sourceCodeEdit);
	DDX_Control(pDX, IDC_EDIT3, treeEdit);
}

BEGIN_MESSAGE_MAP(CmyTinyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(readCode, &CmyTinyDlg::Onreadcode)
	ON_COMMAND(createTree, &CmyTinyDlg::Oncreatetree)
	ON_COMMAND(showTree, &CmyTinyDlg::Onshowtree)
END_MESSAGE_MAP()


// CmyTinyDlg 消息处理程序

void CmyTinyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmyTinyDlg::OnPaint()
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
HCURSOR CmyTinyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmyTinyDlg::Onreadcode()
{
	// TODO: 在此添加命令处理程序代码
	CString path;
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		file_path = path;
		UpdateData(false);
		ifstream file(path);

		if (!file) return;

		char buffer[1024];
		string str = "";
		while (!file.eof())
		{
			file.getline(buffer, 1024);
			str += buffer;
			str += "\r\n";
		}
		s_code = str.c_str();
		filePath.SetWindowTextW(file_path);
		sourceCodeEdit.SetWindowTextW(s_code);
		file.close();
		UpdateData(false);
		//MessageBox(m_input);
	}
	else
	{
		//MessageBox(L"文件选择窗体创建失败");
		return;
	}
}


void CmyTinyDlg::Oncreatetree()
{
	// TODO: 在此添加命令处理程序代码
	ofstream file("./temp.out");
	CString filep;
	sourceCodeEdit.GetWindowTextW(filep);
	for (int i = 0; i < filep.GetLength(); i++) {
		if (filep[i] != '\r')
			file.put(filep[i]);
	}
	file.close();
	tiny("./temp.out", "./tree.out");  //输入路径，输出文件名
	MessageBox(L"生成成功，点击查看即可查看语法树");
}


void CmyTinyDlg::Onshowtree()
{
	// TODO: 在此添加命令处理程序代码
	ifstream file("./tree.out");
	//ifstream file(file_path.c_str());
	if (!file) return;
	char buffer[1024];
	string tree = "";
	while (!file.eof())
	{
		file.getline(buffer, 1024);
		tree += buffer;
		tree += "\r\n";
	}
	tree_text = tree.c_str();
	treeEdit.SetWindowTextW(tree_text);

	file.close();
	UpdateData(false);
}
