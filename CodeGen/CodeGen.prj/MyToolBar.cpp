// My ToolBar


#include "pch.h"
#include "MyToolBar.h"
#include "Resource.h"


static int NoOfButtonControls =  1;
static int NoOfButtons        = 10;



MyToolBar::MyToolBar() : cboBox(createCboBox(ID_CB))
                                          {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}


bool MyToolBar::addButton( uint id, TCchar* caption) {
//  if (id == button.getId()) return add(button,  id, caption);

  return false;
  }


bool MyToolBar::addEditBox(uint id, int noChars)              {
//  if (id == editBox.getId()) return add(editBox, id, noChars);

  return false;
  }


CString MyToolBar::getText(uint id) {

//  if (id == editBox.getId()) {return ToolBarBase::getText(editBox);}

  return _T("");
  }


#ifdef DocView

bool MyToolBar::addMenu(uint id, int idr, TCchar* caption) {
#if 0
  if      (id == menu.getId())      return add(menu,     id, idr, caption);
  else if (id == menu1.getId())     return add(menu1,    id, idr, caption);
  else if (id == saveMenu.getId())  return add(saveMenu, id, idr, caption);
#endif
  return false;
  }


bool MyToolBar::addMenu(uint id, CCbxItem cbxItem[], int n, TCchar* caption) {
#if 0
  if      (id == menu.getId())      return add(menu,     id, cbxItem, n, caption);
  else if (id == menu1.getId())     return add(menu1,    id, cbxItem, n, caption);
  else if (id == saveMenu.getId())  return add(saveMenu, id, cbxItem, n, caption);
#endif
  return false;
  }


bool MyToolBar::addMenu(uint id, int idr, int index) {
#if 0
  if (id == menu.getId())     return add(menu,     id, idr, index);
  if (id == menu1.getId())    return add(menu1,    id, idr, index);
  if (id == saveMenu.getId()) return add(saveMenu, id, idr, index);
#endif
  return false;
  }

#endif


void MyToolBar::setCboCaption(uint id, TCchar* txt) {
  if      (id == cboBox.getId())  ToolBarBase::setCboCaption(cboBox,  txt);
#if 0
  else if (id == cboBox1.getId()) ToolBarBase::setCboCaption(cboBox1, txt);
#ifndef DocView
  else if (id == cboMenu.getId())  ToolBarBase::setCboCaption(cboMenu,  txt);
  else if (id == cboMenu1.getId()) ToolBarBase::setCboCaption(cboMenu1, txt);
#endif
#endif
  }


void MyToolBar::setCboWthPrct(uint id, int percent) {
  if      (id == cboBox.getId())  ToolBarBase::setCboWthPrct(cboBox,  percent);
#if 0
  else if (id == cboBox1.getId()) ToolBarBase::setCboWthPrct(cboBox1, percent);
#ifndef DocView
  else if (id == cboMenu.getId())  ToolBarBase::setCboWthPrct(cboMenu,  percent);
  else if (id == cboMenu1.getId()) ToolBarBase::setCboWthPrct(cboMenu1, percent);
#endif
#endif
  }


void MyToolBar::setCboHeight(uint id) {
  if      (id == cboBox.getId())  ToolBarBase::setCboHeight(cboBox);
#if 0
  else if (id == cboBox1.getId()) ToolBarBase::setCboHeight(cboBox1);
#ifndef DocView
  else if (id == cboMenu.getId())  ToolBarBase::setCboHeight(cboMenu);
  else if (id == cboMenu1.getId()) ToolBarBase::setCboHeight(cboMenu1);
#endif
#endif
  }


void MyToolBar::dispatch(uint id) {
  if      (id == cboBox.getId())    ToolBarBase::dispatch(cboBox);
#if 0
  else if (id == cboBox1.getId())   ToolBarBase::dispatch(cboBox1);
#ifndef DocView
  else if (id == cboMenu.getId())  ToolBarBase::dispatch(cboMenu);
  else if (id == cboMenu1.getId()) ToolBarBase::dispatch(cboMenu1);
#endif
#endif
  }


// Manipulate tuple in the ComboBox

bool MyToolBar::addCboItem(uint id, TCchar* txt, ulongP data) {

  if      (id == cboBox.getId())  {return ToolBarBase::addCboItem(cboBox,  txt, data);}
#if 0
  else if (id == cboBox1.getId()) {return ToolBarBase::addCboItem(cboBox1, txt, data);}
#endif
  return false;
  }


bool MyToolBar::addCboItemSrtd(uint id, TCchar* txt, ulongP data) {

  if      (id == cboBox.getId())  {return ToolBarBase::addCboItemSrtd(cboBox,  txt, data);}
#if 0
  else if (id == cboBox1.getId()) {return ToolBarBase::addCboItemSrtd(cboBox1, txt, data);}
#endif
  return false;
  }


bool MyToolBar::setCurSel(uint id, int index) {
#if 0
  if (id == cboBox1.getId()) return ToolBarBase::setCurSel(cboBox1, index);
#endif
  return false;
  }


bool MyToolBar::setCurSel(uint id, TCchar* tc) {
#if 0
  if (id == cboBox1.getId()) return ToolBarBase::setCurSel(cboBox1, tc);
#endif
  return false;
  }


int  MyToolBar::getCurSel(uint id) {
#if 0
  if (id == cboBox1.getId()) return ToolBarBase::getCurSel(cboBox1);
#endif
  return -1;
  }


bool MyToolBar::getCurSel(uint id, String& s, ulongP& data) {
  if (id == cboBox.getId())  return ToolBarBase::getCurSel(cboBox,  s, data);
#if 0
  if (id == cboBox1.getId()) return ToolBarBase::getCurSel(cboBox1, s, data);
#endif
  return false;
  }


ulongP MyToolBar::getData(uint id, int index) {
#if 0
  if (id == cboBox1.getId()) return ToolBarBase::getData(cboBox1, index);
#endif
  return 0;
  }


int MyToolBar::find(uint id, TCchar* tc) {
#if 0
  if (id == cboBox1.getId()) return ToolBarBase::find(cboBox1, tc);
#endif
  return -1;
  }



