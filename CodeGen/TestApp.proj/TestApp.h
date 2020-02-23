// TestApp.h : main header file for the TestApp application

#pragma once
#include "resource.h"       // main symbols
#include "IniFile.h"

class TestAppDoc;
class TestAppView;


// TestApp:
// See TestApp.cpp for the implementation of this class

class TestApp : public CWinAppEx {
String       appID;

CFrameWndEx* mainFrame;
TestAppDoc*  doc;
TestAppView* view;

String databasePath;

public:

String version;

               TestApp() noexcept;

  virtual BOOL InitInstance();

          void setTitle(TCchar* title) {mainFrame->SetWindowText(title);}

          bool getDocument();
          void invalidate();
          bool getView();

  // Implementation

  afx_msg void OnAppAbout();
  DECLARE_MESSAGE_MAP()

  friend TestAppDoc* doc();
  afx_msg void OnFileOpen();
  afx_msg void OnOpendatabase();
};


extern TestApp theApp;

inline void invalidate() {theApp.invalidate();}
inline  TestAppDoc*   doc() {return theApp.getDocument() ? theApp.doc : 0;}
