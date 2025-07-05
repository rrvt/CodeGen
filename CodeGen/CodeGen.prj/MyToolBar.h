// My ToolBar


#pragma once
#include "ToolBarBase.h"


struct CbxItem;


class MyToolBar : public ToolBarBase {

TBCboBx cboBx;

public:

  MyToolBar();
 ~MyToolBar() { }

  bool    addButton( uint id, TCchar* caption);
  bool    addEditBox(uint id, int     noChars);
  CString getText(uint id);

// Tool Bar ComboBox Functions

  void    clearCbx(  uint id);
  bool    addCBx(    uint id);
  bool    addCBx(    uint id, int     idr, TCchar* caption);
  bool    addCbxItem(uint id, TCchar* txt, int data = 0);
  bool    addCBx(    uint id, CbxItem cbxItem[], int n, TCchar* caption);
  bool    addCbxItemSorted(uint id, TCchar* txt, int data = 0);

  void*   getCbxData(uint cbxId, int index);
  int     getCurSel( uint cbxId);
  bool    getCurSel( uint cbxId, String& s, void*& data);

  bool    setCurSel( uint cbxId, int index);
  bool    setCurSel( uint cbxId, TCchar* tc);

  uint    getCbxCount(uint id);
  void    setCaption( uint id, TCchar* caption);

  void    setWthPercent(uint id, int prcnt);            // good for Menus and ComboBoxes
  void    setWidth(     uint id);
  void    setHeight(    uint id);
  };



///--------------------

#ifdef ButtonDefs

#if 0
TBButton  button;
TBEditBox editBox;

#ifdef DocViewTB

TBMenu    menu;
TBMenu    menu1;

#else

TBCbxMenu cbxMenu;
TBCbxMenu cbxMenu1;

#endif
#endif


#if 0
#ifdef DocViewTB

TBMenu    saveMenu;

#else

TBCboBx   cboBx1;

#endif
#endif
#endif
#ifdef DocViewTB
#include "TBCbxMenu.h"
#endif
#ifdef DocViewTB

  bool    addMenu(   uint id, int     idr, TCchar* caption);
  bool    addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);
  void    dispatch(uint id);

#endif
//#define MyButtonDefs
//#define DocViewTB
//#include "TBButton.h"
//#include "TBEditBox.h"
//#include "TBMenu.h"
//#include "TBCboBx.h"

#if 0
  bool    addMenu(   uint id, int     idr, TCchar* caption);
  bool    addMenu(   uint id, int     idr, int     index);
  bool    addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);
#endif

