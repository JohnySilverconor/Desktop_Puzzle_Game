// SquareDlg.cpp : implementation file
//////////////////////////////////////////////////////////////////////
//////////			Created by		:	Hadi Dayvary		//////////
//////////			Email			:	hdayvary@yahoo.com	//////////
//////////			Creation Date	:	2005/5/10			//////////
//////////			Last Update		:	2005/7/19			//////////
//////////			Description		:	Square Game			//////////
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Square.h"
#include "SquareDlg.h"
#include "Setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//****************************************************************************
// - Constructor
//****************************************************************************
CSquareDlg::CSquareDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSquareDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSquareDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CSetting	dlgSetting;
	if(dlgSetting.DoModal() != IDOK)
		exit(0);

	Sleep(dlgSetting.m_iTime * 1000);

	
	m_ixScreen	= ::GetSystemMetrics(SM_CXSCREEN);
	m_iyScreen	= ::GetSystemMetrics(SM_CYSCREEN);

	m_ixSquare	= m_ixScreen / 8;
	m_iySquare	= m_iyScreen / 8;

	for(int i=0; i<64; i++)
		m_iSquares[i] = i+1;

	CaptureDesktop();

	srand((UINT)time(NULL));

	for(i=0; i<(dlgSetting.m_iDifficulty+1)*20; i++)
	{
		ReplaceRects(GetSquareFromPoint(CPoint(rand()%m_ixScreen, rand()%m_iyScreen)), GetSquareFromPoint(CPoint(rand()%m_ixScreen, rand()%m_iyScreen)));
		InvertRect(GetSquareFromPoint(CPoint(rand()%m_ixScreen, rand()%m_iyScreen)));
	}

	m_iTime		= ::GetTickCount();

	m_iSelected	= 0;
	m_bFrame	= FALSE;
	m_bRed		= TRUE;
}
//****************************************************************************
// - Destructor : clean up
//****************************************************************************
CSquareDlg::~CSquareDlg()
{
	delete m_pDescBitmap;

	delete m_pDesktopDC;
	delete m_pMemDC;
}
//****************************************************************************
void CSquareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSquareDlg)
	//}}AFX_DATA_MAP
}
//****************************************************************************
BEGIN_MESSAGE_MAP(CSquareDlg, CDialog)
	//{{AFX_MSG_MAP(CSquareDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDOK, OnExit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, OnExit)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//****************************************************************************
HCURSOR CSquareDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//****************************************************************************
//****************************************************************************
void CSquareDlg::OnPaint() 
{
	CDialog::OnPaint();

	CDC		*pDC = GetDC();
	pDC->BitBlt(0, 0, m_ixScreen, m_iyScreen, m_pDesktopDC, 0, 0, SRCCOPY);

	if(m_bFrame)
		DrawFrames();

	ReleaseDC(pDC);
}
//****************************************************************************
// - 
//****************************************************************************
BOOL CSquareDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

#ifdef _DEBUG
	::SetWindowPos (GetSafeHwnd(), 0, 0, 0, m_ixScreen, m_iyScreen, SWP_SHOWWINDOW);
#else
	::SetWindowPos (GetSafeHwnd(), HWND_TOPMOST, 0, 0, m_ixScreen, m_iyScreen, SWP_SHOWWINDOW);
