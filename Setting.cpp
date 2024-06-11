// Setting.cpp : implementation file
//

#include "stdafx.h"
#include "Square.h"
#include "Setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetting dialog


CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetting)
	m_iTime = 2;
	m_iDifficulty = 1;
	//}}AFX_DATA_INIT
}


void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetting)
	DDX_Text(pDX, IDC_ETIME, m_iTime);
	DDX_Radio(pDX, IDC_REASY, m_iDifficulty);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetting, CDialog)
	//{{AFX_MSG_MAP(CSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetting message handlers

