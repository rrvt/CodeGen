// CodeGen.h : main header file for the CodeGen application
//
#pragma once

#ifndef __AFXWIN_H__
  #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "CodeGenDoc.h"
#include "MapTable.h"
#include "IniFile.h"


extern TCchar* FileSection;
extern TCchar* HeaderExt;
extern TCchar* CppExt;


class CodeGenView;


class CodeGen : public CWinApp {

CodeGenDoc*  doc;
CodeGenView* view;

public:

String version;

String dbPath;
String mapPath;

  CodeGen();

  void doOpenDB();
  void openOneDB(TCchar* title, TCchar* ext, String& path);

  bool getDocument();
  void invalidate();
  bool getView();

// Overrides
public:
  virtual BOOL InitInstance();

// Implementation
  afx_msg void OnAppAbout();
  DECLARE_MESSAGE_MAP()

  friend void        invalidateView();
  friend CodeGenDoc* doc();
  };


extern CodeGen theApp;


inline void invalidateView() {theApp.invalidate();}
inline CodeGenDoc* doc() {return theApp.getDocument() ? theApp.doc : 0;}
