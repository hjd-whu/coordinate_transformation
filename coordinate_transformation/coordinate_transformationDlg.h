
// coordinate_transformationDlg.h: 头文件
//

#pragma once


// CcoordinatetransformationDlg 对话框
class CcoordinatetransformationDlg : public CDialogEx
{
// 构造
public:
	CcoordinatetransformationDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COORDINATE_TRANSFORMATION_DIALOG };
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
public:
	afx_msg void OnEnChangeEditPathOrigin();
	afx_msg void OnEnChangeEditOrigin();
	afx_msg void OnBnClickedButtonPathOrigin();
	CString m_path_origin;
	afx_msg void OnBnClickedButtonPathTarget();
	CString m_path_target;
	CString m_origin;
	afx_msg void OnBnClickedButton1();
	CString m_target;
	CString m_result;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CProgressCtrl m_process1;
	CProgressCtrl m_process2;
	afx_msg void OnBnClickedButton6();
};
