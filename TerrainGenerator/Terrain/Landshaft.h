#pragma once
#include "GlLib.h"
#include "CVector.h"
#include "Shader.h"
#include "Texture.h"
class CLandshaft
{
struct TLandState
{
	bool LandState;
	bool TextureState;
	bool InitState;   //сосото€ние инициализации обњекта (0-не инициализирован, 1-иниц)
} States;
private:
	TLandProperties LandProperties; 
	int **MassHeight;
	int **Mass;//
	CVector3 **MassVNormal;

    CShader MixingShader;                            // объект(программа) шейдер смешивани€
	GLuint  MemoryPt;
	CTexture TexMixing[4];                           // 3 текстуры, которые используютс€ дл€ смешивани€(буду ее тоже называть текстурной картоц)

	CVector3 GenTrianglePNormal(CVector3 p1,CVector3 p2,CVector3 p3);// вычисл€ем нормать плоскости (p1,p2,p3)
	void LoadMapFromDC(CDC *pDC,int w,int h);
	void LoadToMemory();
	void GenVNormals();
	void LoadTextures(CTextureProp propVec);
public:
	CLandshaft(void);
	
	bool Init(TLandProperties Properties);
	//void GetHeight(int i, int j);
	void Render();
	double GetHeight(int x,int y)
	{
		return Mass[x][y];
	}


	bool IsInitState(){return States.InitState;}
	~CLandshaft(void);
};
