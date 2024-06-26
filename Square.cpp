// Square.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Square.h"
#include "SquareDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSquareApp

BEGIN_MESSAGE_MAP(CSquareApp, CWinApp)
	//{{AFX_MSG_MAP(CSquareApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSquareApp construction

CSquareApp::CSquareApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSquareApp object

CSquareApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSquareApp initialization

BOOL CSquareApp::InitInstance()
{
	// Standard initialization

	CSquareDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
