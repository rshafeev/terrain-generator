#pragma once
#include "afxwin.h"
#include "Functions.h"
// CDlgCreateProject dialog

class CDlgCreateProject : public CDialog
{
	DECLARE_DYNAMIC(CDlgCreateProject)
CString *w, *h, *File;
public:
	CDlgCreateProject(CString *w, CString *h, CString *File, CWnd* pParent = NULL);   
	virtual ~CDlgCreateProject();

// Dialog Data
	enum { IDD = IDD_DIALOG_CREATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditPath; //поле ввода пути к файлу в диалоговом окне "«агрузить карту высот"
	CButton m_BtnSelectPath; //выбор пути
	afx_msg void OnBnSelectPathClicked();
	afx_msg void OnBnClickedOk();
	CEdit m_EditWight; //поле ширины в диалоговом окне "«агрузить карту высот"
	CEdit m_EditHeight;// поле высоты в диалоговом окне "«агрузить карту высот"
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL); //создание диалогового окна
	CString GetFullFileName(){return GetStrFromEdit(&m_EditPath);}
	int GetW(){return atoi(GetStrFromEdit(&m_EditWight));} //
	int GetH(){return atoi(GetStrFromEdit(&m_EditHeight));} //
};
