
// Delay_Composition_VHFDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Delay_Composition_VHF.h"
#include "Delay_Composition_VHFDlg.h"

#include "common.h"
#include "map_2d.h"
#include "diff_wheel_robot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDelay_Composition_VHFDlg 대화 상자




CDelay_Composition_VHFDlg::CDelay_Composition_VHFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelay_Composition_VHFDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDelay_Composition_VHFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDelay_Composition_VHFDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CDelay_Composition_VHFDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CDelay_Composition_VHFDlg 메시지 처리기

BOOL CDelay_Composition_VHFDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	//// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != NULL)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	//// 맵을 그리기 위한 윈도우 크기를 가져온다.
	GetDlgItem (IDC_STATIC_MAP)->GetWindowRect (_mapRect);
	GetDlgItem (IDC_STATIC_MAP)->DestroyWindow();
	ScreenToClient(_mapRect);

	// TODO: Add extra initialization here
	//_robot_x    = g_ini.robot_x;
	//_robot_y    = g_ini.robot_y;
	//_robot_theta= g_ini.robot_theta;

	//_scale    = g_ini.scale;
	//_offset_x = g_ini.offset_x;
	//_offset_y = g_ini.offset_y;

	_robot_x    = 3.89229;
	_robot_y    = -1.15531;
	_robot_theta= 32.1608;

	_scale    = 35.9137;
	_offset_x = -7.22623;
	_offset_y = -5.29498;



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDelay_Composition_VHFDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDelay_Composition_VHFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

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
		//=================================================
		CPaintDC dc(this); // device context for painting

		if (_memDC.GetSafeHdc() == NULL) {
			_memDC.CreateCompatibleDC(&dc);
			_bitmap.CreateCompatibleBitmap(&dc, _mapRect.Width(), _mapRect.Height());
			_bitmapOld = _memDC.SelectObject(&_bitmap);
			ASSERT (_bitmapOld);
		}

		if (_memDC.GetSafeHdc() != NULL) {
			dc.BitBlt(_mapRect.left, _mapRect.top, _mapRect.Width(), _mapRect.Height(), &_memDC, 0,0, SRCCOPY);
		}
		//=================================================


		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDelay_Composition_VHFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDelay_Composition_VHFDlg::OnBnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CFileDialog fdlg(TRUE, "dxf", "*.dxf", OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, 
			"Map Files (*.dxf)|*.dxf|All Files (*.*)|*.*||", this);

	if (IDOK == fdlg.DoModal ()) {
		CString fileName = fdlg.GetPathName ();

		//strncpy (g_ini.map_file, (LPCSTR)fileName, MAX_PATH);
		MessageBox(_T((LPCSTR)fileName));

		_map_2d.clear(); // 변수 초기화 안해줘도 되지만 변수는 초기화 해주는 습관을...
		load_dxf ((LPCSTR)fileName, &_map_2d);

		// load_dxf() 함수로 읽어들인 맵 정보는 mm로 저장되어있다. 
		// 이 데이터를 m로 단위 변경한다.
		for (unsigned int i=0; i<_map_2d.size(); ++i) {
			_map_2d[i].x0 *= 0.001;
			_map_2d[i].y0 *= 0.001;
			_map_2d[i].z0 *= 0.001;
			_map_2d[i].x1 *= 0.001;
			_map_2d[i].y1 *= 0.001;
			_map_2d[i].z1 *= 0.001; 
		}
	}

	// 멥 그리기 -> ontimer 로 이동
	if (_memDC.GetSafeHdc()) {

		DrawBackground (_memDC, 100, 100);
		DrawMap (_memDC);
		DrawRobot (_memDC, 0, 0, 0, _axle_length, RGB(0,0,255));

		//if (IsDlgButtonChecked(IDC_CHECK_MAP				) == BST_CHECKED) DrawMap (_memDC);
		//if (IsDlgButtonChecked(IDC_CHECK_2D_FEATURE			) == BST_CHECKED) DrawFeature2D (_memDC);
		//if (IsDlgButtonChecked(IDC_CHECK_3D_FEATURE			) == BST_CHECKED) DrawFeature3D (_memDC);
		//if (IsDlgButtonChecked(IDC_CHECK_BEACON				) == BST_CHECKED) DrawBeacon (_memDC);
		//if (IsDlgButtonChecked(IDC_CHECK_CEILING_LANDMARK	) == BST_CHECKED) DrawCeilingLandmark (_memDC);
		//if (IsDlgButtonChecked(IDC_CHECK_FLOOR_LANDMARK		) == BST_CHECKED) DrawFloorLandmark (_memDC);
		//if (IsDlgButtonChecked(IDC_CHECK_SCANNING_LASER		) == BST_CHECKED) DrawScanningLaser (_memDC, RGB(255,0,0), false);
		//if (IsDlgButtonChecked(IDC_CHECK_ROBOT				) == BST_CHECKED) DrawRobot (_memDC, _robot_x, _robot_y, _robot_theta, _axle_length, RGB(0,0,255));

		//DrawText (_memDC, dt);
	}

	InvalidateRect (&_mapRect, FALSE);
}

