// Create Table Body File


#include "pch.h"
#include "TableBdy.h"
#include "Capitalize.h"
#include "Declarations.h"
#include "LinSrch.h"
#include "ModNames.h"
#include "NotePad.h"


void TableBdy::create() {

  notePad.clear();

  notePad << _T("// ") << modNames.accTbl << _T(" Table") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("#include \"pch.h\"") << nCrlf;
  notePad << _T("#include \"") << modNames.tblCls << _T(".h\"") << nCrlf;
  notePad << _T("#include \"NotePad.h\"") << nCrlf;
  notePad << _T("#include \"Utilities.h\"") << nCrlf;
  notePad << nCrlf << nCrlf;

  load();                  notePad << nCrlf << nCrlf;
  loadRcd();               notePad << nCrlf << nCrlf;
  store();                 notePad << nCrlf << nCrlf;
  storeRcd();
  addRcd();                notePad << nCrlf << nCrlf;
  copyRcd();               notePad << nCrlf << nCrlf;
  add();                   notePad << nCrlf << nCrlf;
  linSrch.addTblBdyFn();   notePad << nCrlf << nCrlf;
  display();               notePad << nCrlf << nCrlf;
  dispRcd();               notePad << nCrlf << nCrlf;
  setTabs();               notePad << nCrlf << nCrlf;
  }


