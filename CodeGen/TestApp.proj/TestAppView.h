// TestAppView.h : interface of the TestAppView class


#pragma once
#include "DisplayView.h"

class TestAppDoc;


class TestAppView : public CScrollView {

protected: // create from serialization only

  TestAppView() noexcept;
  DECLARE_DYNCREATE(TestAppView)

// Attributes

DisplayView dspView;
DisplayView prtView;

String      author;
String      font;

public:

  TestAppDoc* GetDocument() const;

// Operations
public:

          void setAuthor(TCchar* a) {author = a;}
          void setFont(  TCchar* f) {font   = f;}

// Overrides
public:
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* sb);
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

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
          void setScrollSize(DisplayView& dv);

// Implementation
public:
  virtual ~TestAppView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestAppView.cpp
inline TestAppDoc* TestAppView::GetDocument() const
   { return reinterpret_cast<TestAppDoc*>(m_pDocument); }
#endif

