// СDrawFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Terrain.h"
#include "DrawFrame.h"


// СDrawFrame
IMPLEMENT_DYNCREATE(CDrawFrame, CFrameWndEx)
BEGIN_MESSAGE_MAP(CDrawFrame, CFrameWndEx)

	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()
void CDrawFrame::ResizeMap(int w, int h)			//изменения карты, вызывается нажатии на кнопку Изменить размер
{
/*	int oldW,oldH;
	oldW=W;
	oldH=H;
	CDC dcTemp;
	CBitmap dcTempBmp;									//создали битмап
	dcTemp.DeleteDC();									//удалили предыдущиц контекст
	dcTemp.CreateCompatibleDC(NULL);					//создаем новый контекст
	CClientDC *dc=new CClientDC(this);
	dcTempBmp.CreateCompatibleBitmap(dc, W,H);			//создаем битмап размером в карту высот
	dcTemp.SelectObject(&dcTempBmp);					//контексту передаем битмап dcMemoryBmp(что бы было где рисовать)
	dcTemp.BitBlt(0,0,W,H,&dcMemory,0,0,SRCCOPY);
*/

	
		this->W=w;
		this->H=h;
		
		if(W*H*MainW*MainH==0)
		 return;
		

		CRect r;
		GetClientRect(r);

	   if(MainW>W+40)
	   {	
		   this->SetScrollRange(SB_HORZ,0,0);
		   this->MoveWindow(20,180,w+4,r.Height()+4);
		   
	   }
	   else
	   {
		   SetScrollRange(SB_HORZ,0,w-MainW);
		   this->MoveWindow(20,180,MainW-40+4,r.Height()+4);

	   }
	   GetClientRect(r);
	   if(MainH>H+200)
	   {
		   this->SetScrollRange(SB_VERT,0,0);
		   this->MoveWindow(20,180,r.Width()+4,h+4);
	   }
	   else
	   {
		   this->SetScrollRange(SB_VERT,0,h - MainH);
		   this->MoveWindow(20,180,r.Width()+4,MainH-200+4);
	   }
//	  	picture->Resize(w,h);
/*	CBitmap dcMemoryBmp;//создали битмап
	dcMemory.DeleteDC();//удалили предыдущий контекст
	dcMemory.CreateCompatibleDC(GetDC());//создаем новый контекст
	dcMemoryBmp.CreateCompatibleBitmap(dc, W,H);//создаем битмап размером в карту высот
	dcMemory.SelectObject(&dcMemoryBmp);//контексту передаем битмап dcMemoryBmp(что бы было где рисовать)
	dcMemory.Rectangle(-2,-2,W+2,H+2);//закрасили контекст белым квадратом
	dcMemory.BitBlt(0,0,oldW,oldH,&dcTemp,0,0,SRCCOPY);
*/
	}

void CDrawFrame::OnPaint()// создается вместе с главным окном
{
	CPaintDC dc(this); 
//	dc.BitBlt(0,0,W,H,&dcMemory,0,0,SRCCOPY);//копируем с контекста dcMemory в CPaintDC dc(вывели в окно)
	CFrameWndEx::OnPaint();
}

int CDrawFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CDrawFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int delta =3;
	int CurPos = GetScrollPos(SB_HORZ);
	switch (nSBCode)
	{
		case SB_LINELEFT:      // Scroll to far left.
			if(CurPos>=3)
			{
				delta = -3;
				CurPos-=3;
			}
			break;
		case  SB_LINERIGHT:      // Scroll to far right.
			if(CurPos<picture->W-MainW)
			{
			delta = 3;
			CurPos+=3;
			}
			break;
		case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
			CurPos = nPos;      // of the scroll box at the end of the drag operation.
		break;
	}
		picture->position.x=-CurPos;
		picture->MoveWindow(picture->position.x,picture->position.y,picture->W,picture->H,1);
	SetScrollPos(SB_HORZ,CurPos,1);

	CFrameWndEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDrawFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int delta =3;
	int CurPos = GetScrollPos(SB_VERT);

	switch (nSBCode)
	{
		case SB_LINEUP:      
			if(CurPos>=1)
			{
				delta = -3;
				CurPos-=3;
			}
			break;
		case  SB_LINEDOWN: 
			  
			if(CurPos<picture->H-MainH)
			{
			delta = 3;
			CurPos+=3;
			}	
			break;
		case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
			CurPos = nPos;      // of the scroll box at the end of the drag operation.
		break;
	}
	picture->position.y=-CurPos;
	picture->MoveWindow(picture->position.x,picture->position.y,picture->W,picture->H,1);
	SetScrollPos(SB_VERT,CurPos,1);
	CFrameWndEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
