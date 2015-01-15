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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Terrain.h"
#include "DrawMapFrame.h"
#include "MainFrm.h"
#include "DlgCreateProject.h"
#include "GLFrame.h"
#include "DialogPencil.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define ID_EDIT_LANDWIGHT  100001
#define ID_EDIT_LANDHEIGHT 100002
#define ID_BUTTON_LOADLAND 100003
#define ID_BUTTON_PENCIL   100004
#define ID_BUTTON_ARROW    100005
#define ID_BUTTON_SAVE     100006
#define ID_BUTTON_DELETEALL  100007
#define ID_BUTTON_LOAD  100008
#define ID_BUTTON_TEXTURE  100009
#define ID_BUTTON_RTEXTURE  1000010
#define ID_BUTTON_GTEXTURE  1000011
#define ID_BUTTON_BTEXTURE  1000012
#define ID_EDIT_TEXTUREWIGHT  1000013
#define ID_EDIT_TEXTUREHEIGHT  100014
#define ID_BUTTON_TPENCIL   1000015
#define ID_BUTTON_TARROW    1000016
#define ID_BUTTON_TSAVE     1000017
#define ID_BUTTON_TDELETEALL  1000018
#define ID_BUTTON_CHANGESIZE  1000019
#define ID_BUTTON_LOADTEXTUREFROMFILE 1000020
#define ID_EDIT_ZMAX  1000021
#define ID_EDIT_ZMIN 1000022
#define ID_EDIT_X  1000023
#define ID_EDIT_Y 1000024
#define ID_BUTTON_CHANGETEXTURESIZE  1000025
#define ID_BUTTON_ADDTREES 1000027
#define ID_EDIT_TREESHEIGHT 1000030
#define ID_EDIT_TREESWEIGHT 1000031
#define ID_EDIT_STEPSIZE 1000032
#define ID_BUTTON_SPRAYER 1000033
#define ID_BUTTON_BRUSH 1000134
#define ID_BUTTON_LASTIC 1000135


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND (ID_BUTTON_LOADLAND,OnBtnLoadMapClick)
	ON_COMMAND (ID_BUTTON_LOAD,OnBtnLoadProject)//////
	ON_COMMAND (ID_BUTTON_PENCIL, OnBtnPencil)
	ON_COMMAND (ID_BUTTON_ARROW , OnBtnArrow)
	ON_COMMAND (ID_BUTTON_DELETEALL, OnBtnDeleteAll)
	ON_COMMAND (ID_BUTTON_SAVE, OnBtnSave)
	ON_COMMAND (ID_BUTTON_RTEXTURE, OnBtnRTexture)
	ON_COMMAND (ID_BUTTON_GTEXTURE, OnBtnGTexture)
	ON_COMMAND (ID_BUTTON_BTEXTURE, OnBtnBTexture)
	ON_COMMAND (ID_BUTTON_CHANGETEXTURESIZE, OnBtnChangeTextureSize)
	ON_COMMAND (ID_BUTTON_TPENCIL, OnBtnTPencil)
	ON_COMMAND (ID_BUTTON_TARROW , OnBtnTArrow)
	ON_COMMAND (ID_BUTTON_TDELETEALL, OnBtnTDeleteAll)
	ON_COMMAND (ID_BUTTON_TSAVE, OnBtnTSave)
	ON_COMMAND (ID_FILE_NEW,OnNewProject)
	ON_COMMAND (ID_FILE_OPEN,OnOpenProject)
	ON_COMMAND (ID_FILE_SAVE,OnSaveProject)
	ON_COMMAND (ID_FILE_CLOSE,OnCloseProject)
	ON_COMMAND (ID_BUTTON_CHANGESIZE, OnBtnChangeSize)
	ON_COMMAND (ID_BUTTON_LOADTEXTUREFROMFILE, OnBtnLoadTextureFromFile)
	ON_COMMAND (ID_BUTTON_ADDTREES,OnBtnAddTrees)
	ON_COMMAND (ID_BUTTON_SPRAYER,OnBtnSprayer)
	ON_COMMAND (ID_BUTTON_BRUSH,OnBtnBrush)
	ON_COMMAND (ID_BUTTON_LASTIC,OnBtnLastic)
	ON_BN_CLICKED(IDD_DIALOGPENCIL,&CMainFrame::OnBtnPencil)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);// add member initialization code here
	ValueOfButton=0;

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)						//���������� ��� �������� �������� ����
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	OnApplicationLook(theApp.m_nAppLook);// set the visual manager and style based on persisted value
	CreateRibbonBar();
	theApp.DrawMapFrame=new  CDrawMapFrame();
	theApp.DrawMapFrame->Create(NULL,"DrawLand",WS_CHILD,rectDefault,this);			//�������� ��������������� ���� ��� ��������� "����� �����"
	theApp.DrawMapFrame->ShowWindow(SW_SHOW);
	theApp.DrawMapFrame->MoveWindow(20,180,100,100);

	theApp.DrawTextureFrame=new  CDrawTextureFrame();
	theApp.DrawTextureFrame->Create(NULL,"DrawTexture",WS_CHILD,rectDefault,this);	//�������� ���� ��������� ��� "��������"
	theApp.DrawTextureFrame->ShowWindow(SW_HIDE);
	theApp.DrawTextureFrame->MoveWindow(20,180,100,100);

	OnNewProject();
	
	CString Tex1File,Tex2File,Tex3File;
	Tex1File = "Shaders\\textureL0.bmp";
	Tex2File = "Shaders\\textureL1.bmp";
	Tex3File = "Shaders\\textureL2.bmp";

	RImage=new CImage;
	GImage=new CImage;
	BImage=new CImage;

	RImage->Load(Tex1File);
	GImage->Load(Tex2File);
	BImage->Load(Tex3File);
	
	return 0;

}
void CMainFrame::CreateRibbonBar()//�������� �����
{
	Ribbon.Create(this);					//�������� � ���� ����
	CreatePageLand();						//�������� ������� �������� ������� ����� �����
	CreatePageTexture();					//�������� ������� �������� ������� ��������
	CreatePageLoadProject();				//�������� ������� �������� ������� ���������


//****************************
	Ribbon.SetApplicationButton(&m_MainButton, CSize (45, 45));					//�������������� ����

	CMFCRibbonMainPanel* pMainPanel = Ribbon.AddMainCategory("dd", IDB_FILESMALL, IDB_FILELARGE);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, "����� ������", 0, 0));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, "������� ������", 1, 1));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, "��������� ������", 2, 2));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, "�������", -1, -1));

