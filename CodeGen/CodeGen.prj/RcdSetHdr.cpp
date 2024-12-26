// RcdSetHdr RcdSetHdr Creation


#include "pch.h"
#include "RcdSetHdr.h"
#include "Capitalize.h"
#include "Declarations.h"
#include "ModNames.h"
#include "NotePad.h"


enum {PageWidth = 106};


void RcdSetHdr::create() {
  notePad.clear();

  notePad << _T("// ") << modNames.setCls << _T(" Record") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"AccRcdSet.h\"") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  record();   notePad << nCrlf << nCrlf;
  iterator();
  }


void RcdSetHdr::record() {
FldsIter     iter(fields);
Field*       fld;
Declarations decls;
int          i;

  notePad << _T("class ") << modNames.setCls << _T(" : public AccRcdSet {") << nCrlf;
  notePad << _T("public:") << nCrlf;

  for (i = 0, fld = iter(); fld; i++, fld = iter++) decls.add(fld->type, notCaped(fld->name));
  decls.output();
  notePad << nCrlf;

  notePad << _T("  ") << modNames.setCls << _T("();") << nCrlf;
  notePad << _T(" ~") << modNames.setCls << _T("() {close();}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  bool open(TCchar* path);") << nCrlf;
  notePad << _T("  bool isOpen() {return opened;}") << nCrlf;
  notePad << _T("  void close() {AccRcdSet::close(); opened = false;}") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  bool edit();")   << nCrlf;
  notePad << _T("  bool addNew();") << nCrlf;
  notePad << _T("  bool update();") << nCrlf;
  notePad << _T("  bool remove();") << nCrlf;
  notePad << nCrlf;
  notePad << _T("private:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  virtual void DoFieldExchange(CFieldExchange* pFX);") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << modNames.setCls << _T("* moveFirst();") << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* moveNext();")  << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* moveLast();")  << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* movePrev();")  << nCrlf;

  notePad << _T("  friend class ") << modNames.setIterCls << _T(';') << nCrlf;
  notePad << _T("  };") << nCrlf;
  }




void RcdSetHdr::iterator() {

  notePad << _T("// Iterator Declaration, see IterT.h for details") << nCrlf;
  notePad << nCrlf;

  notePad << _T("class ") << modNames.setIterCls << _T(" {") << nCrlf;
  notePad << nCrlf;
  notePad << modNames.setCls << _T("& rcd;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("public:") << nCrlf;
  notePad << nCrlf;
  notePad << _T("enum Dir {Fwd, Rev};") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setIterCls << _T('(') << modNames.setCls;
  notePad << _T("& record) : rcd(record) { }");
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* find(int id);") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setCls;
  notePad << _T("* operator() (Dir dir = Fwd) ");
  notePad << _T("{return dir == Fwd ? rcd.moveFirst() : rcd.moveLast();}");
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* operator++ (int)           ");
  notePad << _T("{return rcd.moveNext();}");
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* operator-- (int)           ");
  notePad << _T("{return rcd.movePrev();}");
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("private:") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setIterCls << _T("() : rcd(*(") << modNames.setCls;
  notePad << _T("*)0) { }");
  notePad << nCrlf;
  notePad << _T("  };") << nCrlf;
  }


