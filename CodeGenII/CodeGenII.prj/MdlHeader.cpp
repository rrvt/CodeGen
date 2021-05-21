// MdlHeader Header Creation


#include "stdafx.h"
#include "MdlHeader.h"
#include "Declarations.h"
#include "NotePad.h"
#include "Utilities.h"



void MdlHeader::create() {
  daoTbl     = module.daoTbl;
  primaryKey = module.primaryKey;
  noFields   = module.noFields;
  indexName  = module.indexName;
  indexType  = module.indexType;

  notePad.clear();

  notePad << _T("// ") << namePfx << _T("Table") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"DBtables.h\"") << nCrlf;
  notePad << _T("#include \"DAOfields.h\"") << nCrlf;
  notePad << _T("#include \"ExpandableP.h\"") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  record();   notePad << nCrlf << nCrlf;
  iterator(); notePad << nCrlf << nCrlf;
  table();    notePad << nCrlf << nCrlf;

  notePad << _T("  extern ") << tblName << _T(" ") << tblObj << _T(";") << nCrlf;
  notePad << nCrlf;
  }


void MdlHeader::record() {
FldListIter  iter(fieldList);
FieldDsc*    fld;
Declarations decls;
int          i;

  notePad << _T("class ") << rcdName << _T(" : public DBrcd {") << nCrlf;
  notePad << _T("public:") << nCrlf;

  for (i = 0, fld = iter(); fld; i++, fld = iter++) {
    if (i) decls.add(fld->type, fld->name);
    }
  decls.output();
  notePad << nCrlf;

  constructor();

  notePad << _T(" ~") << rcdName << _T("() { }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("          void load(FieldsP fields);") << nCrlf;
  notePad << _T("          void store(FieldsP fields);") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  virtual void display();") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  // Needed for Insertion Sort of Primary Key") << nCrlf;
  rcdComparison(_T("=="));
  rcdComparison(_T(">="));  notePad << nCrlf;

  notePad << _T("  // Needed for Binary Search of Primary Key") << nCrlf;
  binComparison(_T("=="));
  binComparison(_T("< "));
  binComparison(_T("> "));
  notePad << nCrlf;

  linComparison();
  notePad << _T("  };") << nCrlf;
  }


void MdlHeader::constructor() {
FldListIter           iter(fieldList);
FieldDsc*             fld;
Expandable<String, 2> buf;

String                s;
int                   initTab;
String                t;
int                   i;
int                   n;

  s =  _T("  ") + rcdName + _T("() : ");   initTab = s.length();   s += _T("DBrcd()");

  for (fld = iter(); fld; fld = iter++) {
    if (fld->type == _T("String") || iter.index() == 0) continue;

    t = fld->name;
    if (fld->type == _T("long")) t += _T("(0)");
    if (fld->type == _T("bool")) t += _T("(false)");

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

void MdlHeader::rcdComparison(TCchar* op) {

  notePad << _T("  bool operator") << op << _T(" (") << rcdName << _T("& r) {return ");
  notePad << indexName << _T(" ") << op << _T(" r.") << indexName << _T(";}") << nCrlf;
  }


/*
  // Needed for Binary Search of Primary Key
  bool operator== (long id) {return ID == id;}
  bool operator<  (long id) {return ID <  id;}
  bool operator>  (long id) {return ID >  id;}
*/

void MdlHeader::binComparison(TCchar* op) {
  notePad << _T("  bool operator") << op << _T(" (") << indexType << _T(" ") << indexName;
  notePad << _T(") {return this->") << indexName << _T(" ") << op << _T(" ") << indexName;
  notePad << _T(";}") << nCrlf;
  }


void MdlHeader::linComparison() {
String argList;
int    noArgs;
String prfx;
String sfx;
String s;

  notePad << _T("  // Needed for Linear Search with one or more arguments") << nCrlf;

  argList = module.getArgList(noArgs);
  prfx = _T("  bool ");
  if (noArgs == 1) {prfx += _T("operator== (");}
  else             {prfx += _T("isInRcd(");}
  prfx += argList + _T(")");

  sfx = _T("{return ") + module.getArgsComp() + _T(";}");

  if (prfx.length() + sfx.length() < 99) s = prfx + _T(" ") + sfx;
  else {notePad << prfx << nCrlf; s = rightAdj(sfx, PageWidth);}
  notePad << s << nCrlf;
  }


void MdlHeader::iterator() {

  notePad << _T("// Iterator Declaration, see IterT.h for details") << nCrlf;

  notePad << _T("class ") << tblName << _T(";") << nCrlf;
  notePad << _T("typedef IterT<") << tblName << _T(", ") << rcdName << _T("> ");
  notePad << iterName << _T(";") << nCrlf;
  notePad << nCrlf;

  notePad << _T("// Record Pointer Declaration, see ExpandableP.h for details") << nCrlf;
  notePad << _T("typedef RcdPtrT<") << rcdName << _T("> ") << ptrName << _T(";") << nCrlf;
  }


void MdlHeader::table() {
FldListIter iter(fieldList);
FieldDsc*   fld;
int         noArgs;
int         i;
String      retRcdPtr = rcdName + _T('*');
int         lng = retRcdPtr.length() + 2;
int         retTab = 14;    if (lng > retTab) retTab = lng;

  notePad << _T("class ") << tblName <<  _T(" : public DBtable {") <<nCrlf;
  notePad << nCrlf;

  notePad << _T("ExpandableP<") << rcdName <<  _T(", ") << ptrName << _T(", 2> data;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("public:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << tblName << _T("() : DBtable(_T(\"") << namePfx << _T("\")) ");
  notePad << _T("{dbTables = this;}");
  notePad << nCrlf;

  notePad << _T(" ~") << tblName << _T("() { }") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(_T("virtual bool"), retTab);
  notePad << _T(" operator== (TCchar* name) {return this->name == name;}") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(_T("void"), retTab) << _T(" clear() {data.clear();}") << nCrlf;
  notePad << rightAdj(_T("bool"), retTab) << _T(" load(DAOtable* daoTable);");
  notePad << _T("  // load database table into memory, does not use addNewRcd.") << nCrlf;
  notePad << nCrlf;

  notePad << rightAdj(retRcdPtr, retTab) << _T(" add(") << rcdName;
  notePad << _T("& rcd);     // Add a new record to table and database") << nCrlf;

  if (noFields == 3) {
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

  notePad << rightAdj(retRcdPtr, retTab) << _T(" find(") << indexType << _T(' ') << indexName;
  notePad << _T(") {return data.bSearch(") << indexName << _T(");}") << nCrlf;

  notePad << rightAdj(retRcdPtr, retTab) << _T(" find(");
  notePad << module.getArgList(noArgs) << _T(")");
  if (noArgs == 1) notePad << _T(" {return data.find(") << module.getArgs() << _T(");}") << nCrlf;
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

  notePad << _T("  ") << rcdName << _T("* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}");
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("  int   nData()      {return data.end();}                       ");
  notePad << _T("// returns number of data items in array") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  friend typename ") << iterName << _T(";") << nCrlf;
  notePad << _T("  };") << nCrlf;
  }

