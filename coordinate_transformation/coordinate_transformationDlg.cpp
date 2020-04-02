
// coordinate_transformationDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "coordinate_transformation.h"
#include "coordinate_transformationDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <iomanip>
#include <cmath>
using namespace Eigen;
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


// CcoordinatetransformationDlg 对话框



CcoordinatetransformationDlg::CcoordinatetransformationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COORDINATE_TRANSFORMATION_DIALOG, pParent)
	, m_path_origin(_T(""))
	, m_path_target(_T(""))
	, m_origin(_T(""))
	, m_target(_T(""))
	, m_result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcoordinatetransformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH_ORIGIN, m_path_origin);
	DDX_Text(pDX, IDC_EDIT_PATH_TARGET, m_path_target);
	DDX_Text(pDX, IDC_EDIT_ORIGIN, m_origin);
	DDX_Text(pDX, IDC_EDIT_TARGET, m_target);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_result);
	DDX_Control(pDX, IDC_PROGRESS1, m_process1);
	DDX_Control(pDX, IDC_PROGRESS2, m_process2);
}

BEGIN_MESSAGE_MAP(CcoordinatetransformationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_PATH_ORIGIN, &CcoordinatetransformationDlg::OnEnChangeEditPathOrigin)
	ON_EN_CHANGE(IDC_EDIT_ORIGIN, &CcoordinatetransformationDlg::OnEnChangeEditOrigin)
	ON_BN_CLICKED(IDC_BUTTON_PATH_ORIGIN, &CcoordinatetransformationDlg::OnBnClickedButtonPathOrigin)
	ON_BN_CLICKED(IDC_BUTTON_PATH_TARGET, &CcoordinatetransformationDlg::OnBnClickedButtonPathTarget)
	ON_BN_CLICKED(IDC_BUTTON1, &CcoordinatetransformationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CcoordinatetransformationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CcoordinatetransformationDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CcoordinatetransformationDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CcoordinatetransformationDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CcoordinatetransformationDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CcoordinatetransformationDlg 消息处理程序

BOOL CcoordinatetransformationDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcoordinatetransformationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcoordinatetransformationDlg::OnPaint()
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
HCURSOR CcoordinatetransformationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcoordinatetransformationDlg::OnEnChangeEditPathOrigin()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CcoordinatetransformationDlg::OnEnChangeEditOrigin()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}







CString filename_origin;//保存路径
//放到函数外面，当全局变量用
void CcoordinatetransformationDlg::OnBnClickedButtonPathOrigin()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CFileDialog opendlg(TRUE, _T("*"), _T("*.xyz"), OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (opendlg.DoModal() == IDOK)
	{
		filename_origin = opendlg.GetPathName();
	}
	//显示传入地址
	m_path_origin = filename_origin;
	UpdateData(FALSE);	
}

CString filename_target;//保存路径
void CcoordinatetransformationDlg::OnBnClickedButtonPathTarget()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog opendlg(TRUE, _T("*"), _T("*.xyz"), OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (opendlg.DoModal() == IDOK)
	{
		filename_target = opendlg.GetPathName();
	}
	//显示目标地址
	m_path_target = filename_target;
	UpdateData(FALSE);
}

