// CodeGenIIView.h : interface of the CodeGenIIView class


#pragma once
#include "CScrView.h"
#include "NoteRptB.h"
#include "TableDscRpt.h"


class CodeGenIIDoc;



class CodeGenIIView : public CScrView {

NoteRptB    dspNote;
NoteRptB    prtNote;
TableDscRpt dspDsc;
TableDscRpt prtDsc;

protected: // create from serialization only

  CodeGenIIView() noexcept;
  DECLARE_DYNCREATE(CodeGenIIView)

public:

  virtual ~CodeGenIIView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool isNotePad, bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

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

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in CodeGenIIView.cpp
inline CodeGenIIDoc* CodeGenIIView::GetDocument() const
   { return reinterpret_cast<CodeGenIIDoc*>(m_pDocument); }
#endif

