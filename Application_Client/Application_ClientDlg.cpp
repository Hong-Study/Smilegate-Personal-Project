
// Application_ClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Application_Client.h"
#include "Application_ClientDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApplicationClientDlg 대화 상자

CApplicationClientDlg::CApplicationClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_APPLICATION_CLIENT_DIALOG, pParent)
	, URL_INPUT(_T(""))
	, URL_OUTPUT(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_socket = new ClientNetwork(L"127.0.0.1", 5005);
	if (!_socket->Connect())
		exit(0);
}

void CApplicationClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_URLL, URL_INPUT);
	DDX_Text(pDX, IDC_URLS, URL_OUTPUT);
}

BEGIN_MESSAGE_MAP(CApplicationClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CApplicationClientDlg::OnInputClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CApplicationClientDlg::OnBnClickedBrowser)
END_MESSAGE_MAP()


// CApplicationClientDlg 메시지 처리기

BOOL CApplicationClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CApplicationClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
// 이 함수를 호출합니다.
HCURSOR CApplicationClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CApplicationClientDlg::OnInputClicked()
{
	GetDlgItemText(IDC_URLL, URL_INPUT);
	int len = URL_INPUT.GetLength();
	char* send_Buffer = new char[len+1];

	send_Buffer = URL_INPUT.GetBuffer(0);
	send_Buffer[len] = '\0';
	if (!_socket->IsCheck(send_Buffer) && (_socket->Send(send_Buffer, 0) == -1)) {
		SetDlgItemText(IDC_URLS, "올바른 URL을 입력해주세요.");
		return;
	}
	_socket->Recv();

	URL_OUTPUT = _socket->getUrlString().c_str();
	SetDlgItemText(IDC_URLS, URL_OUTPUT);

	send_Buffer = nullptr;
	delete[] send_Buffer;
}


void CApplicationClientDlg::OnBnClickedBrowser()
{
	try {
		GetDlgItemText(IDC_URLL, URL_INPUT);
		if (URL_INPUT.GetLength() == 0) {
			return;
		}
		int len = URL_INPUT.GetLength();
		char* send_Buffer = new char[len + 1];
		send_Buffer = URL_INPUT.GetBuffer(0);
		send_Buffer[len] = '\0';
		//만약 short일 경우 long 받아오고 아니면 그냥 실행.
		if (_socket->IsCheck(send_Buffer)) {
			if (_socket->Send(send_Buffer, 1) == -1)
				return;
			if (_socket->Recv() == -1) {
				SetDlgItemText(IDC_URLS, "Error");
				return;
			}
			//오류 체크 넣어줘야함
			URL_OUTPUT = _socket->getNormalString().c_str();
		}
		else {
			URL_OUTPUT = URL_INPUT;
		}
		char browser[MAX_PATH];
		HFILE h = _lcreat("dummy.html", 0);
		_lclose(h);
		FindExecutable("dummy.html", NULL, browser);
		DeleteFile("dummy.html");

		SetDlgItemText(IDC_URLS, URL_OUTPUT);
		ShellExecute(NULL, "open", browser, URL_OUTPUT, NULL, 0);
	}
	catch (exception e) {
		SetDlgItemText(IDC_URLS, "Input URL");
	}

}