//**************
}



void CMainFrame::CreatePageLand()				//������� ����� �����
{
	CMFCRibbonCategory* category = Ribbon.AddCategory("����� �����",IDB_RIBBON_LANDsSMALL,/*IDB_RIBBON_LANDsLARGE*/IDB_FILELARGE);
	CMFCRibbonPanel* panel = category->AddPanel("�������");
	CMFCRibbonPanel* PanelInsrument = category->AddPanel("������ ������������");


	

	m_Edit_LandWight=new CMFCRibbonEdit(ID_EDIT_LANDWIGHT,100, _T("������ :\nsb"), -1);
	m_Edit_LandWight->SetEditText("100");
	panel->Add(m_Edit_LandWight);

	m_Edit_LandHeight=new CMFCRibbonEdit(ID_EDIT_LANDHEIGHT,100, _T("������   :\nsb"), -1);
	m_Edit_LandHeight->SetEditText("100");
	panel->Add(m_Edit_LandHeight);

	m_Btn_ChangeSize = new CMFCRibbonButton(ID_BUTTON_CHANGESIZE,"�������� ������");
	panel->Add(m_Btn_ChangeSize);
	//*********************************************************************************************************************

	m_Btn_Arrow = new CMFCRibbonButton(ID_BUTTON_ARROW,"������",7);
	PanelInsrument->Add(m_Btn_Arrow);

	m_Btn_Pencil = new CMFCRibbonButton(ID_BUTTON_PENCIL,"��������",13);
	PanelInsrument->Add(m_Btn_Pencil);

	m_Btn_DeleteAll = new CMFCRibbonButton(ID_BUTTON_DELETEALL,"�������� ����",12);
	PanelInsrument->Add(m_Btn_DeleteAll);
	PanelInsrument->AddSeparator();

	m_Btn_Sprayer = new CMFCRibbonButton(ID_BUTTON_SPRAYER,"�����������");
	PanelInsrument->Add(m_Btn_Sprayer);

	m_Btn_Brush = new CMFCRibbonButton(ID_BUTTON_BRUSH,"�����");
	PanelInsrument->Add(m_Btn_Brush);

	m_Btn_Lastic = new CMFCRibbonButton(ID_BUTTON_LASTIC,"������");
	PanelInsrument->Add(m_Btn_Lastic);

	//*********************************************************************************************************************
	
	CMFCRibbonPanel* AddTrees = category->AddPanel("�������� ������");

	m_Edit_TreesHeight=new CMFCRibbonEdit(ID_EDIT_TREESHEIGHT,100, _T("������   :\nsb"), -1);
	m_Edit_TreesHeight->SetEditText("20");
	AddTrees->Add(m_Edit_TreesHeight);

	m_Edit_TreesWeight=new CMFCRibbonEdit(ID_EDIT_TREESWEIGHT,100, _T("������ :\nsb"), -1);
	m_Edit_TreesWeight->SetEditText("100");
	AddTrees->Add(m_Edit_TreesWeight);

	m_Btn_AddTrees = new CMFCRibbonButton(ID_BUTTON_ADDTREES,"�������� ������",14);
	AddTrees->Add(m_Btn_AddTrees);

	//*********************************************************************************************************************

	CMFCRibbonPanel* save = category->AddPanel("���������");
	m_Btn_Save = new CMFCRibbonButton(ID_BUTTON_SAVE,"���������",IDB_RIBBON_LANDsLARGE,3);
	save->Add(m_Btn_Save);

	//*********************************************************************************************************************

	CMFCRibbonPanel* load = category->AddPanel("��������� � �����");
	m_Btn_LoadLand = new CMFCRibbonButton(ID_BUTTON_LOADLAND,"��������� � �����",IDB_WRITELARGE,1);
	load->Add(m_Btn_LoadLand);
}

