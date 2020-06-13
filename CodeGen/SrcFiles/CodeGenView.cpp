// CodeGenView.cpp : implementation of the CodeGenView class
//

#include "stdafx.h"
#include "CodeGenView.h"
#include "CodeGenDoc.h"


// CodeGenView

IMPLEMENT_DYNCREATE(CodeGenView, CScrView)

BEGIN_MESSAGE_MAP(CodeGenView, CScrView)
  ON_COMMAND(ID_FILE_PRINT,         &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT,  &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()


// CodeGenView diagnostics

#ifdef _DEBUG
void CodeGenView::AssertValid() const {CScrollView::AssertValid();}

void CodeGenView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

CodeGenDoc* CodeGenView::GetDocument() const // non-debug version is inline
            {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CodeGenDoc))); return (CodeGenDoc*)m_pDocument;}
#endif //_DEBUG
