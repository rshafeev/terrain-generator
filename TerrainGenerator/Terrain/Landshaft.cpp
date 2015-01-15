#include "StdAfx.h"
#include "Landshaft.h"
#include "Terrain.h"
#include "Functions.h"
//#include "GLib.h"

CLandshaft::CLandshaft(void)
{
	States.InitState=false;
	States.LandState=false;
	States.TextureState=false;
}

CLandshaft::~CLandshaft(void)
{
	for(int i=0;i<LandProperties.width;i++)
	{
		delete[] Mass[i];
	}
	for(int i=0;i<LandProperties.DW;i++)
	{
		delete[] MassHeight[i];
		delete[] MassVNormal[i];
	}

	if(MassHeight!=NULL)
		delete[] MassHeight;
	if(Mass!=NULL)
		delete[] Mass;
   if(MassVNormal!=NULL)
		delete[] MassVNormal;

		MassHeight = NULL;
		Mass = NULL;
		MassVNormal = NULL;
	TexMixing[0].Free();
	TexMixing[1].Free();
	TexMixing[2].Free();
	TexMixing[3].Free();
	glDeleteLists(MemoryPt,1);
	MixingShader.DestroyProgram();

}
void CLandshaft::LoadTextures(CTextureProp propVec)
{
CString Tex1File,Tex2File,Tex3File,TexVec;
/*	
Tex1File = "Shaders\\textureL0.bmp";
Tex2File = "Shaders\\textureL1.bmp";
Tex3File = "Shaders\\textureL2.bmp";*/
//TexVec   = "Shaders\\texVec.bmp";
/*
TexMixing[0].InitTexture(Tex1File);
TexMixing[1].InitTexture(Tex2File);
TexMixing[2].InitTexture(Tex3File);*/
//TexMixing[3].InitTexture(TexVec);

	TexMixing[2].InitTexture(LandProperties.RImage);
	TexMixing[1].InitTexture(LandProperties.GImage);
	TexMixing[0].InitTexture(LandProperties.BImage);
	//
	TexMixing[3].InitTexture(propVec);
}
//=============rop============================================================================================================
bool CLandshaft::Init(TLandProperties Properties)
{
	this->LandProperties=Properties;
    MixingShader.LoadShader("Shaders\\MixingLand.vert",			//загрузили вершинный шейдер смешивания
							"Shaders\\MixingLand.frag");		//загрузили фрагментный шейдер смешивания
	LoadTextures(*Properties.TextureVecProp);											    //загрузили 4 текстуры
	glEnable(GL_NORMALIZE);										//делаем нормали нормироваными
	LoadMapFromDC(theApp.DrawMapFrame->GetMemoryDC(),theApp.DrawMapFrame->GetW(),
												theApp.DrawMapFrame->GetH());
	 

	GenVNormals();
	LoadToMemory();
	return true; 
}
//=========================================================================================================================

