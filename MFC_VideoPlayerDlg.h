
// MFC_VideoPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFC_VideoPlayerDlg �Ի���
class CMFC_VideoPlayerDlg : public CDialogEx
{
// ����
public:
	CMFC_VideoPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_VIDEOPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
