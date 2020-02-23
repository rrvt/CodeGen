// TestAppView.cpp : implementation of the TestAppView class


#include "stdafx.h"
#include "TestAppView.h"
#include "TestApp.h"
#include "TestAppDoc.h"
#include "DisplayView.h"
#include "Display.h"
#include "NotePad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// TestAppView

IMPLEMENT_DYNCREATE(TestAppView, CScrollView)

BEGIN_MESSAGE_MAP(TestAppView, CScrollView)
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT,         &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT,  &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()


// TestAppView construction/destruction

TestAppView::TestAppView() noexcept : font(_T("Arial")), author(_T("sde")) { }


TestAppView::~TestAppView() { }


BOOL TestAppView::PreCreateWindow(CREATESTRUCT& cs) {return CScrollView::PreCreateWindow(cs);}


void TestAppView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* sb)
                                                            {CScrollView::OnVScroll(nSBCode, nPos, sb);}


void TestAppView::OnInitialUpdate() {CScrollView::OnInitialUpdate();}


void TestAppView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
                                  {setScrollSize(dspView); CScrollView::OnUpdate(pSender, lHint, pHint);}


// TestAppView printing
/* The following functions are called for printing a page in the order given with one exception:
BOOL OnPreparePrinting(        CPrintInfo* pInfo);  -- 1st
void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);  -- 2nd
     CDC::StartDoc()                                -- 3rd
void OnPrepareDC(    CDC* pDC, CPrintInfo* pInfo);  -- 4th                         <-
     CDC::StartPage()                               -- 5th                          ^
void OnPrint(        CDC* pDC, CPrintInfo* pInfo);  -- 6th                          ^
     CDC::EndPage()                                 -- 7th then loops for each page ^
     CDC::EndDoc()                                  -- after last page
void OnEndPrinting(  CDC* pDC, CPrintInfo* pInfo);  -- last
*/

BOOL TestAppView::OnPreparePrinting(CPrintInfo* pInfo) {
BOOL rslt;

  pInfo->m_nNumPreviewPages = 0;

  prtView.OnPreparePrinting(pInfo);

  rslt = DoPreparePrinting(pInfo);                  // Get printer dialog box

  return rslt;
  }


void TestAppView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
                       {Date d;   d.getToday();  prtView.OnBeginPrinting(pDC, pInfo, author, d);}


void TestAppView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
DisplayView* dv = pInfo ? &prtView : &dspView;

  dv->OnPreparePrinting(pInfo);

  CScrollView::OnPrepareDC(pDC, pInfo);

  dv->OnPrepareDC(font, 120, pDC, pInfo);
  }


void TestAppView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {prtView.OnPrint(pInfo);}


void TestAppView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {if (!pInfo->m_bPreview) invalidate();}


// TestAppView drawing

void TestAppView::OnDraw(CDC* pDC) {dspView.OnDraw(); setScrollSize(dspView);}


void TestAppView::setScrollSize(DisplayView& dv) {
RECT  winSize;
CSize s;
CSize pageSize;
CSize scrollSize;

  GetClientRect(&winSize); dv.getScrollSize(winSize, s, pageSize, scrollSize);

  SetScrollSizes(MM_TEXT, s, pageSize, scrollSize);
  }


// TestAppView diagnostics

#ifdef _DEBUG
void TestAppView::AssertValid() const
{
  CScrollView::AssertValid();
}

void TestAppView::Dump(CDumpContext& dc) const
{
  CScrollView::Dump(dc);
}

TestAppDoc* TestAppView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(TestAppDoc)));
  return (TestAppDoc*)m_pDocument;
}
#endif //_DEBUG


// TestAppView message handlers