// 
int CDelay_Composition_VHFDlg::M2Px(double _x) { return INTEGER( _scale*(_x - _offset_x)); }
int CDelay_Composition_VHFDlg::M2Py(double _y) { return INTEGER(-_scale*(_y - _offset_y)) + _mapRect.Height(); }
int CDelay_Composition_VHFDlg::M2Pl(double _d) { return INTEGER( _scale*_d); }
double CDelay_Composition_VHFDlg::P2Mx(int _x) { return (                    _x)/_scale + _offset_x; }
double CDelay_Composition_VHFDlg::P2My(int _y) { return (_mapRect.Height() - _y)/_scale + _offset_y; }
double CDelay_Composition_VHFDlg::P2Ml(int _d) { return (                    _d)/_scale; }

void CDelay_Composition_VHFDlg::DrawBackground (CDC &dc, int width, int height)
{
	dc.SelectStockObject (WHITE_PEN);
	dc.SelectStockObject (WHITE_BRUSH);

	dc.Rectangle (0, 0, 10000, 10000);

	CPen pen (PS_SOLID, 1, RGB(225,225,225));
	dc.SelectObject (pen);

	for (int i=0; i<=width; ++i) {
		dc.MoveTo (M2Px(i), M2Py(0));
		dc.LineTo (M2Px(i), M2Py(height));
	}
	for (int i=0; i<=height; ++i) {
		dc.MoveTo (M2Px(0), M2Py(i));
		dc.LineTo (M2Px(width), M2Py(i));
	}
}

void CDelay_Composition_VHFDlg::DrawMap (CDC &dc)
{
	CPen pen (PS_SOLID, 1, RGB(127,127,127));
	dc.SelectObject (pen);

	for (unsigned int i=0; i<_map_2d.size(); ++i) {
		if (_map_2d[i].type == ET_LINE) {
			dc.MoveTo (M2Px(_map_2d[i].x0), M2Py(_map_2d[i].y0));
			dc.LineTo (M2Px(_map_2d[i].x1), M2Py(_map_2d[i].y1));
		}
	}
}

void CDelay_Composition_VHFDlg::DrawRobot (CDC &dc, double x, double y, double theta, double diameter, COLORREF color)
{
	dc.SelectStockObject (NULL_BRUSH);

	CPen pen (PS_SOLID, 2, color);
	dc.SelectObject (pen);

	int rx = M2Px(x);
	int ry = M2Py(y);
	int rr = M2Pl(diameter/2);

	int dx = (int)(rr*cos(theta));
	int dy = (int)(rr*sin(theta));

	dc.Ellipse (rx-rr, ry-rr, rx+rr, ry+rr);
	dc.MoveTo (rx, ry);
	dc.LineTo (rx+dx, ry-dy);
}
