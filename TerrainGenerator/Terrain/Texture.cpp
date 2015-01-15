#include "StdAfx.h"
#include "Texture.h"
#include "memory.h"
#include "Functions.h"
CTexture::CTexture(void)
{
	createdFlag=false;
}

CTexture::~CTexture(void)
{
}
//====================================================================================================
CString CTexture::GetTexFileName()			 //получения имени файла, возвращает имя файла
{
   return FileName;
}
//====================================================================================================
void CTexture::Create(AUX_RGBImageRec *texture)
{
  if(texture!=NULL)
	  this->texture=texture;
}
//====================================================================================================
GLvoid CTexture::LoadGLTextures()
{
   texture=auxDIBImageLoadA((LPCSTR)FileName);
   glGenTextures(1,&texPtr);                                  // Создание текстуры
  texture->sizeX -= texture->sizeX%2;
  texture->sizeY -= texture->sizeY%2;
     glBindTexture(GL_TEXTURE_2D, texPtr);	
	 gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture->sizeX, texture->sizeY,
                       GL_RGB, GL_UNSIGNED_BYTE, texture->data); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	 createdFlag=true;   //если выполнилась загрузка текстуры успешно
}

//=======================================================================================================
void CTexture::InitTexture(CString FileName)
{
	this->FileName=FileName;
	if(IsFileExists(FileName)==true)			 //если путь к текстуре указан, то выполняем загрузку 
	   LoadGLTextures();
}
void CTexture::InitTexture(CImage *image)
{
	//AUX_RGBImageRec *texture = propVec.pDC->GetCurrentBitmap();
	int W,H;
	W=image->GetWidth();
	H=image->GetHeight();
	texture = new AUX_RGBImageRec;
	texture->sizeX=W;
	texture->sizeY=H;
	texture->data = GetBufFromDC(CDC::FromHandle(image->GetDC()),W,H);
//CDC* pDC = CDC::FromHandle(image.GetDC());

	
	/*for (int i=0; i<H; i++)
		for (int j=0; j<W; j++)
		{

			COLORREF color = image->GetPixel(i,j);

			texture->data[j*3+W*i*3+0]=GetRValue(color);
			texture->data[j*3+W*i*3+1]=GetGValue(color);
			texture->data[j*3+W*i*3+2]=GetBValue(color);
		}
	*/
   //texture=auxDIBImageLoadA((LPCSTR)FileName);
   glGenTextures(1,&texPtr);                                  // Создание текстуры
   texture->sizeX -= texture->sizeX%2;
   texture->sizeY -= texture->sizeY%2;
     glBindTexture(GL_TEXTURE_2D, texPtr);	
	 gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture->sizeX, texture->sizeY,
		 GL_BGR, GL_UNSIGNED_BYTE, texture->data); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	 createdFlag=true;   //если выполнилась загрузка текстуры успешно
}

void CTexture::InitTexture(CTextureProp propVec)
{
	texture = new AUX_RGBImageRec;
	texture->sizeX=propVec.H;
	texture->sizeY=propVec.W;
	texture->data = GetBufFromDC(propVec.pDC,propVec.W,propVec.H);

		int W,H;
	W=propVec.W;
	H=propVec.H;


	//********************
unsigned char *mas = new unsigned char[W*H*3];
	int f;
    for (int i = 0;i<H;i++)
    {
        f = W-1;
        for (int j = 0;j<W;j++ )
        {
           // transp_mass[i][f] = mass[j][i];
			mas[i*3+W*(f)*3+0] = texture->data[j*3+W*i*3+0];
			mas[i*3+W*(f)*3+1] = texture->data[j*3+W*i*3+1];
			mas[i*3+W*(f)*3+2] = texture->data[j*3+W*i*3+2];
			f--;
        }
    }
delete [] texture->data;
	texture->data = mas;

	//*******************
	/*unsigned char *mas = new unsigned char[W*H*3];
	for (int i=0; i<H; i++)
		for (int j=0; j<W; j++)
		{
			mas[(H-1-j)*3+W*(W-1-i)*3+0] = texture->data[j*3+W*i*3+0];
			mas[(H-1-j)*3+W*(W-1-i)*3+1] = texture->data[j*3+W*i*3+1];
			mas[(H-1-j)*3+W*(W-1-i)*3+2] = texture->data[j*3+W*i*3+2];
		}
    texture->data = mas;*/
   glGenTextures(1,&texPtr);                                  // Создание текстуры
   texture->sizeX -= texture->sizeX%2;
   texture->sizeY -= texture->sizeY%2;
     glBindTexture(GL_TEXTURE_2D, texPtr);	
	 gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture->sizeX, texture->sizeY,
		 GL_RGB, GL_UNSIGNED_BYTE, texture->data); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	 createdFlag=true;   //если выполнилась загрузка текстуры успешно
}
//=======================================================================================================
GLuint CTexture::GetTexPt()
{
	return texPtr;
}
//=======================================================================================================
bool CTexture::IsCreated()
{
  return createdFlag;
}
//=======================================================================================================
int CTexture::PictWigth()   //получение ширины по х
{
	if(createdFlag==false)   return 0;
	return (int)texture->sizeX;
}
//=======================================================================================================
int CTexture::PictHeight()   //получение высоты по у
{
	if(createdFlag==false)   return 0;
	return (int)texture->sizeY;
}
//=======================================================================================================
void CTexture::Free()
{
 if(createdFlag==true)
 {
   createdFlag=false;
   FileName="";
   glDeleteTextures(1,&texPtr);
   delete [] texture->data;
   free(texture);
   texture=NULL;
 }
}
//=======================================================================================================