void CLandshaft::LoadMapFromDC(CDC *pDC,int w,int h)/////////**********
{
	//LandProperties.StepSize=16;                                       //задаем шаг рисования ландшафта
	LandProperties.StepSize=atoi(((CMainFrame*)theApp.m_pMainWnd)->m_Edit_StepSize->GetEditText());
    LandProperties.width=w;												//задаем ширину
    LandProperties.height=h;											// задаем высоту
	LandProperties.DW=LandProperties.width/LandProperties.StepSize;		//
	LandProperties.DH=LandProperties.height/LandProperties.StepSize;	//

	int i,j;
	Mass=new int *[w];
	MassVNormal = new CVector3 *[w];
	MassHeight = new int*[LandProperties.DW+1];
	for (i=0; i<LandProperties.DW; i++)
		MassHeight[i]  = new int      [LandProperties.DH+1];
	
	for (i=0; i<w; i++)
	{
		Mass[i]  = new int      [h];
		MassVNormal[i] = new CVector3 [h];
	}
COLORREF color;		

//***************
unsigned char * buf = GetBufFromDC(pDC,w,h);
for(i=0;i<w;i++)
for(j=0;j<h;j++)
{
	int color = buf[3*(i)*h+(j)*3];
	Mass[i][j] =LandProperties.ZInterval.x+ color*(LandProperties.ZInterval.y-LandProperties.ZInterval.x)/255.0;//
	MassVNormal[i][j] = CVector3(1,1,1);
}

	for ( i = 0; i < LandProperties.DW; i ++)
      for ( j = 0; j < LandProperties.DH; j ++)
		{
		  MassHeight[i][j] = Mass[i*LandProperties.StepSize][j*LandProperties.StepSize];
	  }

delete[] buf;
//***************
/*
for(i=0;i<w;i++)
for(j=0;j<h;j++)
{
	color=pDC->GetPixel(i,j);//
	Mass[i][j] =LandProperties.ZInterval.x+ GetRValue(color)*(LandProperties.ZInterval.y-LandProperties.ZInterval.x)/255.0;//
	MassVNormal[i][j] = CVector3(1,1,1);
}

	for ( i = 0; i < LandProperties.DW; i ++)
      for ( j = 0; j < LandProperties.DH; j ++)
	  {
		  MassHeight[i][j] = Mass[i*LandProperties.StepSize][j*LandProperties.StepSize];
	  }
*/
}
//=========================================================================================================================
void CLandshaft::LoadToMemory()
{
int i= 0, j = 0;                                 // Создаем пару переменных для перемещения по массиву
 const float Texcord=1.0;
 CVector3 p[4];
 
 MemoryPt=glGenLists(1);						//указатель на список
 glNewList(MemoryPt,GL_COMPILE); //




 glEnable(GL_LIGHTING);
 glEnable(GL_TEXTURE_2D);
////////////////// 

 glEnable( GL_LIGHT0 );
 glPushMatrix();											//делает растяжение только в этом блоке
 glScalef(LandProperties.ScaleXY.x,1.0,LandProperties.ScaleXY.y);
 for(i=0;i<(LandProperties.height/LandProperties.StepSize)-2;i++)
	  for(j=0;j<(LandProperties.width/LandProperties.StepSize)-2;j++)
     {     
		 p[0].x = i*LandProperties.StepSize;              
         p[0].y = MassHeight[i][j];  
         p[0].z = j*LandProperties.StepSize;  
		 
		 p[1].x = i*LandProperties.StepSize;                    
         p[1].y = MassHeight[i][j+1];  
         p[1].z = j*LandProperties.StepSize + LandProperties.StepSize;              
  	     p[2].x = i*LandProperties.StepSize + LandProperties.StepSize; 
         p[2].y = MassHeight[i+1][j+1];  
         p[2].z = j*LandProperties.StepSize + LandProperties.StepSize;
		 p[3].x = i*LandProperties.StepSize + LandProperties.StepSize; 
         p[3].y = MassHeight[i+1][j]; 
         p[3].z = j*LandProperties.StepSize;

	 // glColor3f(p[0].y/256,p[0].y/256,p[0].y/256);

	glBegin(GL_QUADS);                           //GL_TRIANGLE_FAN  Полигоны GL_LINES GL_QUADS  GL_TRIANGLE_STRIP GL_LINE_STRIP
		 glMultiTexCoord2f(GL_TEXTURE0,0,0);
		 glMultiTexCoord2f(GL_TEXTURE1,0,0);
		 glMultiTexCoord2f(GL_TEXTURE2,0,0);
		 glNormal3f(MassVNormal[i][j].x,
			        MassVNormal[i][j].y,
					MassVNormal[i][j].z);   
	     glVertex3f(p[0].x, p[0].y, p[0].z);      //рисование точки в трехмере     
                                                        
	       glMultiTexCoord2f(GL_TEXTURE0,Texcord,0.0);
		   glMultiTexCoord2f(GL_TEXTURE1,Texcord,0.0);
		   glMultiTexCoord2f(GL_TEXTURE2,Texcord,0.0);
		 glNormal3f(MassVNormal[i][j+1].x,
			        MassVNormal[i][j+1].y,
					MassVNormal[i][j+1].z);   
         glVertex3f(p[1].x, p[1].y, p[1].z);     
         
         glMultiTexCoord2f(GL_TEXTURE0,0.0,Texcord);
		 glMultiTexCoord2f(GL_TEXTURE1,0.0,Texcord);
		 glMultiTexCoord2f(GL_TEXTURE2,0.0,Texcord);
		 glNormal3f(MassVNormal[i+1][j+1].x,
			        MassVNormal[i+1][j+1].y,
					MassVNormal[i+1][j+1].z);   
         glVertex3f(p[2].x, p[2].y, p[2].z);     
       
         glMultiTexCoord2f(GL_TEXTURE0,Texcord,Texcord);
		 glMultiTexCoord2f(GL_TEXTURE1,Texcord,Texcord);
		 glMultiTexCoord2f(GL_TEXTURE2,Texcord,Texcord);
		 glNormal3f(MassVNormal[i+1][j].x,
			        MassVNormal[i+1][j].y,
					MassVNormal[i+1][j].z);   
         glVertex3f( p[3].x, p[3].y, p[3].z);     
	
	glEnd();



	}
		 glPopMatrix();                                     //восстанавливаем приобразование
glEndList(); 
}
//=========================================================================================================================



