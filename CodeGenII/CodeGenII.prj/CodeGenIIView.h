// CodeGenIIView.h : interface of the CodeGenIIView class


#pragma once
#include "CScrView.h"


class CodeGenIIDoc;


class CodeGenIIView : public CScrView {

protected: // create from serialization only

  CodeGenIIView() noexcept { }
  DECLARE_DYNCREATE(CodeGenIIView)

public:

  virtual ~CodeGenIIView() { }

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput();
  virtual void printFooter(Display& dev, int pageNo);

  CodeGenIIDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

//  DECLARE_MESSAGE_MAP()
public:
  DECLARE_MESSAGE_MAP()
  };


#ifndef _DEBUG  // debug version in CodeGenIIView.cpp
inline CodeGenIIDoc* CodeGenIIView::GetDocument() const
   { return reinterpret_cast<CodeGenIIDoc*>(m_pDocument); }
#endif

