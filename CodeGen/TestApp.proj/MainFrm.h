// MainFrm.h : interface of the MainFrame class


#pragma once

class MainFrame : public CFrameWndEx {

CMFCMenuBar   m_wndMenuBar;
CMFCToolBar   m_wndToolBar;
CMFCStatusBar m_wndStatusBar;

protected:                                          // create from serialization only

  MainFrame() noexcept;

  DECLARE_DYNCREATE(MainFrame)

public:                                             // Overrides

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:                                             // Implementation

  virtual ~MainFrame();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:                                          // Generated message map functions

  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  DECLARE_MESSAGE_MAP()
  };


