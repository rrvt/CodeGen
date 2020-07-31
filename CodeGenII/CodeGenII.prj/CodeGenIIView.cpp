// CodeGenIIView.cpp : implementation of the CodeGenIIView class


#include "stdafx.h"
#include "CodeGenIIView.h"
#include "Options.h"
#include "Report.h"
#include "CodeGenIIDoc.h"


// CodeGenIIView

IMPLEMENT_DYNCREATE(CodeGenIIView, CScrView)

BEGIN_MESSAGE_MAP(CodeGenIIView, CScrView)
END_MESSAGE_MAP()




void CodeGenIIView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  if (pDC->IsPrinting()) {setHorzMgns(leftMgn,  rightMgn);  setVertMgns(topMgn,  botMgn);}
  else                   {setHorzMgns(0.33, 0.33); setVertMgns(0.33, 0.33);}

  CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void CodeGenIIView::onPrepareOutput() {report(isPrinting());   CScrView::onPrepareOutput();}


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void CodeGenIIView::printFooter(Display& dev, int pageNo) {report.footer(dev, pageNo); invalidate();}




// CodeGenIIView diagnostics

#ifdef _DEBUG

void CodeGenIIView::AssertValid() const {CScrollView::AssertValid();}

void CodeGenIIView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
CodeGenIIDoc* CodeGenIIView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CodeGenIIDoc))); return (CodeGenIIDoc*)m_pDocument;}

#endif //_DEBUG
