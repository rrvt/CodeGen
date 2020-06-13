// CodeGenView.h : interface of the CodeGenView class
//


#pragma once
#include "CScrView.h"


class CodeGenDoc;


class CodeGenView : public CScrView {
protected: // create from serialization only

  CodeGenView() { }
  DECLARE_DYNCREATE(CodeGenView)

public:

  virtual ~CodeGenView() { }

  CodeGenDoc* GetDocument() const;


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

