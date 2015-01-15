#pragma once


// CMyRibbon

class CMyRibbon : public CMFCRibbonBar
{
	DECLARE_DYNAMIC(CMyRibbon)

public:
	CMyRibbon();
	virtual ~CMyRibbon();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
};


