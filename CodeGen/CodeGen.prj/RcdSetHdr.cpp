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
  notePad << _T("  void close() {opened = false;}") << nCrlf;
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
  notePad << _T("  ") << modNames.setIterCls << _T('(') << modNames.setCls << _T("& record) : rcd(record) { }");
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* find(int id);") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setCls;
  notePad << _T("* operator() (Dir dir = Fwd) {return dir == Fwd ? rcd.moveFirst() : rcd.moveLast();}");
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* operator++ (int)           {return rcd.moveNext();}");
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setCls << _T("* operator-- (int)           {return rcd.movePrev();}");
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("private:") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  ") << modNames.setIterCls << _T("() : rcd(*(") << modNames.setCls << _T("*)0) { }");
  notePad << nCrlf;
  notePad << _T("  };") << nCrlf;
  }


#if 0
void RcdSetHdr::constructor() {
FldsIter              iter(fields);
Field*                fld;
Expandable<String, 2> buf;

String                s;
int                   initTab;
String                t;
int                   i;
int                   n;

  s =  _T("  ") + modNames.setCls + _T("() : ");   initTab = s.length();   s += _T("DBrcd()");

  for (fld = iter(); fld; fld = iter++) {
    if (fld->type == StgFld) continue;

    t = fld->name;
    if (fld->type == IntFld)  t += _T("(0)");
    if (fld->type == BoolFld) t += _T("(false)");

    buf += t;
    }

  n = buf.end();

  for (i = 0; i < n; i++) {
    if (s.length() + buf[i].length() + 5 < PageWidth) s += _T(", ") + buf[i];
    else {notePad << s << _T(",") << nCrlf;     s = tabStg(initTab) + buf[i];}
    }

  notePad << s <<  _T(" { }") << nCrlf;
  }


/*
  // Needed for Insertion Sort of Primary Key
  bool operator== (EntityRcd& r) {return ID == r.ID;}
  bool operator>= (EntityRcd& r) {return ID >= r.ID;}
*/

void RcdSetHdr::rcdComparison(TCchar* op) {

  notePad << _T("  bool operator") << op << _T(" (") << modNames.setCls << _T("& r) {return ");
  notePad << modNames.indexName << _T(" ") << op << _T(" r.") << modNames.indexName << _T(";}") << nCrlf;
  }


/*
  // Needed for Binary Search of Primary Key
  bool operator== (long id) {return ID == id;}
  bool operator<  (long id) {return ID <  id;}
  bool operator>  (long id) {return ID >  id;}
*/

void RcdSetHdr::binComparison(TCchar* op) {
  notePad << _T("  bool operator") << op << _T(" (") << modNames.indexType;
  notePad << _T(" ") << modNames.indexName;
  notePad << _T(") {return this->") << modNames.indexName << _T(" ") << op;
  notePad << _T(" ") << modNames.indexName;
  notePad << _T(";}") << nCrlf;
  }


void RcdSetHdr::linComparison() {
String argList;
int    noArgs;
String prfx;
String sfx;
String s;

  notePad << _T("  // Needed for Linear Search with one or more arguments") << nCrlf;

  argList = fields.getArgList(noArgs);
  prfx = _T("  bool ");
  if (noArgs == 1) {prfx += _T("operator== (");}
  else             {prfx += _T("isInRcd(");}
  prfx += argList + _T(")");

  sfx = _T("{return ") + fields.getArgsComp() + _T(";}");

  if (prfx.length() + sfx.length() < 99) s = prfx + _T(" ") + sfx;
  else {notePad << prfx << nCrlf; s = rightAdj(sfx, PageWidth);}
  notePad << s << nCrlf;
  }


void RcdSetHdr::table() {
FldsIter iter(fields);
Field*   fld;
int      noArgs;
int      i;
String   retRcdPtr = modNames.setCls + _T('*');
int      lng = retRcdPtr.length() + 2;
int      retTab = 14;    if (lng > retTab) retTab = lng;

  notePad << _T("class ") << modNames.tblCls <<  _T(" : public DBtable {") <<nCrlf;
  notePad << nCrlf;

  notePad << _T("ExpandableP<") << modNames.setCls <<  _T(", ") << modNames.ptrName << _T(", 2> data;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("public:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << modNames.tblCls << _T("() : DBtable(_T(\"") << modNames.accTbl << _T("\")) ");
  notePad << _T("{dbTables = this;}");
  notePad << nCrlf;

  notePad << _T(" ~") << modNames.tblCls << _T("() { }") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(_T("virtual bool"), retTab);
  notePad << _T(" operator== (TCchar* name) {return this->name == name;}") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(_T("void"), retTab) << _T(" clear() {data.clear();}") << nCrlf;
  notePad << rightAdj(_T("bool"), retTab) << _T(" load(DAOtable* daoTable);");
  notePad << _T("  // load database table into memory, does not use addNewRcd.") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(retRcdPtr, retTab) << _T(" add(") << modNames.setCls;
  notePad << _T("& rcd);     // Add a new record to table and database") << nCrlf;

  if (modNames.noFields == 3) {
    notePad << rightAdj(retRcdPtr, retTab) << _T(" add(");

    for (i = 0, fld = iter(); fld; i++, fld = iter++) {
      if (!i) continue;
      if (i > 1) notePad << _T(", ");
      notePad << fld->type << _T(' ') << fld->name;
      }

    notePad << _T(");   // Add a new record to table and database") << nCrlf;
    notePad << nCrlf;
    }

  notePad << rightAdj(_T("void"), retTab) << _T(" store();") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(retRcdPtr, retTab) << _T(" find(") << modNames.indexType;
  notePad << _T(' ') << modNames.indexName;
  notePad << _T(") {return data.bSearch(") << modNames.indexName << _T(");}") << nCrlf;

  notePad << rightAdj(retRcdPtr, retTab) << _T(" find(");
  notePad << fields.getArgList(noArgs) << _T(")");
  if (noArgs == 1) notePad << _T(" {return data.find(") << fields.getArgs() << _T(");}") << nCrlf;
  else             notePad << _T(";") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(_T("virtual void"), retTab) << _T(" display();") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(_T("virtual void"), retTab) << _T(" setTabs();") << nCrlf;
//  notePad << nCrlf;

  notePad << _T("private:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("// returns either a pointer to data (or datum) at index i in array or zero") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << modNames.setCls << _T("* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}");
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("  int   nData()      {return data.end();}                       ");
  notePad << _T("// returns number of data items in array") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  friend typename ") << modNames.iter << _T(";") << nCrlf;
  notePad << _T("  };") << nCrlf;
  }
#endif
#if 0
//  notePad << _T("  virtual void display();") << nCrlf;
//  notePad << nCrlf;

  notePad << _T("  // Needed for Insertion Sort of Primary Key") << nCrlf;
  rcdComparison(_T("=="));
  rcdComparison(_T(">="));  notePad << nCrlf;

  notePad << _T("  // Needed for Binary Search of Primary Key") << nCrlf;
  binComparison(_T("=="));
  binComparison(_T("< "));
  binComparison(_T("> "));
  notePad << nCrlf;

  linComparison(); notePad << nCrlf;
#endif
//  table();    notePad << nCrlf << nCrlf;
#if 1
#else
  daoTbl     = module.daoTbl;
  primaryKey = module.primaryKey;
  noFields   = module.noFields;
  indexName  = module.indexName;
  indexType  = module.indexType;
#endif

