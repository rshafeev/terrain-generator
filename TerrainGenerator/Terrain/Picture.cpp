// Picture.cpp : implementation file
//

#include "stdafx.h"
#include "Terrain.h"
#include "Picture.h"


// CPicture

IMPLEMENT_DYNAMIC(CPicture, CFrameWndEx)

CPicture::CPicture(int WindowType)
{
	position = CPoint(0,0);
	oldP = CPoint(0,0);
	this->WindowType = WindowType;
}

CPicture::~CPicture()
{
}


BEGIN_MESSAGE_MAP(CPicture, CFrameWndEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CPicture message handlers


void CPicture::DrawTrees (CDC *pDC)
{
	int d = 5;
	for(int i=0;i<TreesProp.size();i++)
	{
		CPoint point;
		CPen pen;
		pen.CreatePen(PS_SOLID,2,RGB(255,5,5));
		pDC->SelectObject(&pen);
		point.x = TreesProp[i].x;
		point.y = TreesProp[i].y;
	    pDC->MoveTo(point.x-d, point.y);//горизонтальная
		pDC->LineTo(point.x+d, point.y);
		pDC->MoveTo(point.x, point.y-d);//вертикальная
		pDC->LineTo(point.x, point.y+d);
	}
}
void CPicture::OnPaint()
{
	CPaintDC dc(this); 
		dc.BitBlt(0,0,W,H,dcMemory,0,0,SRCCOPY);//копируем с контекста dcMemory в CPaintDC dc(вывели в окно)
		if(WindowType==0)
		{
			DrawTrees(&dc);
		}
}

void CPicture::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);
	
}

int CPicture::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	dcMemory = new CDC();
	return 0;
}

void CPicture::OnLButtonDown(UINT nFlags, CPoint point)
{
		int d = 8;
	activeBtn=true;
	if (((CMainFrame*)theApp.m_pMainWnd)->ValueOfButton==3)
	{
		CClientDC paint(this);
				CPen pen;
				pen.CreatePen(PS_SOLID,2,RGB(255,5,5));
		paint.SelectObject(&pen);
	    paint.MoveTo(point.x-d, point.y);//горизонтальная
		paint.LineTo(point.x+d, point.y);
		paint.MoveTo(point.x, point.y-d);//вертикальная
		paint.LineTo(point.x, point.y+d);
		TTreeProperties prop;

		prop.x = point.x;
		prop.y = point.y;
		prop.r = atoi(((CMainFrame*)theApp.m_pMainWnd)->m_Edit_TreesHeight->GetEditText());
		TreesProp.push_back(prop);
	}
	oldP=point;

	CFrameWndEx::OnLButtonDown(nFlags, point);
}

void CPicture::OnLButtonUp(UINT nFlags, CPoint point)
{
	activeBtn = false;
	CFrameWndEx::OnLButtonUp(nFlags, point);
}

void CPicture::OnMouseMove(UINT nFlags, CPoint point)
{
	if	(((CMainFrame*)(theApp.m_pMainWnd))->ValueOfButton==1&&activeBtn==true)
{	
	CClientDC paint(this);
	CPen pen;
		pen.CreatePen(PS_SOLID,2,RGB(255,5,5));
		dcMemory->SelectObject(&pen);
		paint.SelectObject(&pen);
	
		paint.MoveTo(oldP);
		paint.LineTo(point);
		dcMemory->MoveTo(oldP);
		dcMemory->LineTo(point);
		paint.SetPixel(point.x,point.y,RGB(5,5,5));
		dcMemory->SetPixel(point.x,point.y,RGB(5,5,5));
}
oldP = point;
if (((CMainFrame*)theApp.m_pMainWnd)->ValueOfButton==6&&activeBtn==true)
{
	int d=8;
	CClientDC paint(this);
	CBrush brush;
	brush.CreateSolidBrush(RGB(5,5,5));
	dcMemory->SelectObject(&brush);
}
	CFrameWndEx::OnMouseMove(nFlags, point);
}
