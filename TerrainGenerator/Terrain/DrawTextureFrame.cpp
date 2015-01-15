#include "StdAfx.h"
#include "DrawTextureFrame.h"
#include <atlimage.h>

BEGIN_MESSAGE_MAP(CDrawTextureFrame, CDrawFrame)

	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

CDrawTextureFrame::CDrawTextureFrame(void)
{

}

CDrawTextureFrame::~CDrawTextureFrame(void)
{
}
/*
void GrayBuffer( const char * pBuffer, int pLen)
{
    int res = 0;
    const double rMask = 0.212671;
    const double gMask = 0.715160;
    const double bMask = 0.002169;
    __asm
    {
        mov eax, pBuffer
        mov ecx, pLen
        sub ecx, 4
        fninit
        xor ebx, ebx
_lp:
        mov bl, byte ptr [eax][ecx]
        mov res, ebx
        fild [res]
        fmul [rMask]
        mov bl, byte ptr [eax][ecx+1]
        mov res, ebx
        fild [res]
        fmul [gMask]
        fadd
        mov bl, byte ptr [eax][ecx+2]
        mov res, ebx
        fild [res]
        fmul [bMask]
        fadd
        fistp [res]
        mov ebx, res
        mov byte ptr [eax][ecx+2], bl
        mov byte ptr [eax][ecx+1], bl
        mov byte ptr [eax][ecx], bl
        sub ecx, 4
        or    ecx, ecx
        jnz _lp
    }
}
HBITMAP GrayBitmap(HWND hWnd, HBITMAP hSource)
{
    BITMAP hBmp;
    if(GetObject(hSource, sizeof(BITMAP), &hBmp))
    {
        LPBITMAPINFO bBmi;
        if(bBmi = (LPBITMAPINFO)GlobalAlloc(GPTR, sizeof(BITMAPINFOHEADER) + ( hBmp.bmWidth * hBmp.bmHeight * sizeof(RGBQUAD))))
        {
            HBITMAP hDest;
            bBmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            HDC dc = GetDC(NULL);
            GetDIBits( dc, hSource, 0, hBmp.bmHeight, NULL, bBmi, DIB_RGB_COLORS); // получаем инфу о битмапе в bBmi
            int bufSize = bBmi->bmiHeader.biSizeImage;
            int result = 0;
            char * buffer;
            if(buffer = (char *)GlobalAlloc(GPTR, bufSize))
            {
                if(GetDIBits(dc, hSource, 0, hBmp.bmHeight, (LPVOID)buffer, bBmi, DIB_RGB_COLORS)) // а вот здесь получаем в buffer наши пиксели :)
                {
                    GrayBuffer(buffer, bufSize);
                    hDest = CreateCompatibleBitmap(dc, hBmp.bmWidth, hBmp.bmHeight );
                    result = SetDIBits(dc, hDest, 0, hBmp.bmHeight, (LPVOID)buffer, bBmi, DIB_RGB_COLORS);
                }
                GlobalFree(buffer);
            }
            GlobalFree(bBmi);
            if(result) return hDest;
        }
    }
    return NULL;
}
*/
char* GetBufFromDC(CDC *pDC, int W, int H)
{

	int bRes;
	HBITMAP hbmScreen;
	char *buffer=new char[3*W*H*3];
	CDC * dc=new CDC();
	
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = W;
	bi.bmiHeader.biHeight = H;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 24;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = 3*W*H;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;
	
	hbmScreen =(HBITMAP) pDC->GetCurrentBitmap()->m_hObject;
	dc->CreateCompatibleDC(NULL);
	dc->SelectObject(hbmScreen);
	bRes = GetDIBits( dc->m_hDC, hbmScreen, 0, H, (LPVOID)buffer, &bi, DIB_RGB_COLORS);
	return buffer;
}
void CDrawTextureFrame::LoadTextureFromFile(CString FileName)//загружение картинки текстуры с файла, и вывод её на экран
{
	CImage *Img=new CImage;
	Img->Load(FileName);//загружаем с файла
	ResizeMap(Img->GetWidth(),Img->GetHeight());
	picture->Resize(Img->GetWidth(),Img->GetHeight());
	
	Img->BitBlt(picture->dcMemory->m_hDC,0,0,SRCCOPY);
	//picture->dcMemory->Rectangle(0,0,100,100);
	picture->RedrawWindow();
	//Img->BitBlt(picture->GetDC()->m_hDC,0,0,SRCCOPY);
	
	/*char* buffer = GetBufFromDC(&picture->dcMemory,Img.GetWidth(),Img.GetHeight());

	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = Img.GetWidth();
	bi.bmiHeader.biHeight = Img.GetHeight();
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 24;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = 3*Img.GetWidth()*Img.GetHeight();
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;
	
	SetDIBits( picture->dcMemory.m_hDC,(HBITMAP)picture->dcMemory.GetCurrentBitmap()->m_hObject,
		0,Img.GetHeight(),buffer,&bi,DIB_RGB_COLORS);
*/
//*******************

}

void CDrawTextureFrame::OnPaint()//создание контекста, окна в котором будет отображение текстуры
{
	CPaintDC dc(this); 
//	dc.BitBlt(0,0,W,H,&dcMemory,0,0,SRCCOPY);//копируем с контекста dcMemory в CPaintDC dc(вывели в окно)
	CDrawFrame::OnPaint();
}

int CDrawTextureFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDrawFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	picture	 = new CPicture(2);
	picture->Create(NULL,"Pict",WS_CHILD,CRect(10,10,100,100),this);
	picture->ShowWindow(SW_SHOW);
	picture->Resize(500,500);

	return 0;
}

void CDrawTextureFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDrawFrame::OnShowWindow(bShow, nStatus);

		/*CBrush b;
		
	b.CreateSolidBrush(RGB(0,255,0));
picture->dcMemory.SelectObject(&b);
	picture->dcMemory.Rectangle(-10,-10,H+5,W+5);*/
}
