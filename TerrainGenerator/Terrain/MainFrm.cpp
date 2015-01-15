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

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)						//вызывается при создании главного окна
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	OnApplicationLook(theApp.m_nAppLook);// set the visual manager and style based on persisted value
	CreateRibbonBar();
	theApp.DrawMapFrame=new  CDrawMapFrame();
	theApp.DrawMapFrame->Create(NULL,"DrawLand",WS_CHILD,rectDefault,this);			//создание дополнительного окна для рисования "карта высот"
	theApp.DrawMapFrame->ShowWindow(SW_SHOW);
	theApp.DrawMapFrame->MoveWindow(20,180,100,100);

	theApp.DrawTextureFrame=new  CDrawTextureFrame();
	theApp.DrawTextureFrame->Create(NULL,"DrawTexture",WS_CHILD,rectDefault,this);	//создание окна рисования для "текстуры"
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
void CMainFrame::CreateRibbonBar()//создание ленты
{
	Ribbon.Create(this);					//создание в этом окне
	CreatePageLand();						//вызываем функцию создания вкладки карты высот
	CreatePageTexture();					//вызываем функцию создания вкладки текстуры
	CreatePageLoadProject();				//вызываем функцию создания вкладки загрузить


//****************************
	Ribbon.SetApplicationButton(&m_MainButton, CSize (45, 45));					//дополнительное меню

	CMFCRibbonMainPanel* pMainPanel = Ribbon.AddMainCategory("dd", IDB_FILESMALL, IDB_FILELARGE);
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_NEW, "Новый проект", 0, 0));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_OPEN, "Открыть проект", 1, 1));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_SAVE, "Сохранить проект", 2, 2));
	pMainPanel->Add(new CMFCRibbonButton(ID_FILE_CLOSE, "Закрыть", -1, -1));

//**************
}



void CMainFrame::CreatePageLand()				//вкладка карты высот
{
	CMFCRibbonCategory* category = Ribbon.AddCategory("Карта высот",IDB_RIBBON_LANDsSMALL,/*IDB_RIBBON_LANDsLARGE*/IDB_FILELARGE);
	CMFCRibbonPanel* panel = category->AddPanel("Размеры");
	CMFCRibbonPanel* PanelInsrument = category->AddPanel("Панель инструментов");


	

	m_Edit_LandWight=new CMFCRibbonEdit(ID_EDIT_LANDWIGHT,100, _T("Ширина :\nsb"), -1);
	m_Edit_LandWight->SetEditText("100");
	panel->Add(m_Edit_LandWight);

	m_Edit_LandHeight=new CMFCRibbonEdit(ID_EDIT_LANDHEIGHT,100, _T("Высота   :\nsb"), -1);
	m_Edit_LandHeight->SetEditText("100");
	panel->Add(m_Edit_LandHeight);

	m_Btn_ChangeSize = new CMFCRibbonButton(ID_BUTTON_CHANGESIZE,"Изменить размер");
	panel->Add(m_Btn_ChangeSize);
	//*********************************************************************************************************************

	m_Btn_Arrow = new CMFCRibbonButton(ID_BUTTON_ARROW,"Курсор",7);
	PanelInsrument->Add(m_Btn_Arrow);

	m_Btn_Pencil = new CMFCRibbonButton(ID_BUTTON_PENCIL,"Карандаш",13);
	PanelInsrument->Add(m_Btn_Pencil);

	m_Btn_DeleteAll = new CMFCRibbonButton(ID_BUTTON_DELETEALL,"Очистить поле",12);
	PanelInsrument->Add(m_Btn_DeleteAll);
	PanelInsrument->AddSeparator();

	m_Btn_Sprayer = new CMFCRibbonButton(ID_BUTTON_SPRAYER,"Распылитель");
	PanelInsrument->Add(m_Btn_Sprayer);

	m_Btn_Brush = new CMFCRibbonButton(ID_BUTTON_BRUSH,"Кисть");
	PanelInsrument->Add(m_Btn_Brush);

	m_Btn_Lastic = new CMFCRibbonButton(ID_BUTTON_LASTIC,"Ластик");
	PanelInsrument->Add(m_Btn_Lastic);

	//*********************************************************************************************************************
	
	CMFCRibbonPanel* AddTrees = category->AddPanel("Добавить дерево");

	m_Edit_TreesHeight=new CMFCRibbonEdit(ID_EDIT_TREESHEIGHT,100, _T("Высота   :\nsb"), -1);
	m_Edit_TreesHeight->SetEditText("20");
	AddTrees->Add(m_Edit_TreesHeight);

	m_Edit_TreesWeight=new CMFCRibbonEdit(ID_EDIT_TREESWEIGHT,100, _T("Ширина :\nsb"), -1);
	m_Edit_TreesWeight->SetEditText("100");
	AddTrees->Add(m_Edit_TreesWeight);

	m_Btn_AddTrees = new CMFCRibbonButton(ID_BUTTON_ADDTREES,"Добавить дерево",14);
	AddTrees->Add(m_Btn_AddTrees);

	//*********************************************************************************************************************

	CMFCRibbonPanel* save = category->AddPanel("Сохранить");
	m_Btn_Save = new CMFCRibbonButton(ID_BUTTON_SAVE,"Сохранить",IDB_RIBBON_LANDsLARGE,3);
	save->Add(m_Btn_Save);

	//*********************************************************************************************************************

	CMFCRibbonPanel* load = category->AddPanel("Загрузить с файла");
	m_Btn_LoadLand = new CMFCRibbonButton(ID_BUTTON_LOADLAND,"Загрузить с файла",IDB_WRITELARGE,1);
	load->Add(m_Btn_LoadLand);
}

