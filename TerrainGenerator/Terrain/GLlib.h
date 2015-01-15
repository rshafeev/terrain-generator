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
{//��������  ���������
  int StepSize;                             //���, � ������� �������� ���� �����
  int width,height;                         //������� ����� ����� 
  CVector2 ZInterval;                  //������������ � ����������� ������ �� �����
  CVector2 ScaleXY;                     // ��������������� �� X,Y(���������� ��� ������)
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

