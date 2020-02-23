// CodeGenView.cpp : implementation of the CodeGenView class
//

#include "stdafx.h"
#include "CodeGenDoc.h"
#include "CodeGenView.h"
#include "CodeGen.h"

#include "DisplayView.h"
#include "Display.h"
#include "NotePad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CodeGenView

IMPLEMENT_DYNCREATE(CodeGenView, CScrollView)

BEGIN_MESSAGE_MAP(CodeGenView, CScrollView)
  ON_COMMAND(ID_FILE_PRINT,         &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT,  &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CodeGenView construction/destruction

CodeGenView::CodeGenView() { }

CodeGenView::~CodeGenView() { }


BOOL CodeGenView::PreCreateWindow(CREATESTRUCT& cs) {return CScrollView::PreCreateWindow(cs);}


void CodeGenView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* sb)
                                                            {CScrollView::OnVScroll(nSBCode, nPos, sb);}


void CodeGenView::OnInitialUpdate() {CScrollView::OnInitialUpdate();}


void CodeGenView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
                                  {setScrollSize(dspView); CScrollView::OnUpdate(pSender, lHint, pHint);}


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

BOOL CodeGenView::OnPreparePrinting(CPrintInfo* pInfo) {
BOOL rslt;

  pInfo->m_nNumPreviewPages = 0;

  prtView.OnPreparePrinting(pInfo);

  rslt = DoPreparePrinting(pInfo);                  // Get printer dialog box

  return rslt;
  }


void CodeGenView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
                       {Date d;   d.getToday();  prtView.OnBeginPrinting(pDC, pInfo, String("SDE"), d);}


void CodeGenView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
DisplayView* dv = pInfo ? &prtView : &dspView;

  dv->OnPreparePrinting(pInfo);

  CScrollView::OnPrepareDC(pDC, pInfo);

  dv->OnPrepareDC(_T("Arial"), 120, pDC, pInfo);
  }


void CodeGenView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {prtView.OnPrint(pInfo);}


void CodeGenView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {if (!pInfo->m_bPreview) invalidateView();}


void CodeGenView::OnDraw(CDC* pDC) {dspView.OnDraw(); setScrollSize(dspView);}


void CodeGenView::setScrollSize(DisplayView& dv) {
RECT  winSize;
CSize s;
CSize pageSize;
CSize scrollSize;

  GetClientRect(&winSize); dv.getScrollSize(winSize, s, pageSize, scrollSize);

  SetScrollSizes(MM_TEXT, s, pageSize, scrollSize);
  }


// CodeGenView diagnostics

#ifdef _DEBUG
void CodeGenView::AssertValid() const
{
  CScrollView::AssertValid();
}

void CodeGenView::Dump(CDumpContext& dc) const
{
  CScrollView::Dump(dc);
}

CodeGenDoc* CodeGenView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CodeGenDoc)));
  return (CodeGenDoc*)m_pDocument;
}
#endif //_DEBUG


// CodeGenView message handlers