void CMainFrame::CreatePageTexture()		//������� ��������
{
	CMFCRibbonCategory* category = Ribbon.AddCategory("��������",IDB_RIBBON_LANDsSMALL,IDB_FILELARGE);
	CMFCRibbonPanel* size = category->AddPanel("�������");
	m_Btn_Texture=new CMFCRibbonCheckBox(ID_BUTTON_TEXTURE,"��������� ����������");
	size->Add(m_Btn_Texture);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	m_Edit_TextureWight=new CMFCRibbonEdit(ID_EDIT_TEXTUREWIGHT,100, _T("������ :\nsb"), -1);
	m_Edit_TextureWight->SetEditText("500");
	size->Add(m_Edit_TextureWight);

	m_Edit_TextureHeight=new CMFCRibbonEdit(ID_EDIT_TEXTUREHEIGHT,100, _T("������   :\nsb"), -1);
	m_Edit_TextureHeight->SetEditText("500");
	size->Add(m_Edit_TextureHeight);

	m_Btn_ChangeTextureSize = new CMFCRibbonButton(ID_BUTTON_CHANGETEXTURESIZE,"�������� ������",IDB_WRITELARGE,4);
	size->Add(m_Btn_ChangeTextureSize);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* texture = category->AddPanel("��������");
	m_Btn_RTexture = new CMFCRibbonButton(ID_BUTTON_RTEXTURE,"R-��������",11);
	texture->Add(m_Btn_RTexture);

	m_Btn_GTexture = new CMFCRibbonButton(ID_BUTTON_GTEXTURE,"G-��������",11);
	texture->Add(m_Btn_GTexture);

	m_Btn_BTexture = new CMFCRibbonButton(ID_BUTTON_BTEXTURE,"B-��������",11);
	texture->Add(m_Btn_BTexture);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* panelInstruments = category->AddPanel("������ ������������");
	m_Btn_TArrow = new CMFCRibbonButton(ID_BUTTON_TARROW,"������",7);
	panelInstruments->Add(m_Btn_TArrow);

	m_Btn_TPencil = new CMFCRibbonButton(ID_BUTTON_TPENCIL,"��������",13);
	panelInstruments->Add(m_Btn_TPencil);

	m_Btn_TDeleteAll = new CMFCRibbonButton(ID_BUTTON_TDELETEALL,"�������� ����",12);
	panelInstruments->Add(m_Btn_TDeleteAll);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* LoadfromFile = category->AddPanel("����� �����");
	m_Btn_LoadTextureFromFile = new CMFCRibbonButton(ID_BUTTON_LOADTEXTUREFROMFILE,"��������� � �����",IDB_WRITELARGE,1);
	LoadfromFile->Add(m_Btn_LoadTextureFromFile);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* Tsave = category->AddPanel("���������");
	m_Btn_TSave = new CMFCRibbonButton(ID_BUTTON_TSAVE,"���������",IDB_WRITELARGE,3);
	Tsave->Add(m_Btn_TSave);

	
}


