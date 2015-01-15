#pragma once
//#include "stdafx.h"
//using namespace std;
#include <gl\glew.h>
#include <gl\gl.h>
#include <gl\glaux.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\glut.h>
#include <gl\wglext.h>
#include "CVector.h"
class CTextureProp
{
public:
CTextureProp(int W,int H,CDC *pDC)
{
	this->W = W;
	this->H = H;
	this->pDC=pDC;
}
	int W;
	int H;
	CDC *pDC;
};
struct TLandProperties
{//свойства  ландшафта
  int StepSize;                             //шаг, с которым читается файл высот
  int width,height;                         //размеры карты высот 
  CVector2 ZInterval;                  //максимальная и минимальная высота на карте
  CVector2 ScaleXY;                     // масштабирование по X,Y(растяжение или сжатие)
  int DH,DW;
  CImage *RImage,*GImage,*BImage;
  CTextureProp *TextureVecProp;
};
struct TTreeProperties
{
int x;
int y;
int r;
CVector2 ScaleXY;       
};

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glut32.lib")

#pragma comment (lib,"OpenGL32.Lib")
#pragma comment (lib,"GLu32.Lib")
#pragma comment (lib,"WinMm.Lib")
#pragma comment (lib,"GLaux.Lib")

