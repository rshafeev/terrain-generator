// MyRibbon.cpp : implementation file
//

#include "stdafx.h"
#include "Terrain.h"
#include "MyRibbon.h"


// CMyRibbon

IMPLEMENT_DYNAMIC(CMyRibbon, CMFCRibbonBar)

CMyRibbon::CMyRibbon()
{

}

CMyRibbon::~CMyRibbon()
{
}


BEGIN_MESSAGE_MAP(CMyRibbon, CMFCRibbonBar)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyRibbon message handlers



void CMyRibbon::OnLButtonUp(UINT nFlags, CPoint point)// ����� ��������� �� ��������
{
	CString g=this->m_pActiveCategory->GetName();//� g �������� �������� �������� ��������� 
	//this->m_pActiveCategory->set
	if(g=="����� �����")//���� ������� ����� �����
	{
		theApp.DrawMapFrame->ShowWindow(SW_SHOW);//������ ������� ���� ����� ����� � ��������� ���� ��������
		theApp.DrawTextureFrame->ShowWindow(SW_HIDE);// � ��������� ���� ��������
	}
	else
	if(g=="��������")
	{
		theApp.DrawMapFrame->ShowWindow(SW_HIDE);//������ ��������� ���� ����� �����
		theApp.DrawTextureFrame->ShowWindow(SW_SHOW);//� ������� ���� ��������
	}	
	else
	{
		theApp.DrawMapFrame->ShowWindow(SW_HIDE);//������ ��������� ���� ����� �����
		theApp.DrawTextureFrame->ShowWindow(SW_HIDE);//� ������� ���� ��������
	}
	
	((CMainFrame*)(theApp.m_pMainWnd))->ValueOfButton =0;
	CMFCRibbonBar::OnLButtonUp(nFlags, point);
}
