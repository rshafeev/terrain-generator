// GLFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Terrain.h"
#include "GLFrame.h"


// CGLFrame

IMPLEMENT_DYNCREATE(CGLFrame, CFrameWnd)

CGLFrame::CGLFrame()                       //изменение параметров освещение
{
	PosLight[0]=-32.0;
	PosLight[1]=177.0;                     //изменение по высоте (у)
	PosLight[2]=-10.0;
	PosLight[3]=1.0;

}

CGLFrame::~CGLFrame()
{
	pDC=NULL;
	hDC=NULL;
	hRC=NULL;

}


BEGIN_MESSAGE_MAP(CGLFrame, CFrameWnd)
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGLFrame message handlers
bool CGLFrame::Init()
{
	InitGL();
	theApp.GLContainer->Init();
	return true;
}
bool CGLFrame::InitGL()									// Начальные установки касаемо OpenGL, при нажатии "Запустить" (главного проекта)
{	
	CRect rect;
	int pixelformat;

	pDC = GetDC();
	hDC = pDC->GetSafeHdc();
  static  PIXELFORMATDESCRIPTOR pfd=                            // pfd сообщает Windows каким будет вывод на экран каждого пикселя
  {
    sizeof(PIXELFORMATDESCRIPTOR),                              // Размер дескриптора данного формата пикселей
    1,                                                          // Номер версии
    PFD_DRAW_TO_WINDOW |                                        // Формат для Окна
    PFD_SUPPORT_OPENGL |                                        // Формат для OpenGL
    PFD_DOUBLEBUFFER,                                           // Формат для двойного буфера
    PFD_TYPE_RGBA,                                              // Требуется RGBA формат
    32,                                                         // Выбирается бит глубины цвета
    0, 0, 0, 0, 0, 0,                                           // Игнорирование цветовых битов
    0,                                                          // Нет буфера прозрачности
    0,                                                          // Сдвиговый бит игнорируется
    0,                                                          // Нет буфера накопления
    0, 0, 0, 0,                                                 // Биты накопления игнорируются
    32,                                                         // 32 битный Z-буфер (буфер глубины)
    0,                                                          // Нет буфера трафарета
    0,                                                          // Нет вспомогательных буферов
    PFD_MAIN_PLANE,                                             // Главный слой рисования
    0,                                                          // Зарезервировано
    0, 0, 0                                                     // Маски слоя игнорируются
  };

	if ((pixelformat = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}
	if (SetPixelFormat(pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat failed");
		return FALSE;
	}
 hRC = wglCreateContext(hDC);
 wglMakeCurrent(hDC, hRC);

 glShadeModel( GL_SMOOTH );                                   // Разрешить плавное цветовое сглаживание
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                        // Очистка экрана в черный цвет
 glClearDepth( 1.0f );                                        // Разрешить очистку буфера глубины
 glEnable( GL_DEPTH_TEST );                                   // Разрешить тест глубины
 glDepthFunc( GL_LEQUAL );									  // Тип теста глубины
 glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );		  // Улучшение в вычислении перспективы (разрешить необязательный контроль над определенными аспектами поведения при визуализации)

 
  GetWindowRect(rect);
 glViewport( 0, 0, rect.Width(), rect.Height());			  // Сброс текущей области вывода 
//освещение

	 GLfloat LightAmbient[] = {0.0, 0.0, 0.0};
	 GLfloat LightDiff[] = {1.0, 1.0, 1.0, 1.0};
	 GLfloat MaterialAmbient[] = {0.9, 0.9, 0.9, 0.0};
     GLfloat MaterialDiffuse[] = {0.8, 0.8, 0.8, 0.0 };//
     GLfloat MaterialSpecular[] = {0.9, 0.9, 0.9, 1.0 };//
     GLfloat MaterialShininess[] = {110.0};
     GLfloat MaterialEmis[] = {0.21, 0.01, 0.01, 0.0};
////////////////////////////////////////
	glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
 	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiff);

//перспектива
 glMatrixMode( GL_PROJECTION );                                       // Выбор матрицы проекций
 glLoadIdentity();                                                    // Сброс матрицы проекции
 gluPerspective( 45.0f, (GLfloat)rect.Width()/(GLfloat)rect.Height(), 0.1f,7500 ); // Вычисление соотношения геометрических размеров для окна
 glMatrixMode( GL_MODELVIEW );                                        // Выбор матрицы вида модели
 glLoadIdentity();                                                  // Сброс матрицы вида модели
 glEnable(GL_NORMALIZE);										      //активизирует функцию рисования

 //камера 
 Camera.Angle.x=30;
 Camera.Angle.y=40.0;
 Camera.Angle.z=0.0;
 Camera.Pos.x=-250;
 Camera.Pos.y=-270;
 Camera.Pos.z=-250.0;
 Camera.walkbiasangle = 0.0;
 glEnable(GL_TEXTURE_2D);
 


 return true;												        // Инициализация прошла успешно
}
void CGLFrame::RenderScene()										//перерисовка окна
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				//окно очищается текущим цветом очистки,установка буфера накопления
  glClearColor(.25f, .25f, .75f, .25f);								//устанавливается состояние визуализации (R,G,B,alfa)
  glLoadIdentity();                                                 // Сброс просмотра
  
  glRotatef(Camera.Angle.y, 1.0f, 0.0, 0.0);					    //выполняет поворот
  glRotatef(Camera.Angle.x, 0.0, 1.0f, 0.0);
  glRotatef(Camera.Angle.z, 0.0, 0.0, 1.0f);
  glTranslatef(Camera.Pos.x,Camera.Pos.y,Camera.Pos.z);
 
  glLightfv(GL_LIGHT0, GL_POSITION, PosLight);						//положение источника света LIGHT0
  theApp.GLContainer->Render();

  SwapBuffers(wglGetCurrentDC());									//записыавем из hRC в pDC
  
  
}
void CGLFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)		//нажатие клавиш передвижения (стрелок)
{ 
	const double PI = 3.1415;
const double Speed=50;
 float X=Camera.Pos.x,Z=Camera.Pos.z;
if (nChar==27)
{
	ShowCursor(true);
	DestroyWindow();
	return;
}
if(nChar==38)//стрелка вперед
  {
	  X -= Speed*sin((Camera.Angle.x)/180.0*PI);
	  Z += Speed*cos((Camera.Angle.x)/180.0*PI);
    }
if(nChar==40)//стрелка назад
  {
     X += (float)sin((Camera.Angle.x)* PI/180.0) * Speed;
     Z -= (float)cos((Camera.Angle.x)* PI/180.0) * Speed;
  }

if(nChar==39)//стрелка влево
  {
     X -= Speed*sin((Camera.Angle.x+90)/180.0*PI);
     Z += Speed*cos((Camera.Angle.x+90)/180.0*PI);
    }
  else
if(nChar==37)//стрелка вправо
  {
     X += Speed*sin((Camera.Angle.x+90)/180.0*PI);
     Z -= Speed*cos((Camera.Angle.x+90)/180.0*PI);
  }
if(nChar==36)
{
	Camera.Pos.y-=Speed/5.0;
}
if(nChar==35)
{
	Camera.Pos.y+=Speed/5.0;
}
	 Camera.Pos.x = X;
     Camera.Pos.z = Z;
RenderScene();
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	
}

int CGLFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)//при создании окна пректа
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	pDC = GetDC();
	Init();
	RenderScene();
	ShowCursor(false);
	return 0;
}

void CGLFrame::OnPaint()		//вызывавается при создании проекта
{
	CPaintDC dc(this); 
	CRect t;					//для указания координат используется объект CRect, который имеет четыре переменные: l – левая координата, t - верхняя координата, r – правая координата, b – нижняя координата.
	GetWindowRect(t);
    dc.BitBlt(0,0,t.Width(), t.Height(),pDC,0,0,SRCCOPY);
	RenderScene();
}

void CGLFrame::OnSize(UINT nType, int cx, int cy)		//размеры окна проекта
{

	CRect t;   //для указания координат используется объект CRect, который имеет четыре переменные: l – левая координата, t - верхняя координата, r – правая координата, b – нижняя координата.
	GetWindowRect(t);
	glViewport( 0, 0, t.Width(), t.Height());            //устанавливает поле просмотра с размерами окна (задает участок окна, где OpenGl может выполнять рисование)

 	CFrameWnd::OnSize(nType, cx, cy); 
}
static long xCurPosOld=0, yCurPosOld=0;
void CGLFrame::OnMouseMove(UINT nFlags, CPoint point)	//движение мышкой
{
	CRect WndRect;
	GetClientRect(WndRect);
	
	if(xCurPosOld!=0&&yCurPosOld!=0)
	{
	  Camera.Angle.y -= (yCurPosOld-point.y)*0.05f;
	  Camera.Angle.x -= (xCurPosOld-point.x)*0.05f;
	}
	CString text;
	text.Format("alfax = %f; alfay=%f; ",Camera.Angle.x,Camera.Angle.y); 
	SetWindowText(text);
  /*  if(Camera.Angle.y<-30)   Camera.Angle.y=-30;
	if(Camera.Angle.y> 50.0) Camera.Angle.y= 50.0;*/
	/*if(Camera.Angle.x< 0.0)   Camera.Angle.x = 359.0;
	if(Camera.Angle.x> 359.0) Camera.Angle.x = 0.0;
*/
	if(point.x>=WndRect.Width()-6)
	{
		point.x = 30;
		SetCursorPos(point.x,point.y);
	}
	if (point.x<=25)
	{
		point.x=WndRect.Width()-10;
		SetCursorPos(point.x,point.y);
	}
	if(point.y>=WndRect.Height()-6)
	{
		point.y = 30;
		SetCursorPos(point.x,point.y);
	}
	if (point.y<=25)
	{
		point.y=WndRect.Height()-10;
		SetCursorPos(point.x,point.y);
	}
	
	/*if(point.x==0)
	{	
		Point.x = OpenGlForm->screenW;
		SetCursorPos(Point.x,Point.y);
	}
	if(point.y==0)
	{	
		Point.y = OpenGlForm->screenH;
		SetCursorPos(Point.x,Point.y);
	}*/

	 xCurPosOld = point.x;
	 yCurPosOld = point.y;	

	RenderScene();

	CFrameWnd::OnMouseMove(nFlags, point);
}

void CGLFrame::OnDestroy()  // при закрытие GLFrame главное окно становится активным
{
	delete theApp.GLContainer;
	DestroyGL();

	((CMainFrame*)theApp.m_pMainWnd)->EnableWindow(1);
	((CMainFrame*)theApp.m_pMainWnd)->SetFocus();
	CFrameWnd::OnDestroy();
	
}
