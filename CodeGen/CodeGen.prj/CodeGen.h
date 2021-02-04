// CodeGen.h : main header file for the CodeGen application

#pragma once
#include "CApp.h"


class CodeGenDoc;
class CodeGenView;
class MainFrame;


// CodeGen:
// See CodeGen.cpp for the implementation of this class

class CodeGen : public CApp {

public:

                 CodeGen() noexcept : CApp(this) { }
  virtual BOOL   InitInstance();


  CodeGenDoc*  doc()  {return (CodeGenDoc*)  CApp::getDoc();}
  CodeGenView* view() {return (CodeGenView*) CApp::getView();}
  MainFrame*     mainFrm() {return (MainFrame*) m_pMainWnd;}

  afx_msg void   OnFilePrintSetup();
  afx_msg void   OnAppAbout();
  afx_msg void   OnHelp();

  DECLARE_MESSAGE_MAP()
  };


extern CodeGen theApp;

inline void           invalidate() {theApp.invalidate();}
inline CodeGenDoc*  doc()  {return theApp.doc();}
inline CodeGenView* view() {return theApp.view();}

