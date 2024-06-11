#if !defined(AFX_SETTING_H__5788BA7D_FB7B_4AE5_8035_2F1738945B58__INCLUDED_)
#define AFX_SETTING_H__5788BA7D_FB7B_4AE5_8035_2F1738945B58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetting dialog

class CSetting : public CDialog
{
// Construction
public:
	CSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetting)
	enum { IDD = IDD_SETTING };
	int		m_iTime;
	int		m_iDifficulty;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetting)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTING_H__5788BA7D_FB7B_4AE5_8035_2F1738945B58__INCLUDED_)
