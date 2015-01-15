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
	CEdit m_EditPath; //���� ����� ���� � ����� � ���������� ���� "��������� ����� �����"
	CButton m_BtnSelectPath; //����� ����
	afx_msg void OnBnSelectPathClicked();
	afx_msg void OnBnClickedOk();
	CEdit m_EditWight; //���� ������ � ���������� ���� "��������� ����� �����"
	CEdit m_EditHeight;// ���� ������ � ���������� ���� "��������� ����� �����"
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL); //�������� ����������� ����
	CString GetFullFileName(){return GetStrFromEdit(&m_EditPath);}
	int GetW(){return atoi(GetStrFromEdit(&m_EditWight));} //
	int GetH(){return atoi(GetStrFromEdit(&m_EditHeight));} //
};
