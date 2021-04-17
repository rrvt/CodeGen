// CodeGenIIView.h : interface of the CodeGenIIView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"


class CodeGenIIDoc;


class CodeGenIIView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;

protected: // create from serialization only

  CodeGenIIView() noexcept;

  DECLARE_DYNCREATE(CodeGenIIView)

public:

  virtual ~CodeGenIIView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  CodeGenIIDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in CodeGenIIView.cpp
inline CodeGenIIDoc* CodeGenIIView::GetDocument() const
   { return reinterpret_cast<CodeGenIIDoc*>(m_pDocument); }
#endif

