// DialogPencil.cpp : implementation file
//

#include "stdafx.h"
#include "Terrain.h"
#include "DialogPencil.h"
#include "MainFrm.h"


// CDialogPencil dialog

IMPLEMENT_DYNAMIC(CDialogPencil, CDialog)

CDialogPencil::CDialogPencil(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPencil::IDD, pParent)
{
activColor=false;
}

CDialogPencil::~CDialogPencil()
{
}

void CDialogPencil::DoDataExchange(CDataExchange* pDX)
{
	
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTONPALLITRA, m_BtnSelectColor);
}


BEGIN_MESSAGE_MAP(CDialogPencil, CDialog)
ON_BN_CLICKED(IDC_BUTTONPALLITRA, &CDialogPencil::OnBnColor)
ON_BN_CLICKED(IDOK, &CDialogPencil::OnBnClickedColorOk)
ON_BN_CLICKED(IDOKMAIN, &CDialogPencil::OnBnClickedPenciOk)
END_MESSAGE_MAP()

void CDialogPencil::OnBnColor()
{
	CColorDialog Color(RGB(255,0,0),CC_FULLOPEN);
		Color.DoModal();

}

void CDialogPencil::OnBnClickedColorOk()
{

}

void CDialogPencil::OnBnClickedPenciOk()
{
	CDialogPencil pencil;
MessageBox("Вы нажали на кнопку очистить всё!");
pencil.DoModal();
}

// CDialogPencil message handlers