#endif
	return TRUE;
}
//****************************************************************************
// - Save bitmap of display DC to a memory DC
//****************************************************************************
void CSquareDlg::CaptureDesktop()
{
	CDC		*pDC = GetDesktopWindow()->GetDC();

	m_pDesktopDC = new CDC();
	m_pDesktopDC->CreateCompatibleDC(pDC);

	m_pDescBitmap = new CBitmap();
	m_pDescBitmap->CreateCompatibleBitmap(pDC, m_ixScreen, m_iyScreen);

	m_pDesktopDC->SelectObject(m_pDescBitmap);

	m_pDesktopDC->BitBlt (0, 0, m_ixScreen, m_iyScreen, pDC, 0, 0, SRCCOPY );

	// - Create a temporary DC for replacing
	m_pMemDC = new CDC();
	m_pMemDC->CreateCompatibleDC(m_pDesktopDC);
}
//****************************************************************************
// - Replace two rects in memory device context
//****************************************************************************
void CSquareDlg::ReplaceRects(CRect rectSource, CRect rectDest)
{
	CBitmap	*pBitmap = new CBitmap();
	pBitmap->CreateCompatibleBitmap(m_pDesktopDC, m_ixSquare, m_iySquare);

	CBitmap	*pOldBitmap = m_pMemDC->SelectObject(pBitmap);

	// - Copy source rectangle from memory DC to a temporary DC
	m_pMemDC->BitBlt (0, 0, m_ixSquare, m_iySquare, m_pDesktopDC, rectSource.left, rectSource.top, SRCCOPY );

	// - Copy destination rectangle from memory DC to source rectangle in memory DC
	m_pDesktopDC->BitBlt (rectSource.left, rectSource.top, m_ixSquare, m_iySquare, m_pDesktopDC, rectDest.left, rectDest.top, SRCCOPY );

	// - Copy source rectangle from temporary DC to destination rectangle in memory DC
	m_pDesktopDC->BitBlt (rectDest.left, rectDest.top, m_ixSquare, m_iySquare, m_pMemDC, 0, 0, SRCCOPY );

	// - Calculate number of rectangles
	int iSource	= rectSource.right / m_ixSquare + rectSource.top / m_iySquare * 8;
	int iDest	= rectDest.right / m_ixSquare + rectDest.top / m_iySquare * 8;

	// - Replace number of rectangles
	int iTemp				= m_iSquares[iSource-1];
	m_iSquares[iSource-1]	= m_iSquares[iDest-1];
	m_iSquares[iDest-1]		= iTemp;

	m_pMemDC->SelectObject(pOldBitmap);
	delete pBitmap;
}
//****************************************************************************
// - 
//****************************************************************************
void CSquareDlg::InvertRect(CRect rect)
{
	CBitmap	*pBitmap = new CBitmap();
	pBitmap->CreateCompatibleBitmap(m_pDesktopDC, m_ixSquare, 1);

	CBitmap	*pOldBitmap = m_pMemDC->SelectObject(pBitmap);

	for(int i=0; i<m_iySquare/2; i++)
	{
		// - Copy top line from memory DC to a temporary DC
		m_pMemDC->BitBlt (0, 0, m_ixSquare, 1, m_pDesktopDC, rect.left, rect.top+i, SRCCOPY );

		// - Copy bottom line from memory DC to top line in memory DC
		m_pDesktopDC->BitBlt (rect.left, rect.top+i, m_ixSquare, 1, m_pDesktopDC, rect.left, rect.bottom-1-i, SRCCOPY );

		// - Copy top line from temporary DC to bottom line in memory DC
		m_pDesktopDC->BitBlt (rect.left, rect.bottom-1-i, m_ixSquare, 1, m_pMemDC, 0, 0, SRCCOPY );
	}

	// - Calculate number of rectangles
	int iSquare	= rect.right / m_ixSquare + rect.top / m_iySquare * 8;

	// - Replace number of rectangles
	m_iSquares[iSquare-1]	= -m_iSquares[iSquare-1];

	m_pMemDC->SelectObject(pOldBitmap);
	delete pBitmap;
}
//****************************************************************************
// - Draws a frame around a rectangle
//****************************************************************************
void CSquareDlg::FrameRect(CRect rect, BOOL bClear)
{
	CDC		*pDC = GetDC();

	if(m_bFrame)
		rect.DeflateRect(1, 1, 1, 1);
	pDC->FrameRect(&rect, &CBrush(RGB(0, 0, 255)));
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.bottom);

	pDC->MoveTo(rect.right-1, rect.top);
	pDC->LineTo(rect.left, rect.bottom);

	ReleaseDC(pDC);
}
//****************************************************************************
// - 
//****************************************************************************
void CSquareDlg::DrawFrames()
{
	CDC		*pDC = GetDC();
	CBrush	brush(RGB(255,0,0));
	CRect	rect;

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
		{
			rect.left	= i * m_ixSquare;
			rect.top	= j * m_iySquare;
			rect.right	= i * m_ixSquare + m_ixSquare;
			rect.bottom	= j * m_iySquare + m_iySquare;
			pDC->FrameRect(&rect,&brush);
		}
	if(m_iSelected)
		FrameRect(m_rectSelected);

	ReleaseDC(pDC);
}
//****************************************************************************
// - 
//****************************************************************************
int CSquareDlg::CheckForWin()
{
	int		i, iError=0;
	for(i=0; i<64; i++)
		if(m_iSquares[i] != i+1)
			iError++;

	if(!iError)
	{
		MessageBox("You Won The Game !", "Congratulation");
		OnOK();
	}
	return iError;
}
//****************************************************************************
// - 
//****************************************************************************
CRect CSquareDlg::GetSquareFromPoint(CPoint point)
{
	CRect	rect;

	rect.left	= point.x - (point.x % m_ixSquare);
	rect.top	= point.y - (point.y % m_iySquare);
	rect.right	= rect.left	+ m_ixSquare;
	rect.bottom	= rect.top	+ m_iySquare;

	return rect;
}
//****************************************************************************
// - Select a rectangle(source) or Replace first selected rectangle(source) 
//	 with new selected rectangle(destination).
//****************************************************************************
void CSquareDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!m_iSelected)// - First clicking
	{
		m_rectSelected = GetSquareFromPoint(point);
		m_iSelected = m_rectSelected.right / m_ixSquare + m_rectSelected.top / m_iySquare * 8;

		// - Draw a frame around first selected rectangle
		FrameRect(m_rectSelected);
		return;
	}
	else			// - Second clicking
	{
		CRect	rect = GetSquareFromPoint(point);
		CRect	rectSelected;
		ReplaceRects(m_rectSelected, rect);

		rectSelected.CopyRect(&m_rectSelected);

		CDC		*pDC = GetDC();
		if(m_bFrame)
		{
			rect.DeflateRect(1,1,1,1);
			rectSelected.DeflateRect(1,1,1,1);
		}
		pDC->BitBlt(rectSelected.left, rectSelected.top, rectSelected.Width(), rectSelected.Height(), m_pDesktopDC, rectSelected.left,rectSelected.top, SRCCOPY);
		pDC->BitBlt(rect.left,rect.top, rectSelected.Width(), rectSelected.Height(), m_pDesktopDC, rect.left, rect.top, SRCCOPY);
		ReleaseDC(pDC);

		m_iSelected = 0;
		CheckForWin();
	}
	CDialog::OnLButtonDown(nFlags, point);
}
//****************************************************************************
// - Draw all frames for help or clear them all.
//****************************************************************************
void CSquareDlg::OnMButtonDown(UINT nFlags, CPoint point) 
{
	m_bFrame = !m_bFrame;

	Invalidate(FALSE);

	CDialog::OnMButtonDown(nFlags, point);
}
//****************************************************************************
// - Invert selected rectangle.
//****************************************************************************
void CSquareDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CRect	rect = GetSquareFromPoint(point);
	InvertRect(rect);

	CDC		*pDC = GetDC();
	if(m_bFrame)
		rect.DeflateRect(1,1,1,1);

	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), m_pDesktopDC, rect.left, rect.top, SRCCOPY);
	ReleaseDC(pDC);

	CheckForWin();
	//m_iSelected = 0;

	CDialog::OnRButtonDown(nFlags, point);
}
//****************************************************************************
// - 
//****************************************************************************
void CSquareDlg::OnExit() 
{
	int		iError = CheckForWin();

	SetTimer(ID_EXIT, 500, NULL);

	m_iTime = ::GetTickCount() - m_iTime;
	m_iTime /= 1000;

	CString	sError;
	sError.Format("Your play took %d minutes and %d seconds.\nYou had %d Errors.", m_iTime/60, m_iTime%60, iError);

	if(iError < 5)
		MessageBox(sError+"\nNot bad , try again.", "Loser !!!");
	else if(iError < 12)
		MessageBox(sError+"\nYou must practice more.", "Loser !!!");
	else if(iError < 20)
		MessageBox(sError+"\nBad babe!", "Loser !!!");
	else
		MessageBox(sError+"\nYou're really a Loser!!!", "Loser !!!");

	OnOK();
}
//****************************************************************************
void CSquareDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_EXIT:
		{
			CDC		*pDC = GetDC();
			CRect	rect;
			m_bRed = !m_bRed;
			pDC->SetTextColor(RGB(m_bRed*255,0,!m_bRed*255));
			pDC->SetBkMode(TRANSPARENT);
			
			m_pDesktopDC->SetTextColor(RGB(255,0,0));
			m_pDesktopDC->SetBkMode(TRANSPARENT);
			
			for(int i=0; i<64; i++)
				if(m_iSquares[i] != i+1)
				{
					rect.left	= (i%8) * m_ixSquare;
					rect.top	= (i/8) * m_iySquare;
					rect.right	= (i%8) * m_ixSquare + m_ixSquare;
					rect.bottom	= (i/8) * m_iySquare + m_iySquare;
					pDC->DrawText("Wrong", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					m_pDesktopDC->DrawText("Wrong", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			ReleaseDC(pDC);
		}
		break;
	case ID_GETHELP:
		KillTimer(ID_GETHELP);
		Invalidate();
		if(m_iSelected)
			FrameRect(m_rectSelected);
		break;
	}

	CDialog::OnTimer(nIDEvent);
}
//****************************************************************************