void CMainFrame::CreatePageTexture()		//вкладка текстуры
{
	CMFCRibbonCategory* category = Ribbon.AddCategory("Текстуры",IDB_RIBBON_LANDsSMALL,IDB_FILELARGE);
	CMFCRibbonPanel* size = category->AddPanel("Размеры");
	m_Btn_Texture=new CMFCRibbonCheckBox(ID_BUTTON_TEXTURE,"Покрывать текстурами");
	size->Add(m_Btn_Texture);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	m_Edit_TextureWight=new CMFCRibbonEdit(ID_EDIT_TEXTUREWIGHT,100, _T("Ширина :\nsb"), -1);
	m_Edit_TextureWight->SetEditText("500");
	size->Add(m_Edit_TextureWight);

	m_Edit_TextureHeight=new CMFCRibbonEdit(ID_EDIT_TEXTUREHEIGHT,100, _T("Высота   :\nsb"), -1);
	m_Edit_TextureHeight->SetEditText("500");
	size->Add(m_Edit_TextureHeight);

	m_Btn_ChangeTextureSize = new CMFCRibbonButton(ID_BUTTON_CHANGETEXTURESIZE,"Изменить размер",IDB_WRITELARGE,4);
	size->Add(m_Btn_ChangeTextureSize);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* texture = category->AddPanel("Текстуры");
	m_Btn_RTexture = new CMFCRibbonButton(ID_BUTTON_RTEXTURE,"R-текстура",11);
	texture->Add(m_Btn_RTexture);

	m_Btn_GTexture = new CMFCRibbonButton(ID_BUTTON_GTEXTURE,"G-текстура",11);
	texture->Add(m_Btn_GTexture);

	m_Btn_BTexture = new CMFCRibbonButton(ID_BUTTON_BTEXTURE,"B-текстура",11);
	texture->Add(m_Btn_BTexture);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* panelInstruments = category->AddPanel("Панель инструментов");
	m_Btn_TArrow = new CMFCRibbonButton(ID_BUTTON_TARROW,"Курсор",7);
	panelInstruments->Add(m_Btn_TArrow);

	m_Btn_TPencil = new CMFCRibbonButton(ID_BUTTON_TPENCIL,"Карандаш",13);
	panelInstruments->Add(m_Btn_TPencil);

	m_Btn_TDeleteAll = new CMFCRibbonButton(ID_BUTTON_TDELETEALL,"Очистить поле",12);
	panelInstruments->Add(m_Btn_TDeleteAll);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* LoadfromFile = category->AddPanel("Карта весов");
	m_Btn_LoadTextureFromFile = new CMFCRibbonButton(ID_BUTTON_LOADTEXTUREFROMFILE,"Загрузить с файла",IDB_WRITELARGE,1);
	LoadfromFile->Add(m_Btn_LoadTextureFromFile);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* Tsave = category->AddPanel("Сохранить");
	m_Btn_TSave = new CMFCRibbonButton(ID_BUTTON_TSAVE,"Сохранить",IDB_WRITELARGE,3);
	Tsave->Add(m_Btn_TSave);

	
}


