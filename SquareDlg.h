// SquareDlg.h : header file
//////////////////////////////////////////////////////////////////////
//////////			Created by		:	Hadi Dayvary		//////////
//////////			Email			:	hdayvary@yahoo.com	//////////
//////////			Creation Date	:	2005/5/10			//////////
//////////			Last Update		:	2005/7/19			//////////
//////////			Description		:	Square Game			//////////
//////////////////////////////////////////////////////////////////////

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CSquareDlg dialog

class CSquareDlg : public CDialog
{
// Construction
public:
	CSquareDlg(CWnd* pParent = NULL);	// standard constructor
	~CSquareDlg();

// Dialog Data
	//{{AFX_DATA(CSquareDlg)
	enum { IDD = IDD_SQUARE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSquareDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSquareDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnExit();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDC*		m_pDesktopDC;
	CDC*		m_pMemDC;
	CBitmap*	m_pDescBitmap;

	int			m_iSquares[64];

	int			m_iSelected;
	CRect		m_rectSelected;
	BOOL		m_bFrame;
	BOOL		m_bRed;

	int			m_iTime;

	int			m_ixScreen;
	int			m_iyScreen;

	int			m_ixSquare;
	int			m_iySquare;

	void		CaptureDesktop();
	void		ReplaceRects(CRect rectSource, CRect rectDest);
	void		InvertRect(CRect rect);
	void		FrameRect(CRect rect, BOOL bClear=FALSE);
	void		DrawFrames();
	int			CheckForWin();
	CRect		GetSquareFromPoint(CPoint point);
};
