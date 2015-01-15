#pragma once
#include "Picture.h"

// СDrawFrame frame
class CDrawFrame :public CFrameWndEx
{
	DECLARE_DYNCREATE(CDrawFrame)
	DECLARE_MESSAGE_MAP()
	CScrollBar m_ScrollBar;
public:
	
	CPicture *picture;
	int MainW, MainH;
	//CDC dcMemory;							//контекcт в памяти
	int W,H;

	int GetW(){return W;}
	int GetH(){return H;}
	CDC* GetMemoryDC(){return (picture->dcMemory);}
	CDrawFrame(){}							// конструктор
	virtual ~CDrawFrame(){}
	void Resize(int MainW,int MainH)
	{
		this->MainW=MainW;
		this->MainH=MainH;
		//picture->Resize(picture->W,picture->H);
		ResizeMap(W,H);
	}
public:
	void ResizeMap(int w, int h);//изменения карты, вызывается при создании окна, вместе с главным окном программы
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
