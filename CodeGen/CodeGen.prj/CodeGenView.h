// CodeGenView.h : interface of the CodeGenView class


#pragma once
#include "ScrollView.h"
#include "CodeGen.h"
#include "CodeGenDoc.h"
#include "DisplayNtPd.h"
#include "Printer.h"


class CodeGenDoc;


class CodeGenView : public ScrollView {
protected:

  CodeGenView() noexcept;

  DECLARE_DYNCREATE(CodeGenView)

public:

  virtual         ~CodeGenView() { }
  virtual BOOL     PreCreateWindow(CREATESTRUCT& cs) {return ScrollView::PreCreateWindow(cs);}

  virtual void     OnInitialUpdate()                 {ScrollView::OnInitialUpdate();}

  virtual void     setHeader(DisplayNtPd& dsplyNp)
                                               {dsplyNp.setHeader(_T("Arial"), 120, &getHeader);}
  virtual void     setFooter(DisplayNtPd& dsplyNp)
                                               {dsplyNp.setFooter(_T("arial"), 120, &getFooter);}
  virtual NotePad& onPrepareOutput() {return doc()->getData();}
                                                        // Create output on a notepad and return it
// Print Data functions

  virtual bool     onPreparePrinter(PrinterInfo& info);
  virtual NotePad& onPreparePrinting() {return doc()->getData();}
  virtual void     setHeader(PrintNtPd& prntNp)
                                              {prntNp.setHeader(_T("Arial"), 120, &getHeader);}
  virtual void     setFooter(PrintNtPd& prntNp)
                                              {prntNp.setFooter(_T("Courier New"), 60, getFooter);}
  static  void     getHeader(NotePad& np, int pageNo, int noPages)
                                                           {doc()->getHeader(np, pageNo, noPages);}
  static  void     getFooter(NotePad& np, int pageNo, int noPages)
                                                           {doc()->getFooter(np, pageNo, noPages);}
  CodeGenDoc*      GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void onFilePrint();
  afx_msg void onFilePrintPreview();
  afx_msg void onSetupPrinter();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in CodeGenView.cpp
inline CodeGenDoc* CodeGenView::GetDocument() const
   { return reinterpret_cast<CodeGenDoc*>(m_pDocument); }
#endif




////////////==========================
#if 0
  virtual void       initNoteOrietn() { }
  virtual void       saveNoteOrietn() { }
  virtual void       initRptOrietn()  { }
  virtual void       saveRptOrietn()  { }
  virtual PrtrOrient getOrientation() {return prtNote.prtrOrietn;}


  virtual void       onDisplayOutput();
  virtual void       onPreparePrinting(CPrintInfo* info) {prtNote.onPreparePrinting(info);}
  virtual void       onBeginPrinting();

  virtual void       printFooter(DevStream& dev, int pageNo);
  virtual void       OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
#endif
//  afx_msg void onOptions();
//  afx_msg void onRptOrietn();

