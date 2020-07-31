// CodeGenII.h : main header file for the CodeGenII application

#pragma once
#include "CApp.h"


class CodeGenIIDoc;
class CodeGenIIView;


// CodeGenII:
// See CodeGenII.cpp for the implementation of this class

class CodeGenII : public CApp {

public:

String dbPath;
String mapPath;

                 CodeGenII() noexcept { }
  virtual BOOL   InitInstance();

          void   doOpenDB();
          void   openOneDB(TCchar* title, TCchar* ext, String& path);

  CodeGenIIDoc*  doc()  {return (CodeGenIIDoc*)  CApp::getDoc();}
  CodeGenIIView* view() {return (CodeGenIIView*) CApp::getView();}

  afx_msg void   OnAppAbout();
  afx_msg void   OnHelp();

  DECLARE_MESSAGE_MAP()
  };


extern CodeGenII theApp;

inline void           invalidate() {theApp.invalidate();}
inline CodeGenIIDoc*  doc()  {return theApp.doc();}
inline CodeGenIIView* view() {return theApp.view();}

