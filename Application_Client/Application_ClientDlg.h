#pragma once
#include "ClientNetwork.h"

// CApplicationClientDlg 대화 상자
class CApplicationClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CApplicationClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPLICATION_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
private:
	CString URL_INPUT;
	CString URL_OUTPUT;
	ClientNetwork* _socket;

	char recv_Buffer[10];
public:
	afx_msg void OnInputClicked();
	afx_msg void OnBnClickedBrowser();
};
