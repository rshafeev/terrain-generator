#include "StdAfx.h"
#include "GLContainer.h"
#include "Terrain.h"
CGLContainer::CGLContainer(void)
{
}

CGLContainer::~CGLContainer(void)
{
	TreeShader.DestroyProgram();
}
void CGLContainer::Create(CVector2 ZInterval, CVector2 ScaleXY,CImage *RImage,CImage *GImage,CImage *BImage)		//
{
	this->ScaleXY=ScaleXY;			//растяжение 
	this->ZInterval=ZInterval;
		prop.RImage = RImage;
	prop.BImage = BImage;
	prop.GImage=GImage;
}
void CGLContainer::Init()		//
{
	CDrawTextureFrame *texFrame = theApp.DrawTextureFrame;
	prop.ZInterval=ZInterval;
	prop.ScaleXY=ScaleXY;
	prop.TextureVecProp = new CTextureProp(texFrame->GetW(),texFrame->GetH(),texFrame->GetMemoryDC());
	Landshaft.Init(prop);

	  TreeShader.LoadShader("Shaders\\Tree.vert",			//загрузили вершинный шейдер смешивания
							"Shaders\\Tree.frag");		//загрузили фрагментный шейдер смешивания
}
void CGLContainer::Render()			//перерисовка
{
	Landshaft.Render();
	TreeShader.Use();
	for (int i=0; i<Trees.size(); i++)
	{
		Trees[i]->Render();
	}
	TreeShader.Close();
}
void CGLContainer::AddTree(TTreeProperties Prop)		//добавляем деревья
{
	//		theApp.DrawMapFrame->W - theApp.DrawMapFrame->picture->TreesProp[i].x;
	Prop.x = theApp.DrawMapFrame->W   - Prop.x;
	CTree *add=new CTree;
	Prop.ScaleXY = ScaleXY;
	add->Init(Prop);
	Trees.push_back(add);


}
