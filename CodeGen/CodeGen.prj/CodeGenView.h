// CodeGenView.h : interface of the CodeGenView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"


class CodeGenDoc;


class CodeGenView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;

protected: // create from serialization only

  CodeGenView() noexcept;

  DECLARE_DYNCREATE(CodeGenView)

public:

  virtual ~CodeGenView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  CodeGenDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in CodeGenView.cpp
inline CodeGenDoc* CodeGenView::GetDocument() const
   { return reinterpret_cast<CodeGenDoc*>(m_pDocument); }
#endif

