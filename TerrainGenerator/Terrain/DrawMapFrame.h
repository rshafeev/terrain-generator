#pragma once
#include "DrawFrame.h"

class CDrawMapFrame : public CDrawFrame
{
	bool activeBtn;
public:
	
	CDrawMapFrame(void);
	bool LoadMapFromFile(CString FileName,int w,int h);
	//void DrawTrees (CDC *pDC);
	~CDrawMapFrame(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
