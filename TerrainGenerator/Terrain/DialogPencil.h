#pragma once
#include "DialogPencil.h"
#include "MainFrm.h"

// CDialogPencil dialog

class CDialogPencil : public CDialog
{
	DECLARE_DYNAMIC(CDialogPencil)
bool activColor;
public:
	CDialogPencil(CWnd* pParent = NULL);   // standard constructor
	afx_msg void OnBnColor();
	afx_msg void OnBnClickedColorOk();
	afx_msg void OnBnClickedPenciOk();
	int Value;
	CButton m_BtnSelectColor;
	virtual ~CDialogPencil();

// Dialog Data
	enum { IDD = IDD_DIALOGPENCIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
