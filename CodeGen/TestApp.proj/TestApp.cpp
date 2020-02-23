
// TestApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestApp.h"
#include "About.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MainFrm.h"
#include "MapData.h"
#include "Resources.h"
#include "TestAppDoc.h"
#include "TestAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


TestApp theApp;                       // The one and only TestApp object
IniFile iniFile;


// TestApp

BEGIN_MESSAGE_MAP(TestApp, CWinAppEx)
  ON_COMMAND(ID_FILE_OPEN,        &TestApp::OnFileOpen)
  ON_COMMAND(ID_APP_ABOUT,        &TestApp::OnAppAbout)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
  ON_COMMAND(ID_OpenDatabase, &TestApp::OnOpendatabase)
END_MESSAGE_MAP()


// TestApp construction

TestApp::TestApp() noexcept : doc(0), view(0) {
ResourceData res;

  res.getVersion(version);

  if (res.getAppID(appID)) SetAppID(appID);
  }


// TestApp initialization

BOOL TestApp::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.open();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(TestAppDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(TestAppView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  if (getView()) {view->setAuthor(_T("Test App")); view->setFont(_T("Arial"));}

  iniFile.readString(FileSection, DBFileKey, databasePath);

  mainFrame = (MainFrame*) m_pMainWnd;

  setTitle(_T("Test App -- Test CodeGen Interface Code to a Database"));

  // The one and only window has been initialized, so show and update it

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


void TestApp::OnFileOpen() {
String path;

  if (!getPathDlg(_T("Test App"), _T("*.txt"), _T("txt"), _T("txt"), path)) return;

  notePad.close();

  if (doc->OnOpenDocument(path)) messageBox(_T("Loaded!"));
  }



void TestApp::OnOpendatabase() {
String title;
String ext;

  notePad.close();

  if (getPathDlg(_T("Database"), 0, _T("accdb"), _T("*.accdb"), databasePath))
                                            iniFile.writeString(FileSection, DBFileKey, databasePath);

  maps.initializeMaps(DBFileKey, databasePath);   invalidate();
  }


void TestApp::invalidate() {if (getView()) view->Invalidate();}


bool TestApp::getView() {
POSITION   pos;

  if (view) return true;

  if (!getDocument()) return false;

  pos  = doc->GetFirstViewPosition();        if (!pos)  return false;
  view = (TestAppView*) doc->GetNextView(pos);

  return view != 0;
  }



bool TestApp::getDocument() {

  if (doc) return true;

  POSITION      pos = GetFirstDocTemplatePosition(); if (!pos) return false;
  CDocTemplate* t   = GetNextDocTemplate(pos);       if (!t)   return false;

  pos = t->GetFirstDocPosition();                    if (!pos) return false;
  doc = (TestAppDoc*) t->GetNextDoc(pos);            if (!doc) return false;

  return true;
  }


void TestApp::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}

