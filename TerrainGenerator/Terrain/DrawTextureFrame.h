#pragma once
#include "DrawFrame.h"
class CDrawTextureFrame: public CDrawFrame
{
	DECLARE_MESSAGE_MAP()
public:
	void LoadTextureFromFile(CString FileName);

	CDrawTextureFrame(void);
	~CDrawTextureFrame(void);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