void CMainFrame::CreatePageLoadProject()		 // вкладка Загрузить
{
	CMFCRibbonCategory* category = Ribbon.AddCategory("Запуск",IDB_RIBBON_LANDsSMALL,/*IDB_RIBBON_LANDsLARGE*/IDB_FILELARGE);
	CMFCRibbonPanel* map = category->AddPanel("Z-масштабирование");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Edit_ZMin=new CMFCRibbonEdit(ID_EDIT_ZMIN,100, _T("Z-min :\nsb"), -1);
	m_Edit_ZMin->SetEditText("0");
	map->Add(m_Edit_ZMin);

	m_Edit_ZMax=new CMFCRibbonEdit(ID_EDIT_ZMAX,100, _T("Z-max :\nsb"), -1);
	m_Edit_ZMax->SetEditText("255");
	map->Add(m_Edit_ZMax);

	m_Edit_StepSize=new CMFCRibbonEdit(ID_EDIT_STEPSIZE,100, _T("Шаг   :\nsb"), -1);
	m_Edit_StepSize->SetEditText("16");
	map->Add(m_Edit_StepSize);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* max = category->AddPanel("Растяжение");
	m_Edit_X=new CMFCRibbonEdit(ID_EDIT_X,50, _T("X :\nsb"), -1);
	m_Edit_X->SetEditText("1");
	max->Add(m_Edit_X);

	m_Edit_Y=new CMFCRibbonEdit(ID_EDIT_Y,50, _T("Y :\nsb"), -1);
	m_Edit_Y->SetEditText("1");
	max->Add(m_Edit_Y);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CMFCRibbonPanel* load = category->AddPanel("Загрузка");
	m_Btn_LoadProject = new CMFCRibbonButton(ID_BUTTON_LOAD,"Запустить",IDB_WRITELARGE);
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
void CMainFrame::OnBtnLoadMapClick()						//вызов диалогового окна для карты высот
{
	  CString wStr,hStr,fileStr;
	  CDlgCreateProject *DlgCreateProject=new CDlgCreateProject(&wStr,&hStr,&fileStr);
	  if (DlgCreateProject->DoModal()==IDOK)									
	  {
		  theApp.DrawMapFrame->LoadMapFromFile(fileStr,atoi(wStr),atoi(hStr));	//вызывает функцию загрузки с файла карты высот и вывод её на экран
		  m_Edit_LandWight->SetEditText(wStr);								    //передает параметры ширины вводимое в поле
	      m_Edit_LandHeight->SetEditText(hStr);									//передает параметры высоты вводимое в поле
	  }
	 

}

void CMainFrame::OnBtnChangeSize()								//изменение параметров контексного окна в "Карте высот"
{
theApp.DrawMapFrame->ResizeMap(atoi(m_Edit_LandWight->GetEditText()),atoi(m_Edit_LandHeight->GetEditText()));//перводим в целочисленные значения ширину и высоту контексного окна

}



void CMainFrame::OnBtnLoadProject()		// функция выполнения действия при нажатии на копку "Запуск"
{
//Отправляем все данные о ландшафте в объект Landshaft
	CVector2 z,scale;
	z.x = atof(m_Edit_ZMin->GetEditText());					// масштабирование изображения  Min
	z.y = atof(m_Edit_ZMax->GetEditText());					//масштабирование изображения Max
	scale.x=atof(m_Edit_X->GetEditText());					//растяжение по х
	scale.y=atof(m_Edit_Y->GetEditText());					//растяжение по у
	theApp.GLContainer = new CGLContainer();
	theApp.GLContainer->Create(z,scale,RImage,GImage, BImage);
	
//Создаем GL-окно
	/*
	CString Tex1File,Tex2File,Tex3File,TexVec;
	
Tex1File = "Shaders\\textureL0.bmp";
Tex2File = "Shaders\\textureL1.bmp";
Tex3File = "Shaders\\textureL2.bmp";
TexVec   = "Shaders\\texVec.bmp";
	*/
	CGLFrame *GLFrame=new CGLFrame; 
	GLFrame->Create(NULL,"Terrain3D",WS_MAXIMIZE|WS_POPUPWINDOW,CRect(0,0,100,100),NULL);	//создаем окно проекта на весь экран
	GLFrame->ShowWindow(SW_HIDE);															//скрыть окно
	CRect t;//для указания координат используется объект CRect, который имеет четыре переменные: l – левая координата, t - верхняя координата, r – правая координата, b – нижняя координата.
	GLFrame->GetWindowRect(t);
	GLFrame->MoveWindow(-3,-3,t.Width()+5,t.Height()+5,0);									//задаем координаты окну
	///

	for (int i=0; i<theApp.DrawMapFrame->picture->TreesProp.size(); i++)
		theApp.GLContainer->AddTree(theApp.DrawMapFrame->picture->TreesProp[i]);						//добавление деревьев на ландшафт
	
	GLFrame->ShowWindow(SW_SHOW);
	this->EnableWindow(0);																	//основное окно неактивно
}

void CMainFrame::OnBtnPencil ()				//карандаш в карте высот
{
CDialogPencil pencil;
	pencil.DoModal();
/*ValueOfButton=1;                            //если нажата кнопка 1
OnMouseMove (0,0);						//вызываем функцию */
}

void CMainFrame::OnBtnArrow()//курсор в карте высот
{
ValueOfButton=0;
}

void CMainFrame::OnBtnAddTrees()		//добавляем на карту высот деревья
{
	ValueOfButton=3;
	OnLButtonDown(0,0);					//функция рисования крестиков (деревьев)
}



void CMainFrame::OnBtnDeleteAll()		// функция очистки поля в карте высот
{
	ValueOfButton=4;
	OnLButtonUp(0,0);
//MessageBox("Вы нажали на кнопку очистить всё!");
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

void CMainFrame::OnBtnSave()			//функуия сохранения данных карты высот
{
//MessageBox("Вы нажали на кнопку сохранить!");
//	theApp.GLContainer.Landshaft.LoadMapFromDC(theApp.DrawMapFrame->GetMemoryDC(),theApp.DrawMapFrame->GetW(),theApp.DrawMapFrame->GetH());
}


void CMainFrame::OnBtnRTexture()			 // данные R-текстуры
{
 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"RТекстура(.bmp)|*.bmp||");
 File.DoModal();
 RImage->Destroy();
 RImage = new CImage;
 RImage->Load(File.GetPathName());

}

void CMainFrame::OnBtnGTexture()			// данные G-текстуры
{
 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"GТекстура(.bmp)|*.bmp||");
 File.DoModal();
 GImage->Destroy();
 GImage = new CImage;
 GImage->Load(File.GetPathName());

}

