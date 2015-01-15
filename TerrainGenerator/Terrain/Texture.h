#pragma once
#include "afx.h"
#include "GlLib.h"


class CTexture
{
	AUX_RGBImageRec *texture;                                             // �������� ��������
	 CString FileName;
	 GLuint	texPtr;
	 GLvoid LoadGLTextures();
	 bool createdFlag;          //���� �� ��������� ��������
void    Create(AUX_RGBImageRec *texture); //������� ������ �� ��� ���������� texture 
	
public:
	void    InitTexture(CString FileName);
	void    InitTexture(CTextureProp propVec);
	void    InitTexture(CImage *image);
	GLuint  GetTexPt();
	bool    IsCreated();
	CString GetTexFileName();
	int     PictWigth();
	int     PictHeight();
	void    Free();
	CTexture(void);
	~CTexture(void);
};