//四参数坐标转换
void CcoordinatetransformationDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码	
	//读取源文件放进矩阵
	ifstream infile;
	infile.open(filename_origin);
	char data1[100];
	//以double放进了矩阵
	MatrixXd m1(8, 3);

	//设置进度条长度
	m_process1.SetRange(0, 10);
	//设置进度条每一次进度
	m_process1.SetStep(10);
	//设置进度条长度
	m_process2.SetRange(0, 10);
	//设置进度条每一次进度
	m_process2.SetStep(10);
	for (int i = 0; i < 8; i++)
	{
		infile >> data1;
		//这里是把字符串分割的代码
		char x_1[11];
		char y_1[11];
		char z_1[6];
		x_1[10] = NULL;
		y_1[10] = NULL;
		z_1[5] = NULL;
		for (int i2 = 0; i2 < 10; i2++)
		{
			x_1[i2] = data1[i2 + 5];
			y_1[i2] = data1[i2 + 16];
		}
		for (int i3 = 0; i3 < 5; i3++)
		{
			z_1[i3] = data1[i3 + 27];
		}

		string x1_1 = x_1;
		string y1_1 = y_1;
		string z1_1 = z_1;

		double x2_1 = stod(x1_1);
		double y2_1 = stod(y1_1);
		double z2_1 = stod(z1_1);

		m1(i, 0) = x2_1;
		m1(i, 1) = y2_1;
		m1(i, 2) = z2_1;

		CString str;
		str.Format(_T("%lf"), x2_1);
		m_origin = m_origin + str;
		str.Format(_T("%lf"), y2_1);
		m_origin = m_origin + " " + str;
		str.Format(_T("%lf"), z2_1);
		m_origin = m_origin + " " + str;
		m_origin += "\r\n";


		UpdateData(FALSE);

	}


	//读取目标文件放进矩阵
	ifstream infile1;
	infile1.open(filename_target);
	char data2[100];
	//以double放进了矩阵
	MatrixXd m2(8, 3);
	for (int i_2 = 0; i_2 < 8; i_2++)
	{
		infile1 >> data2;
		//这里是把字符串分割的代码
		char x_2[12];
		char y_2[13];
		char z_2[6];
		x_2[11] =NULL;
		y_2[12] = NULL;
		z_2[5] = NULL ;
		for (int i2_2 = 0; i2_2 < 11; i2_2++)
		{
			x_2[i2_2] = data2[i2_2 + 5];			
		}
		for (int i2_2 = 0; i2_2 < 12; i2_2++)
		{
			y_2[i2_2] = data2[i2_2 + 17];
		}
		for (int i3_2 = 0; i3_2 < 5; i3_2++)
		{
			z_2[i3_2] = data2[i3_2 + 30];
		}

		string x1_2 = x_2;
		string y1_2 = y_2;
		string z1_2 = z_2;

		double x2_2 = stod(x1_2);
		double y2_2 = stod(y1_2);
		double z2_2 = stod(z1_2);

		m2(i_2, 0) = x2_2;
		m2(i_2, 1) = y2_2;
		m2(i_2, 2) = z2_2;

		CString str;
		str.Format(_T("%lf"), x2_2);
		m_target = m_target + str;
		str.Format(_T("%lf"), y2_2);
		m_target = m_target + " " + str;
		str.Format(_T("%lf"), z2_2);
		m_target = m_target + " " + str;
		m_target += "\r\n";


		UpdateData(FALSE);

	}

	//开始构造B矩阵
	MatrixXd B_1(8, 4);
	for (int i = 0; i < 4; i ++ )
	{
		B_1(2 * i , 0) = 1;
		B_1(2 * i , 1) = 0;
		B_1(2 * i , 2) = m1(i,1);
		B_1(2 * i , 3) = m1(i,0);
		B_1(2 * i + 1, 0) = 0;
		B_1(2 * i + 1, 1) = 1;
		B_1(2 * i + 1, 2) = -1*m1(i, 0);
		B_1(2 * i + 1, 3) = m1(i, 1);
	}
	//开始构造L矩阵
	MatrixXd L_1(8, 1);
	for (int i = 0; i < 4; i++)
	{
		L_1(2 * i , 0) = -m1(i, 0)+ m2(i, 0);
		L_1(2 * i + 1 , 0) = -m1(i, 1) + m2(i, 1);
	}

	//构建X矩阵
	MatrixXd X_1(4, 1);
	X_1 = (B_1.transpose()*B_1).inverse()*B_1.transpose()*L_1;

	//构建V矩阵
	MatrixXd V_1(8, 1);
	V_1 = B_1 * X_1 - L_1;
	//单位权中误差
	double sigma_1;
	sigma_1 = sqrt((V_1.transpose()*V_1)(0,0) / 4);

	//准备用得到的结果估计
	//创建整体的估计b矩阵
	MatrixXd b_1(18, 4);
	for (int i = 0; i < 8; i++)
	{
		b_1(2 * i, 0) = 1;
		b_1(2 * i, 1) = 0;
		b_1(2 * i, 2) = m1(i, 1);
		b_1(2 * i, 3) = m1(i, 0);
		b_1(2 * i + 1, 0) = 0;
		b_1(2 * i + 1, 1) = 1;
		b_1(2 * i + 1, 2) = -1 * m1(i, 0);
		b_1(2 * i + 1, 3) = m1(i, 1);
	}
	//最后一个坐标与自己的学号有关
	//点(115***.237 , 118***.826 , 0.000),***是学号
	//即(115032.237 , 118032.826 , 0.000)
	b_1(16, 0) = 1;
	b_1(16, 1) = 0;
	b_1(16, 2) = 118032.826;
	b_1(16, 3) = 115032.237;
	b_1(17, 0) = 0;
	b_1(17, 1) = 1;
	b_1(17, 2) = -115032.237;
	b_1(17, 3) = 118032.826;
	//创建整体估计的l矩阵
	MatrixXd l_1(18, 1);
	for (int i = 0; i < 8; i++)
	{
		l_1(2 * i, 0) = m1(i, 0);
		l_1(2 * i + 1, 0) = m1(i, 1);		
	}
	l_1(16, 0) = 115032.237;
	l_1(17, 0) = 118032.826;
	//创建估计值矩阵theta
	MatrixXd theta_1(18, 1);
	theta_1 = b_1 * X_1 + l_1;

	//创建8个点的残差矩阵sigma1
	//残差为估计减去实际
	MatrixXd sigma1_1(16, 1);
	for (int i = 0; i < 8; i++)
	{	
		sigma1_1(2*i, 0) = theta_1(2*i, 0)- m2(i, 0);
		sigma1_1(2*i+1, 0) = theta_1(2*i+1, 0)- m2(i, 1);
	}
	//做好了之后就直接让进度条完成
	m_process1.StepIt();
	m_process2.StepIt();

	//输出结果
	CString str;
	m_result += "***************转换参数***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), X_1(0, 0));
	m_result = m_result + "计算得到的DX为："+ str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_1(1, 0));
	m_result = m_result + "计算得到的DY为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_1(2, 0));
	m_result = m_result + "计算得到的DR为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_1(3, 0));
	m_result = m_result + "计算得到的DK为：" + str;
	m_result += "\r\n";
	m_result += "***************条件数与冗余度***************";
	m_result += "\r\n";
	m_result += "条件数n为8，冗余度r为4";
	m_result += "\r\n";
	m_result += "***************单位权中误差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma_1);
	m_result = m_result + "单位权中误差为：" + str;
	m_result += "\r\n";
	m_result += "***************四个公共点的残差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_1(0, 0));
	m_result = m_result + "  " + str ;
	str.Format(_T("%lf"), sigma1_1(1, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_1(2, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_1(3, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_1(4, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_1(5, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_1(6, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_1(7, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	m_result += "***************检核点坐标残差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_1(8, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_1(9, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_1(10, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_1(11, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_1(12, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_1(13, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_1(14, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_1(15, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	m_result += "***************学号对应坐标的转换结果***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), theta_1(16, 0));
	m_result = m_result +  str;
	m_result += "\r\n";
	str.Format(_T("%lf"), theta_1(17, 0));
	m_result = m_result +  str;
	m_result += "\r\n";
	UpdateData(FALSE);
}

//七参数/六参数坐标转换
void CcoordinatetransformationDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码	
	//设置进度条长度
	m_process1.SetRange(0, 10);
	//设置进度条每一次进度
	m_process1.SetStep(10);
	//设置进度条长度
	m_process2.SetRange(0, 10);
	//设置进度条每一次进度
	m_process2.SetStep(10);
	//读取源文件放进矩阵
	ifstream infile;
	infile.open(filename_origin);
	char data1[100];
	//以double放进了矩阵
	MatrixXd m1(6, 3);
	for (int i = 0; i < 6; i++)
	{
		infile >> data1;
		//这里是把字符串分割的代码
		char x_1[14];//13个元素加空
		char y_1[13];//12个元素加空
		char z_1[13];//12个元素加空
		x_1[13] = NULL;
		y_1[12] = NULL;
		z_1[2] = NULL;
		for (int i2 = 0; i2 < 13; i2++)
		{
			x_1[i2] = data1[i2 + 2];			
		}
		for (int i3 = 0; i3 < 12; i3++)
		{
			y_1[i3] = data1[i3 + 16];
			z_1[i3] = data1[i3 + 29];
		}

		string x1_1 = x_1;
		string y1_1 = y_1;
		string z1_1 = z_1;

		double x2_1 = stod(x1_1);
		double y2_1 = stod(y1_1);
		double z2_1 = stod(z1_1);

		m1(i, 0) = x2_1;
		m1(i, 1) = y2_1;
		m1(i, 2) = z2_1;

		CString str;
		str.Format(_T("%lf"), x2_1);
		m_origin = m_origin + str;
		str.Format(_T("%lf"), y2_1);
		m_origin = m_origin + " " + str;
		str.Format(_T("%lf"), z2_1);
		m_origin = m_origin + " " + str;
		m_origin += "\r\n";


		UpdateData(FALSE);

	}

	//读取目标文件放进矩阵
	ifstream infile1;
	infile1.open(filename_target);
	char data2[100];
	//以double放进了矩阵
	MatrixXd m2(6, 3);
	for (int i_2 = 0; i_2 < 6; i_2++)
	{
		infile1 >> data2;
		//这里是把字符串分割的代码
		char x_2[14];//13个元素加空
		char y_2[13];//12个元素加空
		char z_2[13];//12个元素加空
		x_2[13] = NULL;
		y_2[12] = NULL;
		z_2[2] = NULL;
		for (int i2 = 0; i2 < 13; i2++)
		{
			x_2[i2] = data2[i2 + 2];
		}
		for (int i3 = 0; i3 < 12; i3++)
		{
			y_2[i3] = data2[i3 + 16];
			z_2[i3] = data2[i3 + 29];
		}

		string x1_2 = x_2;
		string y1_2 = y_2;
		string z1_2 = z_2;

		double x2_2 = stod(x1_2);
		double y2_2 = stod(y1_2);
		double z2_2 = stod(z1_2);

		m2(i_2, 0) = x2_2;
		m2(i_2, 1) = y2_2;
		m2(i_2, 2) = z2_2;

		CString str;
		str.Format(_T("%lf"), x2_2);
		m_target = m_target + str;
		str.Format(_T("%lf"), y2_2);
		m_target = m_target + " " + str;
		str.Format(_T("%lf"), z2_2);
		m_target = m_target + " " + str;
		m_target += "\r\n";


		UpdateData(FALSE);

	}

	//开始构造B矩阵
	MatrixXd B_2(12, 7);
	for (int i = 0; i < 4; i++)
	{
		B_2(3 * i, 0) = 1;
		B_2(3 * i, 1) = 0;
		B_2(3 * i, 2) = 0;
		B_2(3 * i, 3) = 0;
		B_2(3 * i, 4) = -m1(i,2);
		B_2(3 * i, 5) = m1(i, 1);
		B_2(3 * i, 6) = m1(i, 0);
		B_2(3 * i + 1, 0) = 0;
		B_2(3 * i + 1, 1) = 1;
		B_2(3 * i + 1, 2) = 0;
		B_2(3 * i + 1, 3) = m1(i, 2);
		B_2(3 * i + 1, 4) = 0;
		B_2(3 * i + 1, 5) = -m1(i, 0);
		B_2(3 * i + 1, 6) = m1(i, 1);
		B_2(3 * i + 2, 0) = 0;
		B_2(3 * i + 2, 1) = 0;
		B_2(3 * i + 2, 2) = 1;
		B_2(3 * i + 2, 3) = -m1(i, 1);
		B_2(3 * i + 2, 4) = m1(i, 0);
		B_2(3 * i + 2, 5) = 0;
		B_2(3 * i + 2, 6) = m1(i, 2);
	}
	//开始构造L矩阵
	MatrixXd L_2(12, 1);
	for (int i = 0; i < 4; i++)
	{
		L_2(3 * i, 0) = m2(i, 0) - m1(i, 0);
		L_2(3 * i + 1, 0) = m2(i, 1) - m1(i, 1);
	    L_2(3 * i + 2, 0) = m2(i, 2) - m1(i, 2);
	}
	//构建X矩阵
	MatrixXd X_2(7, 1);
	X_2 = (B_2.transpose()*B_2).inverse()*B_2.transpose()*L_2;
	//构建V矩阵
	MatrixXd V_2(12, 1);
	V_2 = B_2 * X_2 - L_2;
	//单位权中误差
	double sigma_2;
	sigma_2 = sqrt((V_2.transpose()*V_2)(0, 0) / 5);

	//准备用得到的结果估计
	//创建整体的估计b矩阵
	MatrixXd b_2(21, 7);
	for (int i = 0; i < 6; i++)
	{
		b_2(3 * i, 0) = 1;
		b_2(3 * i, 1) = 0;
		b_2(3 * i, 2) = 0;
		b_2(3 * i, 3) = 0;
		b_2(3 * i, 4) = -m1(i, 2);
		b_2(3 * i, 5) = m1(i, 1);
		b_2(3 * i, 6) = m1(i, 0);
		b_2(3 * i + 1, 0) = 0;
		b_2(3 * i + 1, 1) = 1;
		b_2(3 * i + 1, 2) = 0;
		b_2(3 * i + 1, 3) = m1(i, 2);
		b_2(3 * i + 1, 4) = 0;
		b_2(3 * i + 1, 5) = -m1(i, 0);
		b_2(3 * i + 1, 6) = m1(i, 1);
		b_2(3 * i + 2, 0) = 0;
		b_2(3 * i + 2, 1) = 0;
		b_2(3 * i + 2, 2) = 1;
		b_2(3 * i + 2, 3) = -m1(i, 1);
		b_2(3 * i + 2, 4) = m1(i, 0);
		b_2(3 * i + 2, 5) = 0;
		b_2(3 * i + 2, 6) = m1(i, 2);
	}
	//最后一个坐标与自己的学号有关
	//(-2100***.2849 , 5496***.0138 , 2894***.6030)（“***”为学号后三位）
	//即(-2100032.2849 , 5496032.0138  , 2894032.6030)
	b_2(18, 0) = 1;
	b_2(18, 1) = 0;
	b_2(18, 2) = 0;
	b_2(18, 3) = 0;
	b_2(18, 4) = -2894032.6030;
	b_2(18, 5) = 5496032.0138;
	b_2(18, 6) = -2100032.2849;
	b_2(19, 0) = 0;
	b_2(19, 1) = 1;
	b_2(19, 2) = 0;
	b_2(19, 3) = 2894032.6030;
	b_2(19, 4) = 0;
	b_2(19, 5) = 2100032.2849;
	b_2(19, 6) = 5496032.0138;
	b_2(20, 0) = 0;
	b_2(20, 1) = 0;
	b_2(20, 2) = 1;
	b_2(20, 3) = -5496032.0138;
	b_2(20, 4) = -2100032.2849;
	b_2(20, 5) = 0;
	b_2(20, 6) = 2894032.6030;
	//创建整体估计的l矩阵
	MatrixXd l_2(21, 1);
	for (int i = 0; i < 6; i++)
	{
		l_2(3 * i, 0) = m1(i, 0);
		l_2(3 * i + 1, 0) = m1(i, 1);
		l_2(3 * i + 2, 0) = m1(i, 2);
	}
	l_2(18, 0) = -2100032.2849;
	l_2(19, 0) = 5496032.0138;
	l_2(20, 0) = 2894032.6030;
	//创建估计值矩阵theta
	MatrixXd theta_2(21, 1);
	theta_2 = b_2 * X_2 + l_2;

	//创建6个点的残差矩阵sigma1
	//残差估计减去实际
	MatrixXd sigma1_2(18, 1);
	for (int i = 0; i < 6; i++)
	{
		sigma1_2(3 * i, 0) = theta_2(3 * i, 0)- m2(i, 0);
		sigma1_2(3 * i + 1, 0) =  theta_2(3 * i + 1, 0)- m2(i, 1);
		sigma1_2(3 * i + 2, 0) =  theta_2(3 * i + 2, 0)- m2(i, 2);
	}
	//做好了之后就直接让进度条完成
	m_process1.StepIt();
	m_process2.StepIt();

	//输出结果
	CString str;
	m_result += "***************转换参数***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), X_2(0, 0));
	m_result = m_result + "计算得到的DX为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_2(1, 0));
	m_result = m_result + "计算得到的DY为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_2(2, 0));
	m_result = m_result + "计算得到的DR为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_2(3, 0));
	m_result = m_result + "计算得到的RX为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_2(4, 0));
	m_result = m_result + "计算得到的RY为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_2(5, 0));
	m_result = m_result + "计算得到的RZ为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_2(6, 0));
	m_result = m_result + "计算得到的DK为：" + str;
	m_result += "\r\n";
	m_result += "***************条件数与冗余度***************";
	m_result += "\r\n";
	m_result += "条件数n为12，冗余度r为5";
	m_result += "\r\n";
	m_result += "***************单位权中误差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma_2);
	m_result = m_result + "单位权中误差为：" + str;
	m_result += "\r\n";
	m_result += "***************四个公共点的残差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_2(0, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(1, 0));
	m_result = m_result + "  " + str;	
	str.Format(_T("%lf"), sigma1_2(2, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_2(3, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(4, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(5, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_2(6, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(7, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(8, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_2(9, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(10, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(11, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	m_result += "***************检核点坐标残差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_2(12, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(13, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(14, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_2(15, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(16, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_2(17, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	m_result += "***************学号对应坐标的转换结果***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), theta_2(18, 0));
	m_result = m_result + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), theta_2(19, 0));
	m_result = m_result + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), theta_2(20, 0));
	m_result = m_result + str;
	m_result += "\r\n";
	UpdateData(FALSE);
}

//十三参数坐标转换
void CcoordinatetransformationDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//设置进度条长度
	m_process1.SetRange(0, 10);
	//设置进度条每一次进度
	m_process1.SetStep(10);
	//设置进度条长度
	m_process2.SetRange(0, 10);
	//设置进度条每一次进度
	m_process2.SetStep(10);
	//读取源文件放进矩阵
	ifstream inf;
	inf.open(filename_origin, ifstream::in);
	MatrixXd m1(17, 3);
	CString str_1;
	const int cnt_1 = 4;
	string line_1;
	double z_1 = 0;
	int j_1 = 0;
	//用来计数小循环
	int k_1 = 0;
	//用来计数大循环
	size_t comma_1 = 0;
	size_t comma2_1 = 0;

	while (!inf.eof())//当不是文件末尾的时候
	{
		getline(inf, line_1);
		comma_1 = line_1.find(',', 0);
		z_1 = atof(line_1.substr(0, comma_1).c_str());
		//点号不作处理
		while (comma_1 < line_1.size() && j_1 != cnt_1 - 1)
		{
			comma2_1 = line_1.find(',', comma_1 + 1);
			z_1 = atof(line_1.substr(comma_1 + 1, comma2_1 - comma_1 - 1).c_str());			
		    m1(k_1, j_1) = z_1;		
			//往矩阵里面放东西
			++j_1;
			
			str_1.Format(_T("%lf"), z_1);
			m_origin = m_origin + " " + str_1;
			
			comma_1 = comma2_1;
			if (j_1 == 3)
			{
				k_1++;
				m_origin += "\r\n";
			}
		}
		cout << endl;
		j_1 = 0;
	}
	inf.close();
	UpdateData(FALSE);

	//读取目标文件放进矩阵
	inf.open(filename_target, ifstream::in);
	MatrixXd m2(17, 3);
	CString str_2;
	const int cnt_2 = 4;
	string line_2;
	double z_2 = 0;
	int j_2 = 0;
	//用来计数小循环
	int k_2 = 0;
	//用来计数大循环
	size_t comma_2 = 0;
	size_t comma2_2 = 0;

	while (!inf.eof())//当不是文件末尾的时候
	{
		getline(inf, line_2);
		comma_2 = line_2.find(',', 0);
		z_2 = atof(line_2.substr(0, comma_2).c_str());
		//点号不作处理
		while (comma_2 < line_2.size() && j_2 != cnt_2 - 1)
		{
			comma2_2 = line_2.find(',', comma_2 + 1);
			z_2 = atof(line_2.substr(comma_2 + 1, comma2_2 - comma_2 - 1).c_str());
			m2(k_2, j_2) = z_2;
			//往矩阵里面放东西
			++j_2;

			str_2.Format(_T("%lf"), z_2);
			m_target = m_target + " " + str_2;

			comma_2 = comma2_2;
			if (j_2 == 3)
			{
				k_2++;
				m_target += "\r\n";
			}
		}
		cout << endl;
		j_2 = 0;
	}
	inf.close();
	UpdateData(FALSE);




	//开始构建计算程序
	//构建初始近似值
	//构建未知数的矩阵
	MatrixXd X_all(13, 1);
	//前三个是平移尺度X，Y，Z
	X_all(0, 0) = 0;
	X_all(1, 0) = 0;
	X_all(2, 0) = 0;
	//第四个是尺度参数μ
	X_all(3, 0) = 1;
	//后九个是旋转参数
	X_all(4, 0) = 1;
	X_all(5, 0) = 0;
	X_all(6, 0) = 0;
	X_all(7, 0) = 0;
	X_all(8, 0) = 1;
	X_all(9, 0) = 0;
	X_all(10, 0) = 0;
	X_all(11, 0) = 0;
	X_all(12, 0) = 1;
	//单位权中误差
	double sigma_3;
	//循环体系开始
	for (int i = 0; i < 1;)
	{
		//构建μ，尺度参数
		double μ = X_all(3, 0);
		//构建X矩阵，平移参数
		MatrixXd X_3(3, 1);
		X_3(0, 0) = X_all(0, 0);
		X_3(1, 0) = X_all(1, 0);
		X_3(2, 0) = X_all(2, 0);
		//构建M矩阵，旋转参数
		MatrixXd M(3, 3);
		M(0, 0) = X_all(4, 0);
		M(0, 1) = X_all(5, 0);
		M(0, 2) = X_all(6, 0);
		M(1, 0) = X_all(7, 0);
		M(1, 1) = X_all(8, 0);
		M(1, 2) = X_all(9, 0);
		M(2, 0) = X_all(10, 0);
		M(2, 1) = X_all(11, 0);
		M(2, 2) = X_all(12, 0);
		double a1 = M(0, 0);
		double a2 = M(0, 1);
		double a3 = M(0, 2);
		double b1 = M(1, 0);
		double b2 = M(1, 1);
		double b3 = M(1, 2);
		double c1 = M(2, 0);
		double c2 = M(2, 1);
		double c3 = M(2, 2);

		//构建误差方程
		//一共有11个点是转换公共点
		//构建A矩阵
		MatrixXd A_3(33, 13);
		for (int i = 0; i < 11; i++)
		{
			A_3(3 * i, 0) = 1;
			A_3(3 * i, 1) = 0;
			A_3(3 * i, 2) = 0;
			A_3(3 * i, 3) = a1 * m1(i, 0) + a2 * m1(i, 1) + a3 * m1(i, 2);
			A_3(3 * i, 4) = μ * m1(i, 0);
			A_3(3 * i, 5) = μ * m1(i, 1);
			A_3(3 * i, 6) = μ * m1(i, 2);
			A_3(3 * i, 7) = 0;
			A_3(3 * i, 8) = 0;
			A_3(3 * i, 9) = 0;
			A_3(3 * i, 10) = 0;
			A_3(3 * i, 11) = 0;
			A_3(3 * i, 12) = 0;
			A_3(3 * i + 1, 0) = 0;
			A_3(3 * i + 1, 1) = 1;
			A_3(3 * i + 1, 2) = 0;
			A_3(3 * i + 1, 3) = b1 * m1(i, 0) + b2 * m1(i, 1) + b3 * m1(i, 2);
			A_3(3 * i + 1, 4) = 0;
			A_3(3 * i + 1, 5) = 0;
			A_3(3 * i + 1, 6) = 0;
			A_3(3 * i + 1, 7) = μ * m1(i, 0);
			A_3(3 * i + 1, 8) = μ * m1(i, 1);
			A_3(3 * i + 1, 9) = μ * m1(i, 2);
			A_3(3 * i + 1, 10) = 0;
			A_3(3 * i + 1, 11) = 0;
			A_3(3 * i + 1, 12) = 0;
			A_3(3 * i + 2, 0) = 0;
			A_3(3 * i + 2, 1) = 0;
			A_3(3 * i + 2, 2) = 1;
			A_3(3 * i + 2, 3) = c1 * m1(i, 0) + c2 * m1(i, 1) + c3 * m1(i, 2);
			A_3(3 * i + 2, 4) = 0;
			A_3(3 * i + 2, 5) = 0;
			A_3(3 * i + 2, 6) = 0;
			A_3(3 * i + 2, 7) = 0;
			A_3(3 * i + 2, 8) = 0;
			A_3(3 * i + 2, 9) = 0;
			A_3(3 * i + 2, 10) = μ * m1(i, 0);
			A_3(3 * i + 2, 11) = μ * m1(i, 1);
			A_3(3 * i + 2, 12) = μ * m1(i, 2);
		}
		//构建L矩阵
		MatrixXd L_3(33, 1);
		for (int i = 0; i < 11; i++)
		{
			L_3(3 * i, 0) = X_3(0, 0) + μ * (a1*m1(i, 0) + a2 * m1(i, 1) + a3 * m1(i, 2)) - m2(i, 0);
			L_3(3 * i + 1, 0) = X_3(1, 0) + μ * (b1*m1(i, 0) + b2 * m1(i, 1) + b3 * m1(i, 2)) - m2(i, 1);
			L_3(3 * i + 2, 0) = X_3(2, 0) + μ * (c1*m1(i, 0) + c2 * m1(i, 1) + c3 * m1(i, 2)) - m2(i, 2);
		}

		//构建条件方程
		//可以组成六个条件方程
		//构建B矩阵
		MatrixXd B_3(6, 13);
		B_3.fill(0);
		//先全部设为0，再看情况往里面填充
		B_3(0, 4) = 2 * a1;
		B_3(0, 5) = 2 * a2;
		B_3(0, 6) = 2 * a3;
		B_3(1, 7) = 2 * b1;
		B_3(1, 8) = 2 * b2;
		B_3(1, 9) = 2 * b3;
		B_3(2, 10) = 2 * c1;
		B_3(2, 11) = 2 * c2;
		B_3(2, 12) = 2 * c3;
		B_3(3, 4) = a2;
		B_3(3, 5) = a1;
		B_3(3, 7) = b2;
		B_3(3, 8) = b1;
		B_3(3, 10) = c2;
		B_3(3, 11) = c1;
		B_3(4, 4) = a3;
		B_3(4, 6) = a1;
		B_3(4, 7) = b3;
		B_3(4, 9) = b1;
		B_3(4, 10) = c3;
		B_3(4, 12) = c1;
		B_3(5, 5) = a3;
		B_3(5, 6) = a2;
		B_3(5, 8) = b3;
		B_3(5, 9) = b2;
		B_3(5, 11) = c3;
		B_3(5, 12) = c2;
		//构建W矩阵
		MatrixXd W_3(6, 1);
		W_3(0, 0) = pow(a1, 2) + pow(a2, 2) + pow(a3, 2) - 1;
		W_3(1, 0) = pow(b1, 2) + pow(b2, 2) + pow(b3, 2) - 1;
		W_3(2, 0) = pow(c1, 2) + pow(c2, 2) + pow(c3, 2) - 1;
		W_3(3, 0) = a1 * a2 + b1 * b2 + c1 * c2;
		W_3(4, 0) = a1 * a3 + b1 * b3 + c1 * c3;
		W_3(5, 0) = a3 * a2 + b3 * b2 + c3 * c2;

		//计算未知数最新值
		//按照论文构建大的B和L
		MatrixXd B_all(39, 13);
		B_all << A_3,
			B_3;
		MatrixXd L_all(39, 1);
		L_all << L_3,
			W_3;
		//构建并计算x矩阵
		MatrixXd x_3(13, 1);
		x_3 = (B_all.transpose()*B_all).inverse()*B_all.transpose()*(-1 * L_all);
		//将改正值加到原来的值上
		X_all = X_all + x_3;
		//构建V矩阵
		MatrixXd V_3(39, 1);
		V_3 = B_all * x_3 + L_all;
		//赋值单位权中误差
		sigma_3 = sqrt((V_3.transpose()*V_3)(0, 0) / 24);
		double comp = (x_3.transpose()*x_3)(0,0);
		if (comp < 0.0000001)
		{
			i++;
			//满足则跳出循环
		}
	}


	//准备用得到的结果估计
	//创建整体的估计k
	double k_3= X_all(3, 0);
	//创建整体的估计b矩阵
	MatrixXd B_estimate(3, 3);
		B_estimate(0, 0) = X_all(4, 0);
		B_estimate(0, 1) = X_all(5, 0);
		B_estimate(0, 2) = X_all(6, 0);
		B_estimate(1, 0) = X_all(7, 0);
		B_estimate(1, 1) = X_all(8, 0);
		B_estimate(1, 2) = X_all(9, 0);
		B_estimate(2, 0) = X_all(10, 0);
		B_estimate(2, 1) = X_all(11, 0);
		B_estimate(2, 2) = X_all(12, 0);
	//创建整体的估计L矩阵
	MatrixXd L_estimate(3, 1);
		L_estimate(0, 0) = X_all(0, 0);
		L_estimate(1, 0) = X_all(1, 0);
		L_estimate(2, 0) = X_all(2, 0);	
	//创建整体的初始值x_origin_3矩阵
	MatrixXd x_origin_3(51, 1);
	for (int i = 0; i < 17; i++)
	{
		x_origin_3(3 * i, 0) = m1(i, 0);
		x_origin_3(3 * i + 1, 0) = m1(i, 1);
		x_origin_3(3 * i + 2, 0) = m1(i, 2);
	}	
	//创建整体的实际转换值x_target_3矩阵
	MatrixXd x_target_3(51, 1);
	for (int i = 0; i < 17; i++)
	{
		x_target_3(3 * i, 0) = m2(i, 0);
		x_target_3(3 * i + 1, 0) = m2(i, 1);
		x_target_3(3 * i + 2, 0) = m2(i, 2);
	}
	//创建整体的估计值矩阵theta
	MatrixXd theta_3(51, 1);
	//进行循环整体估计
	for (int i = 0; i < 17; i++)
	{
		//创建一个点一组的暂用转换矩阵
		MatrixXd temp_3(3, 1);
		temp_3(0, 0) = x_origin_3(3 * i, 0);
		temp_3(1, 0) = x_origin_3(3 * i + 1, 0);
		temp_3(2, 0) = x_origin_3(3 * i + 2, 0);
		//创建一个点一组的暂用转换结果矩阵
		MatrixXd temp_r_3(3, 1);
		temp_r_3 = k_3 * B_estimate*temp_3 + L_estimate;
		theta_3(3 * i, 0) = temp_r_3(0, 0);
		theta_3(3 * i + 1, 0) = temp_r_3(1, 0);
		theta_3(3 * i + 2, 0) = temp_r_3(2, 0);
	}

	//创建17个点的残差矩阵sigma1
	MatrixXd sigma1_3(51, 1);
	//残差估计减去实际
	sigma1_3 = theta_3- x_target_3;

	//做好了之后就直接让进度条完成
	m_process1.StepIt();
	m_process2.StepIt();

	//输出结果
	CString str;
	m_result += "***************转换参数***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(0, 0));
	m_result = m_result + "计算得到的dX0为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(1, 0));
	m_result = m_result + "计算得到的dY0为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(2, 0));
	m_result = m_result + "计算得到的dZ0为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(3, 0));
	m_result = m_result + "计算得到的dμ为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(4, 0));
	m_result = m_result + "计算得到的da1为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(5, 0));
	m_result = m_result + "计算得到的da2为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(6, 0));
	m_result = m_result + "计算得到的da3为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(7, 0));
	m_result = m_result + "计算得到的db1为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(8, 0));
	m_result = m_result + "计算得到的db2为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(9, 0));
	m_result = m_result + "计算得到的db3为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(10, 0));
	m_result = m_result + "计算得到的dc1为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(11, 0));
	m_result = m_result + "计算得到的dc2为：" + str;
	m_result += "\r\n";
	str.Format(_T("%lf"), X_all(12, 0));
	m_result = m_result + "计算得到的dc3为：" + str;
	m_result += "\r\n";
	m_result += "***************条件数与冗余度***************";
	m_result += "\r\n";
	m_result += "条件数n为33，冗余度r为24";
	m_result += "\r\n";
	m_result += "***************单位权中误差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma_3);
	m_result = m_result + "单位权中误差为：" + str;
	m_result += "\r\n";
	m_result += "***************十一个公共点的残差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_3(0, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(1, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(2, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//一个点输出
	str.Format(_T("%lf"), sigma1_3(3, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(4, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(5, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//两个点输出
	str.Format(_T("%lf"), sigma1_3(6, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(7, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(8, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//三个点输出
	str.Format(_T("%lf"), sigma1_3(9, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(10, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(11, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//四个点输出
	str.Format(_T("%lf"), sigma1_3(12, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(13, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(14, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//五个点输出
	str.Format(_T("%lf"), sigma1_3(15, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(16, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(17, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//六个点输出
	str.Format(_T("%lf"), sigma1_3(18, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(19, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(20, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//七个点输出
	str.Format(_T("%lf"), sigma1_3(21, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(22, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(23, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//八个点输出
	str.Format(_T("%lf"), sigma1_3(24, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(25, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(26, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//九个点输出
	str.Format(_T("%lf"), sigma1_3(27, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(28, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(29, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//十个点输出
	str.Format(_T("%lf"), sigma1_3(30, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(31, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(32, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//十一个点输出
	m_result += "***************六个检核点坐标残差***************";
	m_result += "\r\n";
	str.Format(_T("%lf"), sigma1_3(33, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(34, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(35, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//一个检验点输出
	str.Format(_T("%lf"), sigma1_3(36, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(37, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(38, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//两个检验点输出
	str.Format(_T("%lf"), sigma1_3(39, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(40, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(41, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//三个检验点输出
	str.Format(_T("%lf"), sigma1_3(42, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(43, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(44, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//四个检验点输出
	str.Format(_T("%lf"), sigma1_3(45, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(46, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(47, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//五个检验点输出
	str.Format(_T("%lf"), sigma1_3(48, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(49, 0));
	m_result = m_result + "  " + str;
	str.Format(_T("%lf"), sigma1_3(50, 0));
	m_result = m_result + "  " + str;
	m_result += "\r\n";
	//六个检验点输出
	UpdateData(FALSE);
}

//地心地固系与大地坐标系转换
void CcoordinatetransformationDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//读取源文件放进矩阵
	ifstream inf;
	inf.open(filename_origin, ifstream::in);
	MatrixXd m1(14435, 4);
	CString str_1;
	const int cnt_1 = 4;
	string line_1;
	double z_1 = 0;
	int j_1 = 0;
	//用来计数小循环
	int k_1 = 0;
	//用来计数大循环
	size_t comma_1 = 0;
	size_t comma2_1 = 0;
	//设置进度条长度
	m_process1.SetRange(0, 14435);
	//设置进度条每一次进度
	m_process1.SetStep(1);

	while (!inf.eof())//当不是文件末尾的时候
	{
		getline(inf, line_1);
		comma_1 = line_1.find(',', 0);
		z_1 = atof(line_1.substr(0, comma_1).c_str());
		//不把点号放进去
		while (comma_1 < line_1.size() && j_1 != cnt_1 - 1)
		{
			comma2_1 = line_1.find(',', comma_1 + 1);
			z_1 = atof(line_1.substr(comma_1 + 1, comma2_1 - comma_1 - 1).c_str());
			m1(k_1, j_1) = z_1;
			//往矩阵在输入数据
			++j_1;

			str_1.Format(_T("%lf"), z_1);
			m_origin = m_origin + " " + str_1;

			comma_1 = comma2_1;
			if (j_1 == 3)
			{
				k_1++;
				m_origin += "\r\n";
				//每放进一个进度条就动一下
				m_process1.StepIt();
			}
		}
		cout << endl;
		j_1 = 0;
	}
	inf.close();
	UpdateData(FALSE);


	//构建输出结果的矩阵
	MatrixXd m2(14435, 3);
	CString str;
	//设置进度条长度
	m_process2.SetRange(0, 14435);
	//设置进度条每一次进度
	m_process2.SetStep(1);
	//开始循环计算输出
	for(int i=0;i< 14435;i++)
	{
		//构建一个x,y,z的值
		double X = m1(i, 0);
		double Y = m1(i, 1);
		double Z = m1(i, 2);
		//设置已知值
		double  a = 6378137.0;
		double  b = 6356752.3142;
		double PI = 3.1415926;
		double e1 = ((pow(a, 2) - pow(b, 2))) / (pow(a, 2)); double e2 = ((pow(a, 2) - pow(b, 2))) / (pow(b, 2));
		double t = sqrt(pow(X, 2) + pow(Y, 2));
		double θ = atan((Z*a) / (b * t));
		double BT = (atan((Z + e2 * b*pow(sin(θ), 3)) / (t - e1 * a*pow(cos(θ), 3))));//B
		double L = (atan(Y / X)) * 180 / PI;
		double N = a / sqrt(1 - e1 * pow(sin(BT), 2));//N
		double H = ((t) / cos(BT)) - N;
		double B = (atan((Z + e2 * b*pow(sin(θ), 3)) / (t - e1 * a*pow(cos(θ), 3)))) * 180 / PI;
		m2(i, 0) = B;
		m2(i, 1) = L;
		m2(i, 2) = H;
		str.Format(_T("%d"), i+1);
		m_result = m_result + " " + str;
		str.Format(_T("%lf"), m2(i, 0));
		m_result = m_result + " " + str;
		str.Format(_T("%lf"), m2(i, 1));
		m_result = m_result + " " + str;
		str.Format(_T("%lf"), m2(i, 2));
		m_result = m_result + " " + str;
		m_result += "\r\n";
		//每放进一个进度条就动一下
		m_process2.StepIt();
	}
	UpdateData(FALSE);
}

//地心地固系与站心坐标系转换
void CcoordinatetransformationDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//读取源文件放进矩阵
	ifstream inf;
	inf.open(filename_origin, ifstream::in);
	MatrixXd m1(14435, 3);
	CString str_1;
	const int cnt_1 = 4;
	string line_1;
	double z_1 = 0;
	int j_1 = 0;
	//用来计数小循环
	int k_1 = 0;
	//用来计数大循环
	size_t comma_1 = 0;
	size_t comma2_1 = 0;
	//设置进度条长度
	m_process1.SetRange(0, 14435);
	//设置进度条每一次进度
	m_process1.SetStep(1);
	while (!inf.eof())//当不是文件末尾的时候
	{
		getline(inf, line_1);
		comma_1 = line_1.find(',', 0);
		z_1 = atof(line_1.substr(0, comma_1).c_str());
		//点号不作处理
		while (comma_1 < line_1.size() && j_1 != cnt_1 - 1)
		{
			comma2_1 = line_1.find(',', comma_1 + 1);
			z_1 = atof(line_1.substr(comma_1 + 1, comma2_1 - comma_1 - 1).c_str());
			m1(k_1, j_1) = z_1;
			++j_1;

			str_1.Format(_T("%lf"), z_1);
			m_origin = m_origin + " " + str_1;
		
			comma_1 = comma2_1;
			if (j_1 == 3)
			{
				k_1++;
				m_origin += "\r\n";
				//每放进一个进度条就动一下
				m_process1.StepIt();
			}
			
		}
		cout << endl;
		j_1 = 0;
	}
	inf.close();
	UpdateData(FALSE);

	//设置进度条长度
	m_process2.SetRange(0, 14435);
	//设置进度条每一次进度
	m_process2.SetStep(1);
	//构建输出结果的矩阵
	MatrixXd m2(14435, 3);
	CString str;
	//设置进度条长度
	m_process2.SetRange(0, 14435);
	//设置进度条每一次进度
	m_process2.SetStep(1);
	//开始循环计算输出
	for (int i = 0; i < 14435; i++)
	{
		//构建一个x,y,z的值
		double X = m1(i, 0);
		double Y = m1(i, 1);
		double Z = m1(i, 2);
		//设置WGS84的已知值
		double  a = 6378137.0;
		double b = 6356752.3142;
		double e1 = (a*a - b * b) / (a*a);
		double e2 = (a*a - b * b) / (b*b);
		double PI = 3.1415926;
		//设置站心
		double x = 6378210.6613, y = 12740.1814, z = 49093.2052;
		double t = sqrt(X*X + Y * Y);
		double θ = atan((Z*a) / (b * t));
		double B = (atan((Z + e2 * b*pow(sin(θ), 3)) / (t - e1 * a*pow(cos(θ), 3))));//B
		double L = (atan(Y / X));
		double XP = -sin(B)*cos(L)*(-x) - sin(L)*sin(B)*(-y) + cos(B)*(-z);
		double YP = -sin(L)*(-x) + cos(L)*(-y);
		double ZP = cos(B)*cos(L)*(-x) + cos(B)*sin(L)*(-y) + sin(B)*(-z);
		double XG = X + ((-sin(B)*cos(L)*XP - sin(L)*YP + cos(B)*cos(L)*ZP));
		double YG = Y + ((-sin(B)*sin(L)*XP + cos(L)*YP + cos(B)*sin(L)*ZP));
		double ZG = Z + (cos(B)*XP + sin(B)*ZP);
		m2(i, 0) = ZG;
		m2(i, 1) = YG;
		m2(i, 2) = XG;
		str.Format(_T("%d"), i + 1);
		m_result = m_result + " " + str;
		str.Format(_T("%lf"), m2(i, 0));
		m_result = m_result + " " + str;
		str.Format(_T("%lf"), m2(i, 1));
		m_result = m_result + " " + str;
		str.Format(_T("%lf"), m2(i, 2));
		m_result = m_result + " " + str;
		m_result += "\r\n";
		//每放进一个进度条就动一下
		m_process2.StepIt();
	}
	UpdateData(FALSE);
}

//清除按钮
void CcoordinatetransformationDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//将edit control中的换成空格
	m_path_origin = "";
	m_path_target = "";
	m_origin = "";
	m_target = "";
	m_result = "";
	//将两个process control重置
	m_process1.SetPos(0);;
	m_process2.SetPos(0);;
	UpdateData(FALSE);
}
