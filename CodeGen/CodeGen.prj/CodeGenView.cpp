// CodeGenView.cpp : implementation of the CodeGenView class


#include "stdafx.h"
#include "CodeGenView.h"
#include "CodeGen.h"
#include "CodeGenDoc.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"
#include "RptOrientDlgOne.h"


// CodeGenView

IMPLEMENT_DYNCREATE(CodeGenView, CScrView)

BEGIN_MESSAGE_MAP(CodeGenView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


CodeGenView::CodeGenView() noexcept {          //dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad())
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL CodeGenView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void CodeGenView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);


  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void CodeGenView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl00 = _T("Report:");

  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);

  if (dlg.DoModal() == IDOK) {prtNote.prtrOrietn = printer.toOrient(dlg.ntpd);   saveNoteOrietn();}
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void CodeGenView::onBeginPrinting() {prtNote.onBeginPrinting(*this);}


void CodeGenView::onDisplayOutput() {dspNote.display(*this);}




// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void CodeGenView::printFooter(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    }
  }


void CodeGenView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


void CodeGenView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


// CodeGenView diagnostics

#ifdef _DEBUG

void CodeGenView::AssertValid() const {CScrollView::AssertValid();}

void CodeGenView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
CodeGenDoc* CodeGenView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CodeGenDoc))); return (CodeGenDoc*)m_pDocument;}

#endif //_DEBUG
