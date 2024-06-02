
// RSADlg.h : header file
//

#pragma once
#include "afxwin.h"


// CRSADlg dialog
class CRSADlg : public CDialogEx
{
// Construction
public:
	CRSADlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RSA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CEdit edt_file_input;
	CListBox list_box_sign;
	CListBox list_box_sign_p;
	CListBox list_box_sign_q;
	CListBox list_box_file_text;
	CListBox list_box_file_sign;
	CListBox list_box_check;
	CButton btn_file;
	CButton btn_sign;
	CButton btn_send;
	CButton btn_save;
	CButton btn_file_text;
	CButton btn_file_sign;
	CButton btn_check;
	CButton btn_generate_key;
public:
	afx_msg void OnBnClickedBtnSign();
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnFile();
	afx_msg void OnBnClickedBtnFileText();
	afx_msg void OnBnClickedBtnCheck();
	afx_msg void OnBnClickedBtnGenerateKey();
protected:
	CEdit edt_file_text;
public:
	afx_msg void OnBnClickedBtnFileSign();
protected:
	CEdit edt_file_sign;
	CEdit list_file_sign;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeListSignP();
	afx_msg void OnEnChangeListSign();
	afx_msg void OnEnChangeListSignE();
	afx_msg void OnEnChangeEdtFileInput();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdtFileText();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMThemeChangedScrollbar2(NMHDR* pNMHDR, LRESULT* pResult);
};
