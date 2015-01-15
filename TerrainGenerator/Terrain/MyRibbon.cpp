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



void CMyRibbon::OnLButtonUp(UINT nFlags, CPoint point)// выбор категории на вкладках
{
	CString g=this->m_pActiveCategory->GetName();//в g записали название активной категории 
	//this->m_pActiveCategory->set
	if(g=="Карта высот")//если выбрана карта высот
	{
		theApp.DrawMapFrame->ShowWindow(SW_SHOW);//делаем видимым окно Карты высот и невидимым окно текстуры
		theApp.DrawTextureFrame->ShowWindow(SW_HIDE);// и невидимым окно текстуры
	}
	else
	if(g=="Текстуры")
	{
		theApp.DrawMapFrame->ShowWindow(SW_HIDE);//делаем невидимым окно карты высот
		theApp.DrawTextureFrame->ShowWindow(SW_SHOW);//и видимым окно текстуры
	}	
	else
	{
		theApp.DrawMapFrame->ShowWindow(SW_HIDE);//делаем невидимым окно карты высот
		theApp.DrawTextureFrame->ShowWindow(SW_HIDE);//и видимым окно текстуры
	}
	
	((CMainFrame*)(theApp.m_pMainWnd))->ValueOfButton =0;
	CMFCRibbonBar::OnLButtonUp(nFlags, point);
}
