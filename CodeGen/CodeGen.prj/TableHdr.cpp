// Create Table Header File


#include "pch.h"
#include "TableHdr.h"
#include "Capitalize.h"
#include "Declarations.h"
#include "LinSrch.h"
#include "ModNames.h"
#include "NotePad.h"


void TableHdr::create() {

  notePad.clear();

  notePad << _T("// ") << modNames.accTbl << _T(" Table") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("#pragma once") << nCrlf;
  notePad << _T("#include \"") << modNames.setCls << _T(".h\"") << nCrlf;
  notePad << _T("#include \"ExpandableP.h\"") << nCrlf;
  notePad << _T("#include \"IterT.h\"") << nCrlf;
  notePad << nCrlf << nCrlf;

  record();    notePad << nCrlf << nCrlf;
  iterator();  notePad << nCrlf << nCrlf;
  table();     notePad << nCrlf << nCrlf;

  notePad << _T("extern ") << modNames.tblCls << _T(' ') << modNames.tblObj << _T(';') << nCrlf;
  notePad << nCrlf;
  }



void TableHdr::record() {
FldsIter     iter(fields);
Field*       fld;
int          i;
Declarations decl;
String       typName;
String       s;

  notePad << _T("class ") << modNames.rcdCls << _T(" {") << nCrlf;
  notePad << _T("int   id;") << nCrlf;
  notePad << _T("bool  dirty;") << nCrlf;
  notePad << _T("bool  remove;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("public:") << nCrlf;
  notePad << nCrlf;

  for (i = 0, fld = iter(); fld; i++, fld = iter++) {

    if (!i) continue;

    switch (fld->type) {
      case IdxFld     :
      case IntFld     : typName = _T("int");    break;
      case StgFld     :
      case LongStgFld : typName = _T("String"); break;
      case BoolFld    : typName = _T("BOOL");   break;
      default         : typName = _T("int");    break;
      }

    decl.add(typName, notCaped(fld->name));
    }

  decl.output();
  notePad << nCrlf;

  notePad << _T("  ") << modNames.rcdCls << _T("();") << nCrlf;
  notePad << _T("  ") << modNames.rcdCls << _T('(') << modNames.rcdCls << _T("& r) ");
  notePad << _T("{copy(r);}") << nCrlf;
  notePad << _T(" ~") << modNames.rcdCls << _T("() { }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void clear();") << nCrlf << nCrlf;

  notePad << _T("  void load(") << modNames.setCls << _T("* set);") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  int getId() {return id;}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void setDirty()  {dirty = true;}") << nCrlf;
  notePad << _T("  void setRemove() {dirty = true; remove = true;}") << nCrlf;
  notePad << _T("  bool isRemoved() {return remove;}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void store(") << modNames.setCls << _T("& set);") << nCrlf;
  notePad << _T("  void add(  ") << modNames.setCls << _T("& set);") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void display();") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << modNames.rcdCls << _T("& operator= (") << modNames.rcdCls << _T("& r) ");
  notePad << _T("{copy(r); return *this;}") << nCrlf << nCrlf;

  notePad << _T("  // Needed for Insertion Sort of Primary Key") << nCrlf;
  notePad << _T("  bool operator== (") << modNames.rcdCls << _T("& r) {return id == r.id;}");
  notePad << nCrlf;
  notePad << _T("  bool operator>= (") << modNames.rcdCls << _T("& r) {return id >= r.id;}");
  notePad << nCrlf << nCrlf;

  notePad << _T("  // Needed for Binary Search of Primary Key") << nCrlf;
  notePad << _T("  bool operator== (long id) {return this->id == id;}") << nCrlf;
  notePad << _T("  bool operator<  (long id) {return this->id <  id;}") << nCrlf;
  notePad << _T("  bool operator>  (long id) {return this->id >  id;}") << nCrlf;
  notePad << nCrlf;

  linSrch.addRcdHdrFn();   notePad << nCrlf;

  notePad << _T("private:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void copy(") << modNames.setCls << _T("& set);") << nCrlf;
  notePad << _T("  void copy(") << modNames.rcdCls << _T("& r);")   << nCrlf;
  notePad << nCrlf;

  notePad << _T("  friend class ") << modNames.tblCls << _T(';') << nCrlf;
  notePad << _T("  };") << nCrlf;
  }


void TableHdr::iterator() {

  notePad << _T("// Record Pointer Declaration, see ExpandableP.h for details") << nCrlf;
  notePad << _T("typedef DatumPtrT<") << modNames.rcdCls << _T(", int> ");
  notePad << modNames.rcdPCls << _T(';') << nCrlf;
  notePad << nCrlf;

  notePad << _T("// Iterator Declaration, see IterT.h for details") << nCrlf;
  notePad << _T("class ") << modNames.tblCls << _T(';') << nCrlf;
  notePad << _T("typedef IterT<") << modNames.tblCls << _T(", ") << modNames.rcdCls;
  notePad << _T("> ") << modNames.tblIter << _T(';') << nCrlf;
  }


void TableHdr::table() {
Declarations decl;

  notePad << _T("class ") << modNames.tblCls << _T(" {") << nCrlf;
  notePad << nCrlf;

  notePad << _T("ExpandableP<") << modNames.rcdCls << _T(", int, ") << modNames.rcdPCls;
  notePad << _T(", 2> data;") << nCrlf;
  notePad << nCrlf;

  decl.add(_T("int"), _T("maxID"));
  decl.add(modNames.setCls, modNames.setObj);
  decl.output();
  notePad << nCrlf;

  notePad << _T("public:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("String name;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << modNames.tblCls << _T("() : maxID(0) { }") << nCrlf;
  notePad << _T(" ~") << modNames.tblCls << _T("() {clear();}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void clear() {data.clear();}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  bool load(TCchar* path);      // load database table into memory") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << modNames.rcdCls << _T("* add(") << modNames.rcdCls;
  notePad << _T("& rcd);     // Add a new record to table and database") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  bool store(TCchar* path);     // Store/Del entities marked") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << modNames.rcdCls << _T("* find(int id) ");
  notePad << _T("{return id ? data.bSearch(id) : 0;}") << nCrlf;

  linSrch.addTblHdrFn();   notePad << nCrlf;

  notePad << _T("  virtual void display() { }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("private:") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  bool open(TCchar* path) {return ") << modNames.setObj << _T(".open(path);}");
  notePad << nCrlf;
  notePad << _T("  void close() {") << modNames.setObj << _T(".close();}") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  void setTabs();") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  // returns either a pointer to data (or datum) at index i in array or zero");
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ") << modNames.rcdCls;
  notePad << _T("* datum(int i) {return 0 <= i && i < nData() ? data[i]"
                " : 0;}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  int   nData()      {return data.end();}   ");
  notePad << _T("// returns number of data items in array") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  friend typename ") << modNames.tblIter << _T(';') << nCrlf;
  notePad << _T("  };") << nCrlf;
  }


