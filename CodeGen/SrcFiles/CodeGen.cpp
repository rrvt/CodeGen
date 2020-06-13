// CodeGen.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "CodeGen.h"
#include "About.h"
#include "CodeGenDoc.h"
#include "CodeGenView.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MainFrm.h"
#include "MapData.h"
#include "NotePad.h"
#include "Resources.h"


TCchar* HeaderExt = _T("*.h");
TCchar* CppExt    = _T("*.cpp");


static TCchar* dbExtensions = _T("*.accdb;*.mdb");


IniFile iniFile;



// CodeGen

BEGIN_MESSAGE_MAP(CodeGen, CWinApp)
  ON_COMMAND(ID_DoOpenDB,  &CodeGen::doOpenDB)
  ON_COMMAND(ID_APP_ABOUT, &CodeGen::OnAppAbout)
END_MESSAGE_MAP()


// CodeGen construction

CodeGen::CodeGen() : doc(0), view(0) {
ResourceData res;
String       appID;

  res.getVersion(version);

  if (res.getAppID(appID)) SetAppID(appID);
  }


// The one and only CodeGen object

CodeGen theApp;


// CodeGen initialization

BOOL CodeGen::InitInstance() {
  // InitCommonControlsEx() is required on Windows XP if an application
  // manifest specifies use of ComCtl32.dll version 6 or later to enable
  // visual styles.  Otherwise, any window creation will fail.
  INITCOMMONCONTROLSEX InitCtrls;
  InitCtrls.dwSize = sizeof(InitCtrls);
  // Set this to include all the common control classes you want to use
  // in your application.
  InitCtrls.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&InitCtrls);

  CWinApp::InitInstance();

  iniFile.getAppDataPath(m_pszHelpFilePath);

  iniFile.readString(FileSection, DBFileKey,      dbPath);
  iniFile.readString(FileSection, GenFilePathKey, mapPath);

  if (mapPath.empty())
                  {mapPath = getPath(dbPath); iniFile.writeString(FileSection, GenFilePathKey, mapPath);}

  notePad.clear();

  maps.initializeMaps(DBFileKey, dbPath);

  // Initialize OLE libraries

  if (!AfxOleInit()) {AfxMessageBox(IDP_OLE_INIT_FAILED); return FALSE;}

  AfxEnableControlContainer();

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  // of your final executable, you should remove from the following
  // the specific initialization routines you do not need
  // Change the registry key under which our settings are stored
  // TODO: You should modify this String to be something appropriate
  // such as the name of your company or organization

//  SetRegistryKey(_T("Local AppWizard-Generated Applications"));

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)
  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(CodeGenDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(CodeGenView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Enable DDE Execute open

  EnableShellOpen(); RegisterShellFileTypes(TRUE);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo; ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  if (getView()) {view->setAuthor(_T("Code Gen")); view->setFont(_T("Courier New"));}

  mainFrame = (MainFrame*) m_pMainWnd;

  setTitle(_T("CodeGen -- Generate Code for an Interface to an Access Database"));

  // The one and only window has been initialized, so show and update it

  m_pMainWnd->ShowWindow(SW_SHOW); m_pMainWnd->UpdateWindow(); return TRUE;
  }



void CodeGen::doOpenDB() {
String title;
String ext;

  notePad.clear();

  openOneDB(DBFileKey, dbExtensions, dbPath);

  maps.initializeMaps(DBFileKey, dbPath);

  invalidate();
  }



void CodeGen::openOneDB(TCchar* title, TCchar* ext,  String& path) {

  iniFile.readString(FileSection, DBFileKey, path);

  if (getPathDlg(title, path, _T(".accdb"), ext, path)) iniFile.writeString(FileSection, DBFileKey, path);
  }


void CodeGen::invalidate() {if (getView()) view->Invalidate();}


bool CodeGen::getView() {
POSITION   pos;

  if (view) return true;

  if (!getDocument()) return false;

  pos  = doc->GetFirstViewPosition();        if (!pos)  return false;
  view = (CodeGenView*) doc->GetNextView(pos);

  return view != 0;
  }



bool CodeGen::getDocument() {

  if (doc) return true;

  POSITION      pos = GetFirstDocTemplatePosition(); if (!pos) return false;
  CDocTemplate* t   = GetNextDocTemplate(pos);       if (!t)   return false;

  pos = t->GetFirstDocPosition();                    if (!pos) return false;
  doc = (CodeGenDoc*) t->GetNextDoc(pos);              if (!doc) return false;

  return true;
  }

#if 0
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog {
public:

  enum { IDD = IDD_ABOUTBOX };                          // Dialog Data

               CAboutDlg();
  virtual BOOL OnInitDialog();

               void setVersion();

protected:

  virtual void DoDataExchange(CDataExchange* pDX);      // DDX/DDV support

// Implementation
protected:
  DECLARE_MESSAGE_MAP()
public:
  };
#endif

// App command to run the dialog

void CodeGen::OnAppAbout() {CAboutDlg aboutDlg;  aboutDlg.DoModal();}

#if 0
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {}


BOOL CAboutDlg::OnInitDialog() {CDialog::OnInitDialog();  setVersion();  return TRUE;}


void CAboutDlg::setVersion() {
ResourceData res;

  SetDlgItemText(IDC_NameVer, res.getAboutNameVer());
  }


void CAboutDlg::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
#endif
