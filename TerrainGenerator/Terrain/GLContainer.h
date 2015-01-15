#pragma once
#include "Landshaft.h"
#include <vector>
#include "Tree.h"
using namespace std;
class CGLContainer
{
private:
	CVector2 ZInterval;
	CVector2 ScaleXY;
CShader TreeShader;    // объект(программа) шейдер смешивания
TLandProperties prop;

	//vector<CTree*> Trees;
public:
	CLandshaft Landshaft;
	void Create(CVector2 ZInterval, CVector2 ScaleXY,CImage *RImage,CImage *GImage,CImage *BImage);
	void Init();
	void Render();
	void AddTree(TTreeProperties Prop);
	vector<CTree*> Trees;

	CGLContainer(void);
	~CGLContainer(void);
};
