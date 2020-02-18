// CodeGenView.h : interface of the CodeGenView class
//


#pragma once
#include "DisplayView.h"


class CodeGenView : public CScrollView {
protected: // create from serialization only
  CodeGenView();
  DECLARE_DYNCREATE(CodeGenView)

// Attributes

DisplayView dspView;

public:
  CodeGenDoc* GetDocument() const;

// Overrides
public:
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* sb);
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

          void dspInitialEntry();

protected:

  virtual void OnInitialUpdate(); // called first time after construct
  virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnPrepareDC(    CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void OnPrint(        CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

          void printFooter();

private:
          void setScrollSize();

// Implementation
public:
  virtual ~CodeGenView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CodeGenView.cpp
inline CodeGenDoc* CodeGenView::GetDocument() const
   { return reinterpret_cast<CodeGenDoc*>(m_pDocument); }
#endif

