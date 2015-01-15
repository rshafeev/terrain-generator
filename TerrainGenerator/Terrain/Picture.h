#pragma once
#include "GLlib.h"
#include <vector>
using namespace std;
// CPicture

class CPicture : public CFrameWndEx
{
	DECLARE_DYNAMIC(CPicture)
	bool activeBtn;
	int WindowType;
	void DrawTrees (CDC *pDC);
public:
	CPoint oldP;
	vector <TTreeProperties> TreesProp;
	int W;
	int H;	
	CDC *dcMemory;							//контекcт в памяти
	CPoint position;
	CPicture(int WindowType);
	virtual ~CPicture();
	void Resize(int w, int h)
	{
		W = w;
		H = h;
		CBitmap dcMemoryBmp;
		
		//CClientDC *dc = GetDC();
		dcMemory->DeleteDC();//удалили предыдущий контекст
		dcMemory->CreateCompatibleDC(NULL);//создаем новый контекст
		dcMemoryBmp.CreateCompatibleBitmap(GetDC(), w,h);//создаем битмап размером в карту высот
		dcMemory->SelectObject(&dcMemoryBmp);//контексту передаем битмап dcMemoryBmp(что бы было где рисовать)
		CBrush br;
		br.CreateSolidBrush(RGB(128,128,128));
		dcMemory->SelectObject(br);
		dcMemory->Rectangle(-2,-2,W+2,H+2);//закрасили контекст белым квадратом
		MoveWindow(0,0,w,h,1);
		
		/*int oldW,oldH;
		oldW=W;
		oldH=H;
		CDC dcTemp;
		CBitmap dcTempBmp,dcMemoryBmp;									//создали битмап
		dcTemp.DeleteDC();									//удалили предыдущиц контекст
		dcTemp.CreateCompatibleDC(NULL);					//создаем новый контекст
		
		dcTempBmp.CreateCompatibleBitmap(dc, W,H);			//создаем битмап размером в карту высот
		dcTemp.SelectObject(&dcTempBmp);					//контексту передаем битмап dcMemoryBmp(что бы было где рисовать)
		dcTemp.BitBlt(0,0,W,H,&dcMemory,0,0,SRCCOPY);

		dcMemory.DeleteDC();//удалили предыдущий контекст
		dcMemory.CreateCompatibleDC(GetDC());//создаем новый контекст
		dcMemoryBmp.CreateCompatibleBitmap(dc, w,h);//создаем битмап размером в карту высот
		dcMemory.SelectObject(&dcMemoryBmp);//контексту передаем битмап dcMemoryBmp(что бы было где рисовать)
		

		W = w;
		H = h;

		CBrush br;
		br.CreateSolidBrush(RGB(200,100,5));
		dcMemory.SelectObject(&br);
		dcMemory.Rectangle(-2,-2,W+2,H+2);//закрасили контекст белым квадратом
		dcMemory.BitBlt(0,0,oldW,oldH,&dcTemp,0,0,SRCCOPY);
		MoveWindow(0,0,w,h,1);*/
	}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