void CMainFrame::CreatePageLoadProject()		 // ������� ���������
{
	CMFCRibbonCategory* category = Ribbon.AddCategory("������",IDB_RIBBON_LANDsSMALL,/*IDB_RIBBON_LANDsLARGE*/IDB_FILELARGE);
	CMFCRibbonPanel* map = category->AddPanel("Z-���������������");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Edit_ZMin=new CMFCRibbonEdit(ID_EDIT_ZMIN,100, _T("Z-min :\nsb"), -1);
	m_Edit_ZMin->SetEditText("0");
	map->Add(m_Edit_ZMin);

	m_Edit_ZMax=new CMFCRibbonEdit(ID_EDIT_ZMAX,100, _T("Z-max :\nsb"), -1);
	m_Edit_ZMax->SetEditText("255");
	map->Add(m_Edit_ZMax);

	m_Edit_StepSize=new CMFCRibbonEdit(ID_EDIT_STEPSIZE,100, _T("���   :\nsb"), -1);
	m_Edit_StepSize->SetEditText("16");
	map->Add(m_Edit_StepSize);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* max = category->AddPanel("����������");
	m_Edit_X=new CMFCRibbonEdit(ID_EDIT_X,50, _T("X :\nsb"), -1);
	m_Edit_X->SetEditText("1");
	max->Add(m_Edit_X);

	m_Edit_Y=new CMFCRibbonEdit(ID_EDIT_Y,50, _T("Y :\nsb"), -1);
	m_Edit_Y->SetEditText("1");
	max->Add(m_Edit_Y);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* load = category->AddPanel("��������");
	m_Btn_LoadProject = new CMFCRibbonButton(ID_BUTTON_LOAD,"���������",IDB_WRITELARGE);
	load->Add(m_Btn_LoadProject);

}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	//pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
void CMainFrame::OnBtnLoadMapClick()						//����� ����������� ���� ��� ����� �����
{
	  CString wStr,hStr,fileStr;
	  CDlgCreateProject *DlgCreateProject=new CDlgCreateProject(&wStr,&hStr,&fileStr);
	  if (DlgCreateProject->DoModal()==IDOK)									
	  {
		  theApp.DrawMapFrame->LoadMapFromFile(fileStr,atoi(wStr),atoi(hStr));	//�������� ������� �������� � ����� ����� ����� � ����� � �� �����
		  m_Edit_LandWight->SetEditText(wStr);								    //�������� ��������� ������ �������� � ����
	      m_Edit_LandHeight->SetEditText(hStr);									//�������� ��������� ������ �������� � ����
	  }
	 

}

void CMainFrame::OnBtnChangeSize()								//��������� ���������� ����������� ���� � "����� �����"
{
theApp.DrawMapFrame->ResizeMap(atoi(m_Edit_LandWight->GetEditText()),atoi(m_Edit_LandHeight->GetEditText()));//�������� � ������������� �������� ������ � ������ ����������� ����

}



