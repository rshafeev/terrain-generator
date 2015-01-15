#include "StdAfx.h"
#include "MainFrm.h"
#include "Terrain.h"
#include "GLContainer.h"
#include "DrawMapFrame.h"
#include "Tree.h"
#include "Landshaft.h"




BEGIN_MESSAGE_MAP(CDrawMapFrame, CDrawFrame)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_CREATE()
END_MESSAGE_MAP()

CDrawMapFrame::CDrawMapFrame(void)
{
	activeBtn=false;
}

CDrawMapFrame::~CDrawMapFrame(void)
{
}
bool CDrawMapFrame::LoadMapFromFile(CString FileName,int w,int h)//загрузить карту с файла,рисование в окне,вывод карты высот на экран
{
	BYTE *fmas;
 	BYTE * mas;
	CStdioFile LandFile;
	int n;

	if(LandFile.Open(FileName,CFile::modeRead)==false)return false;
	n=w*h;
	fmas=new BYTE[n];
	
	mas=new BYTE[3*n];

	LandFile.Read(fmas,n);



	/*for(int i=0;i<n;i++)
	{
		mas[3*i+0] = fmas[i];
		mas[3*i+1] = fmas[i];
		mas[3*i+2] = fmas[i];

	}
*/
for(int i=0;i<w;i++)
for(int j=0;j<h;j++)
{
	int color = fmas[(w-1-i)*h+j];
	//Mass[i][j] =LandProperties.ZInterval.x+ color*(LandProperties.ZInterval.y-LandProperties.ZInterval.x)/255.0;//
	mas[3*h*(i)+3*j+0] = color;
	mas[3*h*(i)+3*j+1] = color;
	mas[3*h*(i)+3*j+2] = color;
}

	BITMAPINFO bi;

	int bRes;
	HBITMAP hbmScreen;

	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = w;
	bi.bmiHeader.biHeight = h;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 24;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = 3*w*h;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

		ResizeMap(w,h);
		picture->Resize(w,h);
		SetDIBits( picture->dcMemory->m_hDC,(HBITMAP)picture->dcMemory->GetCurrentBitmap()->m_hObject,
			0,h,mas,&bi,DIB_RGB_COLORS);
		//picture->dcMemory->Rectangle(0,0,100,100);
//picture->RedrawWindow();

	/* for (int i=0;i<h;i++)
		for (int j=0;j<w; j++)
		{
			int grey=fmas[i*w+j];

			picture->dcMemory.SetPixel(j,i,RGB(grey,grey,grey));//выводим поточечно на экран карту высот
		}
*/
		
		delete [] fmas;
		delete [] mas;
	LandFile.Close();


RedrawWindow();
  return true;
}


void CDrawMapFrame::OnPaint()//вызываетс€ при создании окна
{
	CPaintDC dc(this); 
	//dc.BitBlt(0,0,W,H,&picture->dcMemory,0,0,SRCCOPY);//копируем с контекста dcMemory в CPaintDC dc(вывели в окно)
	picture->RedrawWindow();	
	CDrawFrame::OnPaint();
	
}



CPoint oldP = CPoint(0,0);
void CDrawMapFrame::OnLButtonDown(UINT nFlags, CPoint point)		//рисует крестики, при выборе кнопки "ƒобавить ƒерево"
{
	int d = 8;
	activeBtn=true;
	if (((CMainFrame*)theApp.m_pMainWnd)->ValueOfButton==3)
	{
		CClientDC paint(this);
				CPen pen;
				pen.CreatePen(PS_SOLID,2,RGB(255,5,5));
		paint.SelectObject(&pen);
	    paint.MoveTo(point.x-d, point.y);//горизонтальна€
		paint.LineTo(point.x+d, point.y);
		paint.MoveTo(point.x, point.y-d);//вертикальна€
		paint.LineTo(point.x, point.y+d);
		TTreeProperties prop;

		prop.x = point.x;
		prop.y = point.y;
		prop.r = atoi(((CMainFrame*)theApp.m_pMainWnd)->m_Edit_TreesHeight->GetEditText());
//		TreesProp.push_back(prop);
	}
oldP=point;

	CDrawFrame::OnLButtonDown(nFlags, point);

}

void CDrawMapFrame::OnMouseMove(UINT nFlags, CPoint point)
{



/*pen.CreatePen(PS_SOLID,5,RGB(255,5,5));
		paint.SelectObject(&pen);
paint.MoveTo(point.x+10, point.y+10);//горизонтальна€
		paint.LineTo(point.x+1, point.y+1);
*/

			//	brush.CreateSolidBrush(RGB(255,5,5));
		//paint.SelectObject(&brush);
		/*paint.MoveTo(point.x-d, point.y);//горизонтальна€
		paint.LineTo(point.x+d, point.y);
		paint.MoveTo(point.x, point.y-d);//вертикальна€
		paint.LineTo(point.x, point.y+d);*/
		
//CBrush brush;
//brush.CreateSolidBrush(RGB(0,255,0)); 
//		
	//	dcMemory.SetPixel(point.x,point.y,RGB(5,5,5));
		//oldP = point;
//brush.CreateHatchBrush(HS_CROSS,RGB(125,0,0));
//brush.SelectObject(&brush);
//brush.CreateBrushIndirect(*125);
//paint.SetBkColor(RGB(255,0,0)); //установили €рко-красный фон дл€ кисти
	//}

	CDrawFrame::OnMouseMove(nFlags, point);
}





void CDrawMapFrame::OnLButtonUp(UINT nFlags, CPoint point)
{	
	activeBtn=false;

	CDrawFrame::OnLButtonUp(nFlags, point);
}

int CDrawMapFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDrawFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	picture	 = new CPicture(0);
	picture->Create(NULL,"Pict",WS_CHILD,CRect(10,10,100,100),this);
	picture->ShowWindow(SW_SHOW);
	picture->Resize(500,500);
	return 0;
}
