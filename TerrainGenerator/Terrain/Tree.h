#pragma once
#include "GLlib.h"
	#define MAXLEVEL 6
class CTree
{
	typedef enum { NOTALLOWED, MOUNTAIN, TREE, ISLAND, BIGMTN, STEM, LEAF, 
               MOUNTAIN_MAT, WATER_MAT, LEAF_MAT, TREE_MAT, STEMANDLEAVES,
               AXES } DisplayLists;
private:
	GLuint  MemoryPt;
	TTreeProperties TreeProp;
	void LoadTreeToMemory();

	void CreateTree(void);
	void CTree::FractalTree(int level);
	void CreateTreeLists(void);
	void SetupMaterials(void);

public:
	void Init(TTreeProperties Prop);
	void Render();
	
	CTree(void);
	~CTree(void);
};
