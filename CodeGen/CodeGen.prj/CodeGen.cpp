// CodeGen.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "CodeGen.h"
#include "AboutDlg.h"
#include "CodeGenDoc.h"
#include "CodeGenView.h"
#include "IniFileEx.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "ResourceExtra.h"


CodeGen   theApp;                       // The one and only CodeGen object
IniFileEx iniFile(theApp);

// CodeGen

BEGIN_MESSAGE_MAP(CodeGen, CWinAppEx)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &OnHelp)
  ON_COMMAND(ID_App_About,        &OnAppAbout)
END_MESSAGE_MAP()


// CodeGen initialization

BOOL CodeGen::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath);

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

//  EnableShellOpen(); RegisterShellFileTypes(TRUE);       // Enable DDE Execute open

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("Code Generator II")); setTitle(_T("Working Screen"));

  view()->setFont(_T("Courier New"), 12.0);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


int CodeGen::ExitInstance() {return CApp::ExitInstance();}


void CodeGen::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void CodeGen::OnAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

