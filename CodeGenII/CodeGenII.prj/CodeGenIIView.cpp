// CodeGenIIView.cpp : implementation of the CodeGenIIView class


#include "stdafx.h"
#include "CodeGenIIView.h"
#include "Options.h"
#include "CodeGenII.h"
#include "CodeGenIIDoc.h"
#include "Resources.h"


// CodeGenIIView

IMPLEMENT_DYNCREATE(CodeGenIIView, CScrView)

BEGIN_MESSAGE_MAP(CodeGenIIView, CScrView)
END_MESSAGE_MAP()


CodeGenIIView::CodeGenIIView() noexcept : dspNote(nMgr.getNotePad()), prtNote(pMgr.getNotePad()),
                                          dspDsc( dMgr.getNotePad()), prtDsc( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL CodeGenIIView::PreCreateWindow(CREATESTRUCT& cs) {return CScrView::PreCreateWindow(cs);}



void CodeGenIIView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setIsNotePad(!notePad.isEmpty() || doc()->dataSrc() == NoteSource);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void CodeGenIIView::onPrepareOutput(bool isNotePad, bool printing) {
DataSource ds = isNotePad ? NoteSource : doc()->dataSrc();

  switch (printing) {
    case true : switch(ds) {
                  case NoteSource     : prtNote.print(*this); break;
                  case DataBaseSource : prtDsc.print(*this);  break;
                  }
                break;

    case false: switch(ds) {
                  case NoteSource     : dspNote.display(*this); break;
                  case DataBaseSource : dspDsc.display(*this);  break;
                  }
                break;
    }

  CScrView::onPrepareOutput(isNotePad, printing);
  }




void CodeGenIIView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  setOrientation(options.orient);

  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void CodeGenIIView::printFooter(Display& dev, int pageNo) {
  switch (doc()->dataSrc()) {
    case NoteSource     : prtNote.footer(dev, pageNo); break;
    case DataBaseSource : prtDsc.footer(dev, pageNo); break;
    }
  }



void CodeGenIIView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NoteSource : break;
    }
  }


void CodeGenIIView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NoteSource : break;
    }
  }



// CodeGenIIView diagnostics

#ifdef _DEBUG

void CodeGenIIView::AssertValid() const {CScrollView::AssertValid();}

void CodeGenIIView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
CodeGenIIDoc* CodeGenIIView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CodeGenIIDoc))); return (CodeGenIIDoc*)m_pDocument;}

#endif //_DEBUG
