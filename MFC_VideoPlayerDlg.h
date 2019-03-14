
// MFC_VideoPlayerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMFC_VideoPlayerDlg 对话框
class CMFC_VideoPlayerDlg : public CDialogEx
{
// 构造
public:
	CMFC_VideoPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_VIDEOPLAYER_DIALOG };
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
	afx_msg void OnBnClickedButton1();
private:
	CEdit n_edit1;
	CEdit n_edit2;
public:
	afx_msg void OnBnClickedButton2();
private:
	CEdit n_edit3;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
private:
	CComboBox n_cbx;
public:
//	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton5();
private:
	CComboBox n_cbx1;
public:
//	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo2();
};