void CMainFrame::OnBtnBTexture()			//данные B-текстуры
{
 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"BТекстура(.bmp)|*.bmp||");
 File.DoModal();
 BImage->Destroy();
 BImage = new CImage;
 BImage->Load(File.GetPathName());

}
void CMainFrame::OnBtnChangeTextureSize()
{
MessageBox("Вы нажали на кнопку измениьт размер!");
//theApp.DrawMapFrame->ResizeMap(atoi(m_Edit_LandWight->GetEditText()),atoi(m_Edit_LandHeight->GetEditText()));
}

void CMainFrame::OnBtnTPencil()				// функция карандаш в Текстуре
{
MessageBox("Вы нажали на кнопку карандаш!");
}

void CMainFrame::OnBtnTArrow()				//функция курсор в Текстуре
{
MessageBox("Вы нажали на кнопку курсор!");
}

void CMainFrame::OnBtnTDeleteAll()			// функция очистки поля в Текстуре
{
MessageBox("Вы нажали на кнопку очистить всё!");
}

void CMainFrame::OnBtnLoadTextureFromFile()		// загрузить с файла, диалоговое окно
{
	 CFileDialog File(true,"bmp",NULL,OFN_NOLONGNAMES   ,"Битовые рисунки|*.bmp|Интернет картинки|*.jpg||");
	  if (File.DoModal()==IDOK)
//CString fileStr = "C:\\Users\\Roma\\Desktop\\Новая папка (2)\\Курсовая Last\\Terrain\\Terrain\\Shaders\\texVec.bmp";	 
{
	theApp.DrawTextureFrame->LoadTextureFromFile(File.GetPathName()); //получаем путь к файлу
		  CString strW,strH;
		  strW.Format ("%d", theApp.DrawTextureFrame->GetW());
		  strH.Format ("%d", theApp.DrawTextureFrame->GetH());
		  m_Edit_TextureWight->SetEditText(strW);                           //передаем  в поле ширины окна текстуры ширину
		  m_Edit_TextureHeight->SetEditText(strH);						    //передаем  в поле высоты окна текстуры высоту
	  }

}

void CMainFrame::OnBtnTSave()												//сохранить данные Текстуры
{
MessageBox("Вы нажали на кнопку Сохранить!");
}

/*void CMainFrame::OnBtnClickTick(CCmdUI* pCmdUI)
{

}
*/

void CMainFrame::OnPaint()				//зарисовка главного окна (вне контекста)
{
	CPaintDC dc(this); 
	CRect r;
	CBrush brush;						//заливка
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
		theApp.DrawMapFrame->Resize(r.Width(),r.Height());  //изменение размера
	}
	if(theApp.DrawTextureFrame!=NULL)
	{
		theApp.DrawTextureFrame->Resize(r.Width(),r.Height());
	}

}