void CMainFrame::OnBtnLoadProject()		// ������� ���������� �������� ��� ������� �� ����� "������"
{
//���������� ��� ������ � ��������� � ������ Landshaft
	CVector2 z,scale;
	z.x = atof(m_Edit_ZMin->GetEditText());					// ��������������� �����������  Min
	z.y = atof(m_Edit_ZMax->GetEditText());					//��������������� ����������� Max
	scale.x=atof(m_Edit_X->GetEditText());					//���������� �� �
	scale.y=atof(m_Edit_Y->GetEditText());					//���������� �� �
	theApp.GLContainer = new CGLContainer();
	theApp.GLContainer->Create(z,scale,RImage,GImage, BImage);
	
//������� GL-����
	/*
	CString Tex1File,Tex2File,Tex3File,TexVec;
	
Tex1File = "Shaders\\textureL0.bmp";
Tex2File = "Shaders\\textureL1.bmp";
Tex3File = "Shaders\\textureL2.bmp";
TexVec   = "Shaders\\texVec.bmp";
	*/
	CGLFrame *GLFrame=new CGLFrame; 
	GLFrame->Create(NULL,"Terrain3D",WS_MAXIMIZE|WS_POPUPWINDOW,CRect(0,0,100,100),NULL);	//������� ���� ������� �� ���� �����
	GLFrame->ShowWindow(SW_HIDE);															//������ ����
	CRect t;//��� �������� ��������� ������������ ������ CRect, ������� ����� ������ ����������: l � ����� ����������, t - ������� ����������, r � ������ ����������, b � ������ ����������.
	GLFrame->GetWindowRect(t);
	GLFrame->MoveWindow(-3,-3,t.Width()+5,t.Height()+5,0);									//������ ���������� ����
	///

	for (int i=0; i<theApp.DrawMapFrame->picture->TreesProp.size(); i++)
		theApp.GLContainer->AddTree(theApp.DrawMapFrame->picture->TreesProp[i]);						//���������� �������� �� ��������
	
	GLFrame->ShowWindow(SW_SHOW);
	this->EnableWindow(0);																	//�������� ���� ���������
}

void CMainFrame::OnBtnPencil ()				//�������� � ����� �����
{
CDialogPencil pencil;
	pencil.DoModal();
/*ValueOfButton=1;                            //���� ������ ������ 1
OnMouseMove (0,0);						//�������� ������� */
}

void CMainFrame::OnBtnArrow()//������ � ����� �����
{
ValueOfButton=0;
}

void CMainFrame::OnBtnAddTrees()		//��������� �� ����� ����� �������
{
	ValueOfButton=3;
	OnLButtonDown(0,0);					//������� ��������� ��������� (��������)
}



void CMainFrame::OnBtnDeleteAll()		// ������� ������� ���� � ����� �����
{
	ValueOfButton=4;
	OnLButtonUp(0,0);
//MessageBox("�� ������ �� ������ �������� ��!");
}

void CMainFrame::OnBtnSprayer()
{
CColorDialog Color(RGB(255,0,0),CC_FULLOPEN);
Color.DoModal();
//MessageBox ("fkjdshfk");
}

void CMainFrame::OnBtnBrush()
{
	ValueOfButton=6;
	OnMouseMove(0,0);
//MessageBox ("kist");
}

void CMainFrame::OnBtnLastic()
{
MessageBox ("lastik");
}

void CMainFrame::OnBtnSave()			//������� ���������� ������ ����� �����
{
//MessageBox("�� ������ �� ������ ���������!");
//	theApp.GLContainer.Landshaft.LoadMapFromDC(theApp.DrawMapFrame->GetMemoryDC(),theApp.DrawMapFrame->GetW(),theApp.DrawMapFrame->GetH());
}


void CMainFrame::OnBtnRTexture()			 // ������ R-��������
{
 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"R��������(.bmp)|*.bmp||");
 File.DoModal();
 RImage->Destroy();
 RImage = new CImage;
 RImage->Load(File.GetPathName());

}

void CMainFrame::OnBtnGTexture()			// ������ G-��������
{
 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"G��������(.bmp)|*.bmp||");
 File.DoModal();
 GImage->Destroy();
 GImage = new CImage;
 GImage->Load(File.GetPathName());

}

void CMainFrame::OnBtnBTexture()			//������ B-��������
{
 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"B��������(.bmp)|*.bmp||");
 File.DoModal();
 BImage->Destroy();
 BImage = new CImage;
 BImage->Load(File.GetPathName());

}
void CMainFrame::OnBtnChangeTextureSize()
{
MessageBox("�� ������ �� ������ �������� ������!");
//theApp.DrawMapFrame->ResizeMap(atoi(m_Edit_LandWight->GetEditText()),atoi(m_Edit_LandHeight->GetEditText()));
}

