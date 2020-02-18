// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "CodeGen.h"

#include "MainFrm.h"
#include "WindowData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
  ON_WM_CREATE()
  ON_WM_MOVE()
  ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
  ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
};


// MainFrame construction/destruction

MainFrame::MainFrame()
{
  // TODO: add member initialization code here
}

MainFrame::~MainFrame()
{
}


int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
    | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
  {
    TRACE0("Failed to create toolbar\n");
    return -1;      // fail to create
  }

  if (!m_wndStatusBar.Create(this) ||
    !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
  {
    TRACE0("Failed to create status bar\n");
    return -1;      // fail to create
  }

  // TODO: Delete these three lines if you don't want the toolbar to be dockable
  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndToolBar);

  SetTitle(_T("Entry Report"));
  return 0;
}


BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs) {
int        xSize = ::GetSystemMetrics(SM_CXSCREEN);
int        ySize = ::GetSystemMetrics(SM_CYSCREEN);
RECT       rect;
WindowData winData(iniFile);

  cs.cx = xSize * 45 / 100;  cs.cy = ySize * 7 / 10;

  winData.getSize(rect);

  cs.x = rect.left; cs.y = rect.top;

  if (rect.right  > cs.cx) cs.cx = rect.right;
  if (rect.bottom > cs.cy) cs.cy = rect.bottom;

  return CFrameWnd::PreCreateWindow(cs) ? TRUE : FALSE;
  }




void MainFrame::OnMove(int x, int y) {
RECT       rect;
WindowData winData(iniFile);

  GetWindowRect(&rect); winData.savePos(rect.left, rect.top);

  CFrameWnd::OnMove(x, y);
  }



void MainFrame::OnSize(UINT nType, int cx, int cy) {
RECT       rect;
WindowData winData(iniFile);

  GetWindowRect(&rect);

  if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
                                    winData.saveSize(rect.right - rect.left, rect.bottom - rect.top);
  CFrameWnd::OnSize(nType, cx, cy);
  }


// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
  CFrameWnd::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
  CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// MainFrame message handlers



