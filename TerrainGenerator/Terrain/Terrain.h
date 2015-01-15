// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Terrain.h : main header file for the Terrain application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "GLContainer.h"
#include "MainFrm.h"
#include "DrawMapFrame.h"
#include "DrawTextureFrame.h"
//#include "DrawingFrame.h"

// CTerrainApp:
// See Terrain.cpp for the implementation of this class
//

class CTerrainApp : public CWinAppEx
{
public:
	CTerrainApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	CGLContainer *GLContainer;
	CDrawMapFrame *DrawMapFrame;
	CDrawTextureFrame *DrawTextureFrame;
	UINT  m_nAppLook;
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTerrainApp theApp;
