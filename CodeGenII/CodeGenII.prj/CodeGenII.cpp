// CodeGenII.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "CodeGenII.h"
#include "About.h"
#include "CodeGenIIDoc.h"
#include "CodeGenIIView.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "MapData.h"
#include "NotePad.h"
#include "Options.h"
#include "Resources.h"


static TCchar* dbExtensions = _T("*.accdb;*.mdb");


CodeGenII theApp;                       // The one and only CodeGenII object
IniFile   iniFile;


// CodeGenII

BEGIN_MESSAGE_MAP(CodeGenII, CWinAppEx)
  ON_COMMAND(ID_DoOpenDB,         &CodeGenII::doOpenDB)
  ON_COMMAND(ID_APP_ABOUT,        &CodeGenII::OnAppAbout)
  ON_COMMAND(ID_FILE_NEW,         &CWinAppEx::OnFileNew)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &CodeGenII::OnHelp)
END_MESSAGE_MAP()


// CodeGenII initialization

BOOL CodeGenII::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(CodeGenIIDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(CodeGenIIView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("Code Gen II")); setTitle(_T("Create C++ Code to Read/Write to Access Database"));

  view()->setFont(_T("Arial"), 120);

  options.load();

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



void CodeGenII::doOpenDB() {
String title;
String ext;

  notePad.clear();

  openOneDB(DBFileKey, dbExtensions, dbPath);

  maps.initializeMaps(DBFileKey, dbPath);

  invalidate();
  }



void CodeGenII::openOneDB(TCchar* title, TCchar* ext,  String& path) {

  iniFile.readString(FileSection, DBFileKey, path);

  if (getPathDlg(title, path, _T(".accdb"), ext, path)) iniFile.writeString(FileSection, DBFileKey, path);
  }



void CodeGenII::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void CodeGenII::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}