void CMainFrame::OnBtnTPencil()				// ������� �������� � ��������
{
MessageBox("�� ������ �� ������ ��������!");
}

void CMainFrame::OnBtnTArrow()				//������� ������ � ��������
{
MessageBox("�� ������ �� ������ ������!");
}

void CMainFrame::OnBtnTDeleteAll()			// ������� ������� ���� � ��������
{
MessageBox("�� ������ �� ������ �������� ��!");
}

void CMainFrame::OnBtnLoadTextureFromFile()		// ��������� � �����, ���������� ����
{
	 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"������� �������|*.bmp|�������� ��������|*.jpg||");
	  if (File.DoModal()==IDOK)
//CString fileStr = "C:\\Users\\Roma\\Desktop\\����� ����� (2)\\�������� Last\\Terrain\\Terrain\\Shaders\\texVec.bmp";	 
{
	theApp.DrawTextureFrame->LoadTextureFromFile(File.GetPathName()); //�������� ���� � �����
		  CString strW,strH;
		  strW.Format ("%d", theApp.DrawTextureFrame->GetW());
		  strH.Format ("%d", theApp.DrawTextureFrame->GetH());
		  m_Edit_TextureWight->SetEditText(strW);                           //��������  � ���� ������ ���� �������� ������
		  m_Edit_TextureHeight->SetEditText(strH);						    //��������  � ���� ������ ���� �������� ������
	  }

}

void CMainFrame::OnBtnTSave()												//��������� ������ ��������
{
MessageBox("�� ������ �� ������ ���������!");
}

/*void CMainFrame::OnBtnClickTick(CCmdUI* pCmdUI)
{

}
*/

void CMainFrame::OnPaint()				//��������� �������� ���� (��� ���������)
{
	CPaintDC dc(this); 
	CRect r;
	CBrush brush;						//�������
	brush.CreateSolidBrush(RGB(218,248,220));
	dc.SelectObject(&brush);
	this->GetClientRect(r);
	dc.Rectangle(-2,-2,r.Width()+2,r.Height()+2);
	/*if(theApp.GLContainer.Landshaft.IsStateInitial()==1)
	{
		theApp.GLContainer.Landshaft.DrawMapOnDC(&dc);
	}*/
}


void CMainFrame::OnNewProject()
{
	m_Edit_LandWight->SetEditText("500");
	m_Edit_LandHeight->SetEditText("500");
	m_Edit_TextureWight->SetEditText("500");
	m_Edit_TextureHeight->SetEditText("500");
	
	CRect r;
	GetClientRect(r);
	theApp.DrawMapFrame->Resize(r.Width(),r.Height());
	theApp.DrawMapFrame->ResizeMap(atoi(m_Edit_LandWight->GetEditText()),atoi(m_Edit_LandHeight->GetEditText()));
//	theApp.DrawMapFrame->dcMemory.Rectangle(-2,-2,atoi(m_Edit_LandWight->GetEditText())+2,atoi(m_Edit_LandHeight->GetEditText())+2);

	theApp.DrawTextureFrame->Resize(r.Width(),r.Height());
	theApp.DrawTextureFrame->ResizeMap(atoi(m_Edit_TextureWight->GetEditText()),atoi(m_Edit_TextureHeight->GetEditText()));
//	theApp.DrawTextureFrame->dcMemory.Rectangle(-2,-2,atoi(m_Edit_TextureWight->GetEditText())+2,atoi(m_Edit_TextureHeight->GetEditText())+2);

}
void CMainFrame::OnOpenProject()
{
}
void CMainFrame::OnSaveProject()
{
}
void CMainFrame::OnCloseProject()
{
	DestroyWindow();
}
void CMainFrame::OnSize(UINT nType, int cx, int cy)//
{
	CFrameWndEx::OnSize(nType, cx, cy);
		CRect r;
		GetClientRect(r);
	if(theApp.DrawMapFrame!=NULL)
	{
		theApp.DrawMapFrame->Resize(r.Width(),r.Height());  //��������� �������
	}
	if(theApp.DrawTextureFrame!=NULL)
	{
		theApp.DrawTextureFrame->Resize(r.Width(),r.Height());
	}

}
