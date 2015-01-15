// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.h : interface of the CMainFrame class
//
#pragma once
#include "MyRibbon.h"

class CMainFrame : public CFrameWndEx
{
	//theApp.DrawMapFrame->ResizeMap(atoi(m_Edit_LandWight->GetEditText()),atoi(m_Edit_LandHeight->GetEditText()));
private:
	CMyRibbon Ribbon;
	CImage *RImage, *GImage, *BImage;
protected: 
	DECLARE_DYNAMIC(CMainFrame)
	CMFCRibbonStatusBar  m_wndStatusBar;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);//задает стиль окну
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);

	afx_msg void OnBtnLoadMapClick();
	afx_msg void OnBtnLoadProject();//////
	afx_msg void OnBtnClickTick(CCmdUI* pCmdUI);// галочка в текстуре
	afx_msg void OnBtnPencil();
	afx_msg void OnBtnArrow();
	afx_msg void OnBtnDeleteAll();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnRTexture();
	afx_msg void OnBtnGTexture();
	afx_msg void OnBtnBTexture();
	afx_msg void OnBtnTPencil();
	afx_msg void OnBtnTArrow();
	afx_msg void OnBtnTDeleteAll();
	afx_msg void OnBtnTSave();
	afx_msg void OnNewProject();//«адает начальные значение всем компонентам и объектам.(начальные настройки)
	afx_msg void OnOpenProject();
	afx_msg void OnSaveProject();
	afx_msg void OnCloseProject();
	afx_msg void OnBtnChangeSize();
	afx_msg void OnBtnChangeTextureSize();
	afx_msg void OnBtnLoadTextureFromFile();
	afx_msg void OnBtnAddTrees();
	afx_msg void OnBtnSprayer();
	afx_msg void OnBtnBrush();
	afx_msg void OnBtnLastic();
	afx_msg void OnButtonMouseDown(UINT nFlags, CPoint point);

	
	DECLARE_MESSAGE_MAP()
	void InitializeRibbon();
public:
	int ValueOfButton;
	/*
	0 - 
	1 -  арандаш
	3 - добавить дерево
	4- очистить поле
	5- распылитель
	6-кисть
	7-ластик
	
	*/
	CMFCRibbonApplicationButton m_MainButton;
	void CreateRibbonBar();
	void CreatePageLand(); //карта высот
	void CreatePageTexture(); //текстура
	void CreatePageLoadProject();//загрузка проекта
	
//PAGE1(карта высот)
	CMFCRibbonEdit *m_Edit_LandWight;
	CMFCRibbonEdit *m_Edit_LandHeight;
	CMFCRibbonButton *m_Btn_LoadLand;
	CMFCRibbonButton *m_Btn_Pencil;
	CMFCRibbonButton *m_Btn_Arrow;
	CMFCRibbonButton *m_Btn_Save;
	CMFCRibbonButton *m_Btn_DeleteAll;
	CMFCRibbonButton *m_Btn_ChangeSize;
	CMFCRibbonButton *m_Btn_AddTrees;
	CMFCRibbonEdit *m_Edit_TreesHeight;
	CMFCRibbonEdit *m_Edit_TreesWeight;
	CMFCRibbonEdit *m_Edit_StepSize;
	CMFCRibbonButton *m_Btn_Sprayer;
	CMFCRibbonButton *m_Btn_Brush;
	CMFCRibbonButton *m_Btn_Lastic;


	//PAGE2
	CMFCRibbonButton *m_Btn_Texture;
	CMFCRibbonButton *m_Btn_RTexture;
	CMFCRibbonButton *m_Btn_GTexture;
	CMFCRibbonButton *m_Btn_BTexture;
	CMFCRibbonEdit  *m_Edit_TextureWight;
	CMFCRibbonEdit  *m_Edit_TextureHeight;
	CMFCRibbonButton *m_Btn_TPencil;
	CMFCRibbonButton *m_Btn_TArrow;
	CMFCRibbonButton *m_Btn_TSave;
	CMFCRibbonButton *m_Btn_TDeleteAll;
	CMFCRibbonButton *m_Btn_LoadTextureFromFile;
	CMFCRibbonButton *m_Btn_ChangeTextureSize;
	//PAGE 3
	CMFCRibbonButton *m_Btn_LoadProject;
	CMFCRibbonEdit *m_Edit_ZMax;
	CMFCRibbonEdit *m_Edit_ZMin;
	CMFCRibbonEdit *m_Edit_X;
	CMFCRibbonEdit *m_Edit_Y;





	CMainFrame();
	virtual ~CMainFrame();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


