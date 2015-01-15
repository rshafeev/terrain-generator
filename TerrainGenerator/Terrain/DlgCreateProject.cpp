// DlgCreateProject.cpp : implementation file
//

#include "stdafx.h"
#include "Terrain.h"
#include "DlgCreateProject.h"
#include "GlLib.h"

// CDlgCreateProject dialog

IMPLEMENT_DYNAMIC(CDlgCreateProject, CDialog)

CDlgCreateProject::CDlgCreateProject(CString *w, CString *h, CString *File,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateProject::IDD, pParent)
{
this->w=w;
this->h=h;
this->File=File;
}

CDlgCreateProject::~CDlgCreateProject()
{
}
//===========================================================================================================================


//===========================================================================================================================
void CDlgCreateProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_EditPath);
	DDX_Control(pDX, IDC_BUTTON1, m_BtnSelectPath);
	DDX_Control(pDX, IDC_EDIT1, m_EditWight);
	DDX_Control(pDX, IDC_EDIT2, m_EditHeight);

	m_EditPath.SetWindowTextA("C:\\Users\\Roma\\Desktop\\Last\\Last\\rawfiles\\mySmall - �����.raw");//������ ���� � ����� �������
	m_EditHeight.SetWindowTextA("2000");							  //�������� ������ ����� ����� �������
	m_EditWight.SetWindowTextA("2000");                               //�������� ������ ����� ����� �������
}


BEGIN_MESSAGE_MAP(CDlgCreateProject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgCreateProject::OnBnSelectPathClicked)
	ON_BN_CLICKED(IDOK, &CDlgCreateProject::OnBnClickedOk)
	
END_MESSAGE_MAP()


void CDlgCreateProject::OnBnSelectPathClicked()						// ����� ���� ����� "��������� ����� �����" ��� �������� ������ "�������"
{
	 CFileDialog File(true,"raw",NULL,OFN_NOLONGNAMES   ,"����� �����(.raw)|*.raw||");
 if(File.DoModal()==IDOK)											//�������� ������������ ����������� ����
 {
	 m_EditPath.SetWindowTextA(File.GetPathName());					//��� ������ ������ "�������" � �.���� "��������� ����� �����" ��������� ���� � ������
	 CClientDC dc(this);
	 CString s;
	 dc.SetBkMode(TRANSPARENT); 
	 s.Format("������ �����:%d",GetFileSize(File.GetPathName()));
	 dc.TextOutA(5,5,s);

 }
}

void CDlgCreateProject::OnBnClickedOk()							    //�������� ����������� ���� ����� �.���� "��������� ����� �����"
{
	//TLandProperties Prop;
	if(IsFileExists(GetStrFromEdit(&m_EditPath))==false)            //��� ������ ��������� ���� � �����, ��������� ���������
	{
		MessageBox("��������� ���� �� ����������. ");
		return;
	}
	if( GetStrFromEdit(&m_EditHeight)==""&& GetStrFromEdit(&m_EditWight)=="")//���� �� ��������� ���� �������� ����� - ���������
	{
		MessageBox("������� ������ ����� �����!");
		return;
	}
	*h=GetStrFromEdit(&m_EditHeight);	//���������� ���� ������
	*w=GetStrFromEdit(&m_EditWight);	//���������� ���� ������
	int size;
	int wI=atoi(w->GetBuffer()),hI=atoi(h->GetBuffer());

	if(wI*hI<0||wI*hI>GetFileSize(GetStrFromEdit(&m_EditPath)))
	{
		MessageBox("��������� ������� ����� ����� �� ����������� � �������� �����!");
		return;
	}
	
	*File=GetStrFromEdit(&m_EditPath);  //���������� ���� ���� � �����
	OnOK();
	/*Prop.LandFile = GetStrFromEdit(&m_EditPath);
	Prop.height=atoi(GetStrFromEdit(&m_EditHeight));
	Prop.width=atoi(GetStrFromEdit(&m_EditWight));
	theApp.GLContainer.Landshaft.Init(Prop);*/
	//theApp.m_pMainWnd->RedrawWindow();
	
}

BOOL CDlgCreateProject::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(lpszTemplateName, pParentWnd);
}
