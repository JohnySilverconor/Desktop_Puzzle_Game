// Square.h : main header file for the SQUARE application
//

#if !defined(AFX_SQUARE_H__57BCAECF_3F53_4FC5_A36F_500767A09DE3__INCLUDED_)
#define AFX_SQUARE_H__57BCAECF_3F53_4FC5_A36F_500767A09DE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSquareApp:
// See Square.cpp for the implementation of this class
//

class CSquareApp : public CWinApp
{
public:
	CSquareApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSquareApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSquareApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUARE_H__57BCAECF_3F53_4FC5_A36F_500767A09DE3__INCLUDED_)
