#pragma once


// CGLFrame frame

class CGLFrame : public CFrameWnd
{
struct TCamera
{
  CVector3 Pos; 
  CVector3 Angle; 
  double scale;
  bool  PressingLB,PressingRB;		//нажата ли лева€/права€ кнопка
  CVector3 Center;					//цент окружности, по которой вращаетс€ камера
  float R;							//радиус
  float walkbiasangle;
};
	DECLARE_DYNCREATE(CGLFrame)
	DECLARE_MESSAGE_MAP()
protected:
    
	 float PosLight[4];					  //позици€ источника света
	 TCamera Camera;
	 HGLRC  hRC;						 // ѕосто€нный контекст рендеринга
	 HDC  hDC;							 // ѕриватный контекст устройства GDI
	 CDC *pDC;
	public:
		void CGLFrame::DestroyGL(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	wglMakeCurrent( NULL, NULL );
    wglDeleteContext( hRC );
	ReleaseDC(pDC);
	
	pDC=NULL;
	hDC=NULL;
	hRC=NULL;
}

		bool Init();
		bool InitGL();
		void RenderScene();
		CGLFrame();
		virtual ~CGLFrame();
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnDestroy();
};


