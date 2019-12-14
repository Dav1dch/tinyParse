
// myTinyDlg.h: 头文件
//

#pragma once


// CmyTinyDlg 对话框
class CmyTinyDlg : public CDialogEx
{
// 构造
public:
	CmyTinyDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CString file_path;
	CString s_code;
	CString tree_text;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYTINY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog()
	{
		CDialogEx::OnInitDialog();

		// 将“关于...”菜单项添加到系统菜单中。
		CMenu menu;
		menu.LoadMenu(IDR_MENU1);
		SetMenu(&menu);
		

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

		return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
	}
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void Onreadcode();
	afx_msg void Oncreatetree();
	afx_msg void Onshowtree();
	CEdit filePath;
	CEdit sourceCodeEdit;
	CEdit treeEdit;
private:
};