void TableBdy::load() {
Declarations decl;
String       left;
String       right;

  notePad << _T("bool ") << modNames.tblCls << _T("::load(TCchar* path) {") << nCrlf;
  left  = modNames.setIterCls;
  right = _T("iter(") + modNames.setObj + _T(")");
  decl.add(left, right);
  left  = modNames.setCls + _T('*');
  decl.add(left, _T("set"));
  decl.add(_T("int"), _T("i"));
  decl.output();
  notePad << nCrlf;

  notePad << _T("  if (!open(path)) return false;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  data.clear();") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (i = 0, set = iter(); set; i++, set = iter++) {") << nCrlf;
  notePad << nCrlf;
  notePad << _T("    ") << modNames.rcdCls << _T("* rcd = data.allocate();   ");
  notePad << _T("rcd->load(set);   data = rcd;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("    if (rcd->id > maxID) maxID = rcd->id;") << nCrlf;
  notePad << _T("    }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  close();   return true;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void TableBdy::loadRcd() {
FldsIter     iter(fields);
Field*       fld;
bool         idx;
bool         idxSeen;
Declarations decl;
String       obj;
String       left;
String       right;

  notePad << _T("void ") << modNames.rcdCls << _T("::load(") << modNames.setCls;
  notePad << _T("* set) {") << nCrlf;

  for (idxSeen = false, fld = iter(); fld; fld = iter++) {

    obj = notCaped(fld->name);   idx = !idxSeen && fld->type == IdxFld;

    left = idx ? String(_T("id")) : obj;    if (idx) idxSeen = true;

    left = _T("  ") + left;

    right = _T("= set->") + obj;  decl.add(left, right);
    }
  decl.output();
  notePad << _T("  }") << nCrlf;
  }


void TableBdy::store() {
Declarations decl;
String       left;
String       right;

  notePad << _T("bool ") << modNames.tblCls << _T("::store(TCchar* path) {") << nCrlf;
  decl.add(modNames.tblIter, _T("iter(*this)"));
  left = modNames.rcdCls + _T('*');
  decl.add(left, _T("rcd"));
  right = _T("setIter(") + modNames.setObj + _T(')');
  decl.add(modNames.setIterCls, right);
  left = modNames.setCls + _T('*');
  decl.add(left, _T("set"));
  decl.output();
  notePad << nCrlf;

  notePad << _T("  if (!open(path)) return false;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (rcd = iter(), set = setIter(); rcd; rcd = iter++) if (rcd->dirty) {");
  notePad << nCrlf << nCrlf;
  notePad << _T("    set = setIter.find(rcd->id);   rcd->dirty = false;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("    if (!set)        {rcd->add(") << modNames.setObj << _T("); continue;}");
  notePad << nCrlf << nCrlf;
  notePad << _T("    if (rcd->remove) {set->remove(); iter.remove();  continue;}") << nCrlf;
  notePad << nCrlf;
  notePad << _T("    rcd->store(*set);") << nCrlf;
  notePad << _T("    }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  close();   return true;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void TableBdy::storeRcd() {
  notePad << _T("void ") << modNames.rcdCls << _T("::store(") << modNames.setCls;
  notePad << _T("& set) {set.edit();     copy(set);   set.update();}") << nCrlf;
  }


void TableBdy::addRcd() {
  notePad << _T("void ") << modNames.rcdCls << _T("::add(  ") << modNames.setCls;
  notePad << _T("& set) {set.addNew();   copy(set);   set.update();}") << nCrlf;
  }


void TableBdy::copyRcd() {
FldsIter     iter(fields);
Field*       fld;
bool         idx;
bool         idxSeen;
Declarations decl;
String       obj;
String       left;
String       right;

  notePad << _T("void ") << modNames.rcdCls << _T("::copy(") << modNames.setCls;
  notePad << _T("& set) {") << nCrlf;

  for (idxSeen = false, fld = iter(); fld; fld = iter++) {

    obj = notCaped(fld->name);   idx = !idxSeen && fld->type == IdxFld;

    right = idx ? String(_T("id")) : obj;    if (idx) idxSeen = true;

    right = _T("= ") + right;

    left  = _T("  set.") + obj;

    decl.add(left, right);
    }
  decl.output();
  notePad << _T("  }") << nCrlf;
  }


void TableBdy::add() {

  notePad << modNames.rcdCls << _T("* ") << modNames.tblCls << _T("::add(") << modNames.rcdCls;
  notePad << _T("& rcd) {rcd.id = ++maxID;  rcd.dirty = true;  return data = rcd;}") << nCrlf;
  }


void TableBdy::display() {
Declarations decl;
String       obj;
String       left;
String       right;

  notePad << _T("void ") << modNames.tblCls << _T("::display() {") << nCrlf;
  decl.add(modNames.tblIter, _T("iter(*this)"));
  left = modNames.rcdCls + _T('*');
  decl.add(left, _T("rcd"));
  decl.output();
  notePad << nCrlf;

  notePad << _T("  setTabs();") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  notePad << _T(\"") << modNames.accTbl << _T(" Table\") << nCrlf;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  for (rcd = iter(); rcd; rcd = iter++) rcd->display();") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void TableBdy::dispRcd() {
FldsIter iter(fields);
Field*   fld;
int      i;

  notePad << _T("void ") << modNames.rcdCls << _T("::display() {") << nCrlf;
  notePad << _T("  notePad << nTab << id;") << nCrlf;

  for (i = 1, fld = iter(); fld; i++, fld = iter++) {
    if (fld->type == StgFld)
               {notePad << _T("  notePad << nTab << ") << notCaped(fld->name) << _T(';') << nCrlf;}
    if (i % 6 == 0) notePad << nCrlf;
    }

  notePad << _T("  notePad << nCrlf;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void TableBdy::setTabs() {
Declarations decl;
FldsIter     iter(fields);
Field*       fld;
String       s;
int          nStgs;

  notePad << _T("static const int nTabs = 10;") << nCrlf;
  notePad << nCrlf << nCrlf;

  notePad << _T("void ") << modNames.tblCls << _T("::setTabs() {") << nCrlf;
  decl.add(modNames.tblIter, _T("iter(*this)"));
  s = modNames.rcdCls + _T('*');    decl.add(s, _T("rcd"));
  decl.add(_T("int"), _T("max"));
  decl.add(_T("int"), _T("nFldsLn"));
  decl.add(_T("int"), _T("tabs[nTabs]"));
  decl.add(_T("int"), _T("tab"));
  decl.add(_T("int"), _T("i"));
  decl.add(_T("int"), _T("n"));
  decl.output();
  notePad << nCrlf;

  notePad << _T("  for (max = 0, rcd = iter(); rcd; rcd = iter++) {") << nCrlf;
  decl.clear();
  for (nStgs = 0, fld = iter(); fld; fld = iter++) if (fld->type == StgFld) {
    nStgs++, s = _T("    maxLng(rcd->") + notCaped(fld->name) + _T(',');   decl.add(s, _T("max)"));
    }
  decl.output();
  notePad << _T("    }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  n = max ? 90 / max : 1;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  nFldsLn = n < ") << nStgs << _T(" ? n : ") << nStgs << _T(';') << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (i = 0; i < nTabs; i++) tabs[i] = 0;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (i = 0, rcd = iter(); rcd; i = 0, rcd = iter++) {") << nCrlf;
  decl.clear();
  for (fld = iter(); fld; fld = iter++) if (fld->type == StgFld) {
    s = _T("    maxLng(rcd->") + notCaped(fld->name) + _T(',');
    decl.add(s, _T("tabs[i]);   i = (i + 1) % nFldsLn"));
    }
  decl.output();
  notePad << _T("    }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  tab = 4;") << nCrlf;
  notePad << _T("  notePad << nClrTabs << nSetRTab(tab) << nSetTab(tab += 2);") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (i = 0; i < nTabs && tabs[i]; i++) {") << nCrlf;
  notePad << _T("    tab += tabs[i] + 2;   notePad << nSetTab(tab);") << nCrlf;
  notePad << _T("    }") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


