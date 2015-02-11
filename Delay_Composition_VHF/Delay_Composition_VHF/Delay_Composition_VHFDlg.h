
// Delay_Composition_VHFDlg.h : ��� ����
//

#pragma once


// CDelay_Composition_VHFDlg ��ȭ ����
class CDelay_Composition_VHFDlg : public CDialog
{
// �����Դϴ�.
public:
	CDelay_Composition_VHFDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DELAY_COMPOSITION_VHF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();


private:
	int M2Px(double _x);
	int M2Py(double _y);
	int M2Pl(double _d);
	double P2Mx(int _x);
	double P2My(int _y);
	double P2Ml(int _d);
	
	enum eObjectSel {
		SEL_NONE = 0, SEL_CURRENT, SEL_MAP
	};

	eObjectSel _sel;

	double _scale;
	double _offset_x;
	double _offset_y;
	CPoint _cursorDragStartPt;

	CRect _mapRect;
	
	void DrawBackground (CDC &dc, int width, int height);
	void DrawMap (CDC &dc);
	//void DrawFeature2D (CDC &dc);
	//void DrawFeature3D (CDC &dc);
	void DrawRobot (CDC &dc, double x, double y, double theta, double diameter, COLORREF color);
	//void DrawScanningLaser (CDC &dc, COLORREF color, bool line);
	//void DrawFloorLandmark (CDC &dc);
	//void DrawCeilingLandmark (CDC &dc);
	//void DrawBeacon (CDC &dc);
	//void DrawText (CDC &dc, double dt);

	CDC      _memDC;
	CBitmap  _bitmap;
	CBitmap* _bitmapOld;
};
