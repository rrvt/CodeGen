// CodeGen.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "CodeGen.h"
#include "About.h"
#include "CodeGenDoc.h"
#include "CodeGenView.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "Options.h"
#include "Resources.h"


CodeGen theApp;                       // The one and only CodeGen object
IniFile   iniFile;


// CodeGen

BEGIN_MESSAGE_MAP(CodeGen, CWinAppEx)
  ON_COMMAND(ID_APP_ABOUT,        &OnAppAbout)
  ON_COMMAND(ID_Help,             &OnHelp)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &OnFilePrintSetup)
END_MESSAGE_MAP()


// CodeGen initialization

BOOL CodeGen::InitInstance() {

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
    RUNTIME_CLASS(CodeGenDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(CodeGenView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("Code Gen")); setTitle(_T("Create C++ Code to Read/Write to Access Database"));

  view()->setFont(_T("Courier New"), 12.0);

  options.load();    view()->setOrientation(options.orient);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



void CodeGen::OnFilePrintSetup() {view()->setPrntrOrient(getDevMode()); CWinApp::OnFilePrintSetup();}


void CodeGen::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void CodeGen::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


