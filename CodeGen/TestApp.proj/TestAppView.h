// TestAppView.h : interface of the TestAppView class


#pragma once
#include "CScrView.h"


class TestAppDoc;


class TestAppView : public CScrView {

protected: // create from serialization only

  TestAppView() noexcept { }
  DECLARE_DYNCREATE(TestAppView)

public:

  virtual ~TestAppView() { }

  TestAppDoc* GetDocument() const;

public:
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  DECLARE_MESSAGE_MAP()
  };


#ifndef _DEBUG  // debug version in TestAppView.cpp
inline TestAppDoc* TestAppView::GetDocument() const
   { return reinterpret_cast<TestAppDoc*>(m_pDocument); }
#endif

