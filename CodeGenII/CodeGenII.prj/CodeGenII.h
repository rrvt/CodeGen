// CodeGenII.h : main header file for the CodeGenII application

#pragma once
#include "CApp.h"


class CodeGenIIDoc;
class CodeGenIIView;
class MainFrame;


// CodeGenII:
// See CodeGenII.cpp for the implementation of this class

class CodeGenII : public CApp {

public:

               CodeGenII() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          CodeGenIIDoc*  doc()     {return (CodeGenIIDoc*)  CApp::getDoc();}
          CodeGenIIView* view()    {return (CodeGenIIView*) CApp::getView();}
          MainFrame*     mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
  };


extern CodeGenII theApp;

inline void           invalidate() {theApp.invalidate();}
inline CodeGenIIDoc*  doc()        {return theApp.doc();}
inline CodeGenIIView* view()       {return theApp.view();}

