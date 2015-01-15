#pragma once
#include "Picture.h"

// �DrawFrame frame
class CDrawFrame :public CFrameWndEx
{
	DECLARE_DYNCREATE(CDrawFrame)
	DECLARE_MESSAGE_MAP()
	CScrollBar m_ScrollBar;
public:
	
	CPicture *picture;
	int MainW, MainH;
	//CDC dcMemory;							//������c� � ������
	int W,H;

	int GetW(){return W;}
	int GetH(){return H;}
	CDC* GetMemoryDC(){return (picture->dcMemory);}
	CDrawFrame(){}							// �����������
	virtual ~CDrawFrame(){}
	void Resize(int MainW,int MainH)
	{
		this->MainW=MainW;
		this->MainH=MainH;
		//picture->Resize(picture->W,picture->H);
		ResizeMap(W,H);
	}
public:
	void ResizeMap(int w, int h);//��������� �����, ���������� ��� �������� ����, ������ � ������� ����� ���������
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
