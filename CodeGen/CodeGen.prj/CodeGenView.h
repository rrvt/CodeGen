// CodeGenView.h : interface of the CodeGenView class


#pragma once
#include "CScrView.h"
#include "ReportNtPd.h"


class CodeGenDoc;


class CodeGenView : public CScrView {
protected:

  CodeGenView() noexcept;

  DECLARE_DYNCREATE(CodeGenView)

public:

  virtual ~CodeGenView() { }

  virtual void       initNoteOrietn() { }
  virtual void       saveNoteOrietn() { }
  virtual void       initRptOrietn()  { }
  virtual void       saveRptOrietn()  { }
  virtual PrtrOrient getOrientation() {return prtNote.prtrOrietn;}

  virtual BOOL       PreCreateWindow(CREATESTRUCT& cs);

  virtual void       onDisplayOutput();
  virtual void       onPreparePrinting(CPrintInfo* info) {prtNote.onPreparePrinting(info);}
  virtual void       onBeginPrinting();

  virtual void       printFooter(DevStream& dev, int pageNo);
  virtual void       OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  CodeGenDoc*        GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in CodeGenView.cpp
inline CodeGenDoc* CodeGenView::GetDocument() const
   { return reinterpret_cast<CodeGenDoc*>(m_pDocument); }
#endif