//=========================================================================================================================
CVector3 CLandshaft::GenTrianglePNormal(CVector3 p1,CVector3 p2,CVector3 p3)
{
   CVector3 NVector;
   float modul;
   NVector.x=(p2.y-p1.y)*(p3.z-p1.z)-(p2.z-p1.z)*(p3.y-p1.y);
   NVector.y=(p3.x-p1.x)*(p2.z-p1.z)-(p2.x-p1.x)*(p3.z-p1.z);
   NVector.z=(p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y);
   modul=sqrt(NVector.x*NVector.x+NVector.y*NVector.y+NVector.z*NVector.z);
   NVector.x/=modul;
   NVector.y/=modul;
   NVector.z/=modul;
   
   return NVector;
}
//=========================================================================================================================
void CLandshaft::Render()
{
	MixingShader.Use();
	 //glEnable(GL_TEXTURE_2D);
    MixingShader.SetUniformVec2("Tex1Size",TexMixing[0].PictWigth(),
		                                   TexMixing[0].PictHeight());
    MixingShader.SetUniformVec2("Tex2Size",TexMixing[1].PictWigth(),
		                                   TexMixing[1].PictHeight());
	MixingShader.SetUniformVec2("Tex3Size",TexMixing[2].PictWigth(),
		                                   TexMixing[2].PictHeight());
	MixingShader.SetUniformVec2("PictSize",TexMixing[3].PictWigth(),TexMixing[3].PictHeight());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexMixing[3].GetTexPt());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TexMixing[0].GetTexPt());

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, TexMixing[1].GetTexPt());      //создаем объект текстуры с параметрами (CONST (определяющую вид структуры), имя текстуры)
																//2-мерная текстура
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, TexMixing[2].GetTexPt());

	MixingShader.SetUniformInt("texVec",1);
	MixingShader.SetUniformInt("tex1",2);
	MixingShader.SetUniformInt("tex2",3);
	MixingShader.SetUniformInt("tex3",4);
	glCallList(MemoryPt);
	MixingShader.Close();
	

}
//====================================================================================================================
void CLandshaft::GenVNormals()
{
	int i,j;
	int STEP_SIZE=LandProperties.StepSize;
	CVector3 Normals[6];//нормали всех 6 плоскостей
	CVector3 Versh[3];// вершины плоскости
	CVector3 NormalRes;// усредненная нормаль вершины
	bool **FlagNormalMap= new bool*[LandProperties.DW+1];
	CVector3 **PloskNormals= new CVector3*[LandProperties.DW+1];
	MassVNormal= new CVector3*[LandProperties.DW+1];
	for(int i=0;i<LandProperties.DW;i++)
	{
	   FlagNormalMap[i]= new bool[LandProperties.DH+1];
	   PloskNormals[i] = new CVector3[LandProperties.DH+1];
       MassVNormal[i]  = new CVector3[LandProperties.DH+1];
	}
	for ( i = 0; i < LandProperties.DW; i ++)
      for ( j = 0; j < LandProperties.DH; j ++)
         FlagNormalMap[i][j]=false;

 	for ( i = 0; i < 6; i++)
	{
	  Normals[i].x=0;
      Normals[i].y=0;
      Normals[i].z=0;
	}
	for ( i = 1; i < LandProperties.DW-1; i ++)
      for ( j = 1; j < LandProperties.DH-1; j ++)
	  {
         if(FlagNormalMap[i][j]==false)
	     {
		     Versh[0].x=i;
			 Versh[0].y=MassHeight[i][j]; 
			 Versh[0].z=j;
			 Versh[1].x=i+STEP_SIZE;
			 Versh[1].y=MassHeight[i+1][j];
			 Versh[1].z=j;
			 Versh[2].x=i+STEP_SIZE;
			 Versh[2].y=MassHeight[i+1][j+1];
			 Versh[2].z=j+STEP_SIZE;
			 Normals[0]=GenTrianglePNormal(Versh[0],Versh[1],Versh[2]);
             PloskNormals[i][j]=Normals[0];
	         FlagNormalMap[i][j]=true;
	      }
	      else
              Normals[0]=PloskNormals[i][j];

		 if(FlagNormalMap[i][j+1]==false)
	     {
		     Versh[0].x=i;
			 Versh[0].y=MassHeight[i][j]; 
			 Versh[0].z=j;
			 Versh[1].x=i+STEP_SIZE;
			 Versh[1].y=MassHeight[i+1][j];
			 Versh[1].z=j;
			 Versh[2].x=i;
			 Versh[2].y=MassHeight[i][j-1];
			 Versh[2].z=j-STEP_SIZE;
			 Normals[1]=GenTrianglePNormal(Versh[0],Versh[1],Versh[2]);
             PloskNormals[i][j+1]=Normals[1];
	         FlagNormalMap[i][j+1]=true;
	      }
	      else
              Normals[1]=PloskNormals[i][j+1];
      	if(FlagNormalMap[i+1][j]==false)
	     {
		     Versh[0].x=i;
			 Versh[0].y=MassHeight[i][j]; 
			 Versh[0].z=j;
			 Versh[1].x=i;
			 Versh[1].y=MassHeight[i][j-1];
			 Versh[1].z=j-STEP_SIZE;
			 Versh[2].x=i-STEP_SIZE;
			 Versh[2].y=MassHeight[i-1][j-1];
			 Versh[2].z=j-STEP_SIZE;
			 Normals[2]=GenTrianglePNormal(Versh[0],Versh[1],Versh[2]);
             PloskNormals[i+1][j]=Normals[2];
	         FlagNormalMap[i+1][j]=true;
	      }
	      else
              Normals[2]=PloskNormals[i+1][j];

		 if(FlagNormalMap[i-1][j]==false)
	     {
		     Versh[0].x=i;
			 Versh[0].y=MassHeight[i][j]; 
			 Versh[0].z=j;

			 Versh[1].x=i;
			 Versh[1].y=MassHeight[i][j+1];
			 Versh[1].z=j+STEP_SIZE;

			 Versh[2].x=i-STEP_SIZE;
			 Versh[2].y=MassHeight[i-1][j];
			 Versh[2].z=j;
			 Normals[3]=GenTrianglePNormal(Versh[0],Versh[1],Versh[2]);
             PloskNormals[i-1][j]=Normals[3];
	         FlagNormalMap[i-1][j]=true;
	      }
	      else
              Normals[3]=PloskNormals[i-1][j];

		if(FlagNormalMap[i][j-1]==false)
	     {
		     Versh[0].x=i;
			 Versh[0].y=MassHeight[i][j]; 
			 Versh[0].z=j;

			 Versh[1].x=i-STEP_SIZE;
			 Versh[1].y=MassHeight[i-1][j];
			 Versh[1].z=j;

			 Versh[2].x=i-STEP_SIZE;
			 Versh[2].y=MassHeight[i-1][j-1];
			 Versh[2].z=j-STEP_SIZE;
			 Normals[4]=GenTrianglePNormal(Versh[0],Versh[1],Versh[2]);
             PloskNormals[i][j-1]=Normals[4];
	         FlagNormalMap[i][j-1]=true;
	      }
	      else
              Normals[4]=PloskNormals[i][j-1];

			if(FlagNormalMap[i-1][j-1]==false)
	     {
		     Versh[0].x=i;
			 Versh[0].y=MassHeight[i][j]; 
			 Versh[0].z=j;

			 Versh[1].x=i;
			 Versh[1].y=MassHeight[i][j+1];
			 Versh[1].z=j+STEP_SIZE;

			 Versh[2].x=i+STEP_SIZE;
			 Versh[2].y=MassHeight[i+1][j+1];
			 Versh[2].z=j+STEP_SIZE;
			 Normals[5]=GenTrianglePNormal(Versh[0],Versh[1],Versh[2]);
             PloskNormals[i-1][j-1]=Normals[5];
	         FlagNormalMap[i-1][j-1]=true;
	      }
	      else
              Normals[5]=PloskNormals[i-1][j-1];
	
	    NormalRes.x=(Normals[0].x+Normals[1].x+Normals[2].x+Normals[3].x+Normals[4].x+Normals[5].x);
        NormalRes.y=(Normals[0].y+Normals[1].y+Normals[2].y+Normals[3].y+Normals[4].y+Normals[5].y);
        NormalRes.z=(Normals[0].z+Normals[1].z+Normals[2].z+Normals[3].z+Normals[4].z+Normals[5].z);
		float modul;
        modul=sqrt(NormalRes.x*NormalRes.x+NormalRes.y*NormalRes.y+NormalRes.z*NormalRes.z);
        NormalRes.x/=modul;
        NormalRes.y/=modul;
        NormalRes.z/=modul;
		MassVNormal[i][j]=NormalRes;
	}
	delete[] FlagNormalMap;
	delete[] PloskNormals;

}
//====================================================================================================================
