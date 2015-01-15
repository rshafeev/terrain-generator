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
	CDC *dcMemory;							//������c� � ������
	CPoint position;
	CPicture(int WindowType);
	virtual ~CPicture();
	void Resize(int w, int h)
	{
		W = w;
		H = h;
		CBitmap dcMemoryBmp;
		
		//CClientDC *dc = GetDC();
		dcMemory->DeleteDC();//������� ���������� ��������
		dcMemory->CreateCompatibleDC(NULL);//������� ����� ��������
		dcMemoryBmp.CreateCompatibleBitmap(GetDC(), w,h);//������� ������ �������� � ����� �����
		dcMemory->SelectObject(&dcMemoryBmp);//��������� �������� ������ dcMemoryBmp(��� �� ���� ��� ��������)
		CBrush br;
		br.CreateSolidBrush(RGB(128,128,128));
		dcMemory->SelectObject(br);
		dcMemory->Rectangle(-2,-2,W+2,H+2);//��������� �������� ����� ���������
		MoveWindow(0,0,w,h,1);
		
		/*int oldW,oldH;
		oldW=W;
		oldH=H;
		CDC dcTemp;
		CBitmap dcTempBmp,dcMemoryBmp;									//������� ������
		dcTemp.DeleteDC();									//������� ���������� ��������
		dcTemp.CreateCompatibleDC(NULL);					//������� ����� ��������
		
		dcTempBmp.CreateCompatibleBitmap(dc, W,H);			//������� ������ �������� � ����� �����
		dcTemp.SelectObject(&dcTempBmp);					//��������� �������� ������ dcMemoryBmp(��� �� ���� ��� ��������)
		dcTemp.BitBlt(0,0,W,H,&dcMemory,0,0,SRCCOPY);

		dcMemory.DeleteDC();//������� ���������� ��������
		dcMemory.CreateCompatibleDC(GetDC());//������� ����� ��������
		dcMemoryBmp.CreateCompatibleBitmap(dc, w,h);//������� ������ �������� � ����� �����
		dcMemory.SelectObject(&dcMemoryBmp);//��������� �������� ������ dcMemoryBmp(��� �� ���� ��� ��������)
		

		W = w;
		H = h;

		CBrush br;
		br.CreateSolidBrush(RGB(200,100,5));
		dcMemory.SelectObject(&br);
		dcMemory.Rectangle(-2,-2,W+2,H+2);//��������� �������� ����� ���������
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


