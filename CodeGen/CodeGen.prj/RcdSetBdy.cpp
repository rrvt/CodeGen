// Module Body Creation


#include "pch.h"
#include "RcdSetBdy.h"
#include "Capitalize.h"
#include "Declarations.h"
#include "ModNames.h"
#include "NotePad.h"


void RcdSetBdy::create() {

  notePad.clear();

  notePad << _T("// ") << modNames.setCls << _T(" Record") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;
  notePad << _T("#include \"pch.h\"") << nCrlf;
  notePad << _T("#include \"") << modNames.setCls << _T(".h\"") << nCrlf;
  notePad << _T("#include \"AccessDB.h\"") << nCrlf;
  notePad << nCrlf;
  notePad << nCrlf;

  constructor(); notePad << nCrlf << nCrlf;
  open();        notePad << nCrlf << nCrlf;
  find();        notePad << nCrlf << nCrlf;
  edit();        notePad << nCrlf << nCrlf;
  addNew();      notePad << nCrlf << nCrlf;
  update();      notePad << nCrlf << nCrlf;
  remove();      notePad << nCrlf << nCrlf;
  fieldExch();   notePad << nCrlf << nCrlf;
  moveFirst();   notePad << nCrlf << nCrlf;
  moveNext();    notePad << nCrlf << nCrlf;
  moveLast();    notePad << nCrlf << nCrlf;
  movePrev();
  }


void RcdSetBdy::constructor() {
FldsIter iter(fields);
Field*   fld;
int      i;
int      n = 3;

  notePad << modNames.setCls << _T("::") << modNames.setCls << _T("() : AccRcdSet(accessDB.db())");

  for (i = 0, fld = iter(); fld; i++, fld = iter++) {

    if (i < n) notePad << _T(", ");
    else {notePad << _T(",") << nCrlf << _T("          ");   n = 5;}

    switch (fld->type) {
      case IdxFld     :
      case IntFld     : notePad << notCaped(fld->name) << _T("(0)");     break;
      case StgFld     :
      case LongStgFld : notePad << notCaped(fld->name) << _T("()");      break;
      case BoolFld    : notePad << notCaped(fld->name) << _T("(false)"); break;
      default         : notePad << notCaped(fld->name) << _T("()");      break;
      }
    }

  notePad << _T(" { }")<< nCrlf;
  }


void RcdSetBdy::open() {

  notePad << _T("bool ") << modNames.setCls << _T("::open(TCchar* path) {") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  opened = false;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  if (!accessDB.isOpen() && !accessDB.open(path)) return false;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  SetState(CRecordset::dynaset, NULL, CRecordset::none);");
  notePad << _T("          // Cache state info and allocate hstmt") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  if (!AllocHstmt()) return false;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  OnSetOptions(m_hstmt);   AllocStatusArrays();");
  notePad << _T("   m_nFields = ") << modNames.noFields << _T(';') << nCrlf;
  notePad << nCrlf;

  notePad << _T("  try {if (!Open(CRecordset::dynaset, _T(\"") << modNames.accTbl;
  notePad << _T("\"), CRecordset::none)) return false;}") << nCrlf;
  notePad << _T("  catch(...) {") << nCrlf;
  notePad << _T("    try {if (!Open(CRecordset::snapshot, _T(\"") << modNames.accTbl;
  notePad << _T("\"), CRecordset::none)) return false;}") << nCrlf;
  notePad << _T("    catch(...) {close(); return false;}") << nCrlf;
  notePad << _T("    }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  return opened = true;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }



void RcdSetBdy::find() {
  notePad << modNames.setCls << _T("* ") << modNames.setIterCls << _T("::find(int id) {") << nCrlf;
  notePad << modNames.setCls << _T("* set = &rcd;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for ( ; set && set->") << modNames.index;
  notePad << _T(" <= id; set = (*this)++) if (set->") << modNames.index;
  notePad << _T(" == id) return set;") << nCrlf;

  notePad << _T("  for ( ; set && set->") << modNames.index;
  notePad << _T(" >= id; set = (*this)--) if (set->") << modNames.index;
  notePad << _T(" == id) return set;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::edit() {
  notePad << _T("bool ") << modNames.setCls << _T("::edit()") << nCrlf;
  notePad << _T("  {if (!opened) return false;   ");
  notePad << _T("try {Edit(); return true;} catch(...) {return false;}}") << nCrlf;
  }


void RcdSetBdy::addNew() {
  notePad << _T("bool ") << modNames.setCls << _T("::addNew()") << nCrlf;
  notePad << _T("  {if (!opened) return false;   ");
  notePad << _T("try {AddNew(); return true;} catch(...) {return false;}}") << nCrlf;
  }


void RcdSetBdy::update() {
  notePad << _T("bool ") << modNames.setCls << _T("::update()") << nCrlf;
  notePad << _T("  {if (!opened) return false;   ");
  notePad << _T("try {Update(); movePrev(); return true;} catch(...) {return false;}}") << nCrlf;
  }


void RcdSetBdy::remove() {
  notePad << _T("bool ") << modNames.setCls << _T("::remove()") << nCrlf;
  notePad << _T("  {if (!opened) return false;   ");
  notePad << _T("try {Delete(); movePrev(); return true;} catch(...) {return false;}}") << nCrlf;
  }


void RcdSetBdy::fieldExch() {
FldsIter     iter(fields);
Field*       fld;
String       rfx;
String       arg;
Declarations decl;

  notePad << _T("void ") << modNames.setCls << _T("::DoFieldExchange(CFieldExchange* pFX) {") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  pFX->SetFieldType(CFieldExchange::outputColumn);") << nCrlf;
  notePad << nCrlf;

  for (fld = iter(); fld; fld = iter++) {
    switch (fld->type) {
      case IdxFld     :
      case IntFld     : rfx = _T("  RFX_Int( "); break;
      case StgFld     :
      case LongStgFld : rfx = _T("  RFX_Text("); break;
      case BoolFld    : rfx = _T("  RFX_Bool("); break;
      default         : rfx = _T("  RFX_Int( "); break;
      }

    rfx += _T("pFX, _T(\"") + fld->name + _T("\"),");
    arg = notCaped(fld->name);
    if (fld->type == LongStgFld) arg += _T(", 1024");
    arg += _T(")");
    decl.add(rfx, arg);

//    notePad << rfx << _T("pFX, _T(\"") << fld->name << _T("\"), ") << fld->name << _T(");") << nCrlf;
    }

  decl.output();
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::moveFirst() {
  notePad << modNames.setCls << _T("* ") << modNames.setCls << _T("::moveFirst() {") << nCrlf;
  notePad << _T("  if (!opened || (IsBOF() && IsEOF())) return 0;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  MoveFirst();  return this;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::moveNext() {
  notePad << modNames.setCls << _T("* ") << modNames.setCls << _T("::moveNext() {") << nCrlf;
  notePad << _T("  if (!opened || IsEOF()) return 0;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  try {Move(1);} catch (...) {try {Move(1);} catch (...) {return 0;}}") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  return IsEOF() ? 0 : this;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::moveLast() {
  notePad << modNames.setCls << _T("* ") << modNames.setCls << _T("::moveLast() {") << nCrlf;
  notePad << _T("  if (!opened || (IsBOF() && IsEOF())) return 0;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  MoveLast();   return this;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::movePrev() {
  notePad << modNames.setCls << _T("* ") << modNames.setCls << _T("::movePrev() {") << nCrlf;
  notePad << _T("  if (!opened || IsBOF()) return 0;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  try {Move(-1);} catch (...) {try {Move(-1);} catch (...) {return 0;}}") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  return IsBOF() ? 0 : this;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }





#if 0
void RcdSetBdy::load() {

  notePad << _T("bool ") << tblName << _T("::load(DAOtable* daoTable) {") << nCrlf;

  notePad << _T("DAOrcdsIter iter(daoTable);") << nCrlf;
  notePad << _T("FieldsP     fields;") << nCrlf;
  notePad << _T("int         count;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (count = 0, fields = iter(DAOdenyWrite); fields; count++, fields = iter++) {");
  notePad << nCrlf;
  notePad << _T("    ") << rcdName << _T(" rcd;   rcd.load(fields);   data = rcd;") << nCrlf;
  notePad << _T("    }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  notePad << count << nCrlf; return true;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::rcdLoad() {
FldListIter iter(fieldList);
FieldDsc*   fld;
int         tabLng = fieldList.maxLength();

  notePad << _T("void ") << rcdName << _T("::load(FieldsP fields) {") << nCrlf;
  notePad << _T("DAOfldsIter iter(fields);") << nCrlf;
  notePad << _T("DAOfield*   dsc;") << nCrlf;
  notePad << _T("variant_t   v;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (dsc = iter(); dsc; dsc = iter++) {") << nCrlf;
  notePad << _T("    v = dsc->value();") << nCrlf;
  notePad << _T("    switch (iter.index()) {") << nCrlf;

  for (fld = iter(); fld; fld = iter++) {
    String ind = iter.index();
    notePad << _T("      case ") << rightAdj(ind, 2) << _T(": ") << addTab(fld->name, tabLng);
    notePad << _T(" = v; break;") << nCrlf;
    }
  notePad << _T("      default: throw _T(\"") << namePfx << _T(" Record Error\");") << nCrlf;
  notePad << _T("      }") << nCrlf;
  notePad << _T("    }") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::store() {
int    tab    = rcdName.length() + 2;   if (tab < 10) tab = 10;
String rcdPtr = rcdName + _T('*');
String s;
String primeIndex = primaryKey->name;

  if (iterName.length() + 1 > tab) tab = iterName.length() + 1;

  notePad << _T("void ") << tblName << _T("::store() {") << nCrlf;

  notePad << addTab(_T("DAOtable*"), tab) << _T("daoTbl = daoTablesX.bSearch(name);");
  notePad << _T("   if (!daoTbl) throw _T(\"Unable to locate ") << namePfx << _T(" Table\");") << nCrlf;
  notePad << addTab(_T("DAOrcds"), tab) << _T("daoRcds(daoTbl);") << nCrlf;
  notePad << addTab(_T("FieldsP"), tab) << _T("fieldsP;") << nCrlf;
  notePad << addTab(iterName,      tab) << _T("iter(*this);") << nCrlf;
  notePad << addTab(rcdPtr,        tab) << _T("rcd;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (rcd = iter(); rcd; rcd = iter++) {") << nCrlf;
  notePad << nCrlf;
  notePad << _T("    if (rcd->isDeleted() && daoRcds.findRecord(rcd->") << primeIndex << _T("))");
  notePad << nCrlf;
  notePad << rightAdj(_T("{daoRcds.delCurRcd();   iter.remove();   continue;}"), PageWidth);
  notePad << nCrlf;

  notePad << _T("    if (!rcd->isDirty()) continue;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("    fieldsP = daoRcds.findRecord(rcd->") << primeIndex << _T(");   ");
  notePad << _T("if (!fieldsP) continue;");
  notePad << _T("    // Add new records with addNewRcd") << nCrlf;
  notePad << nCrlf;

  notePad << _T("    daoRcds.edit();   rcd->store(fieldsP);   daoRcds.update();");
  notePad << _T("   rcd->clearMark();") << nCrlf;
  notePad << _T("    }") << nCrlf;

  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::addNewRcd() {
  notePad << rcdName << _T("* ") << tblName << _T("::add(");
  notePad << rcdName << _T("& rcd) {") << nCrlf;
  notePad << _T("DAOtable* daoTbl = daoTablesX.bSearch(name);   ");
  notePad << _T("if (!daoTbl) throw _T(\"Unable to locate ") << namePfx << _T(" Table\");") << nCrlf;
  notePad << _T("DAOrcds   daoRcds(daoTbl);") << nCrlf;
  notePad << _T("FieldsP   fieldsP;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  fieldsP = daoRcds.findRecord(rcd.") << primaryKey->name;
  notePad << _T(");   if (fieldsP) return 0;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  fieldsP = daoRcds.addNew();   rcd.store(fieldsP);  daoRcds.update();  ");
  notePad << _T("rcd.clearMark();") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  return data = rcd;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::addRef() {
FldListIter iter(fieldList);
FieldDsc*   fld;
int         i;

  notePad << rcdName << _T("* ") << tblName << _T("::add(");

  for (i = 0, fld = iter(); fld; i++, fld = iter++) {
    if (!i) continue;
    if (i > 1) notePad << _T(", ");
    notePad << fld->type << _T(' ') << fld->name;
    }

  notePad << _T(") {    // Add a new record to table and database") << nCrlf;

  notePad << rcdName << _T(" rcd;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  ");
  for (i = 0, fld = iter(); fld; i++, fld = iter++) {
    if (!i) continue;

    if (i > 1) notePad << _T("   ");

    notePad << _T("rcd.") << fld->name << _T(" = ") << fld->name << _T(";");
    }

  notePad << _T("   return add(rcd);") << nCrlf;

  notePad << _T("  }") << nCrlf;
  }



void RcdSetBdy::rcdStore() {
FldListIter iter(fieldList);
FieldDsc*   fld;
int         tabLng = fieldList.maxLength();
int         i;

  notePad << _T("void ") << rcdName << _T("::store(FieldsP fields) {") << nCrlf;
  notePad << _T("DAOfldsIter iter(fields);") << nCrlf;
  notePad << _T("DAOfield*   field;") << nCrlf;
  notePad << _T("variant_t   v;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (field = iter(); field; field = iter++) {") << nCrlf;
  notePad << _T("    switch (iter.index()) {") << nCrlf;

  for (fld = iter(); fld; fld = iter++) {
    String ind = i = iter.index();
    notePad << _T("      case ") << rightAdj(ind, 2) << _T(": ");
    if (i) notePad << _T("v  = ") << fld->name << _T("; break;");
    else   notePad << _T("id = field->value(); continue;");
    notePad << nCrlf;
    }
  notePad << _T("      default: throw _T(\"") << namePfx << _T(" Record Error\");") << nCrlf;
  notePad << _T("      }") << nCrlf;
  notePad << nCrlf;

  notePad << _T("    *field = v;") << nCrlf;
  notePad << _T("    }") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


bool RcdSetBdy::find() {
int          noArgs;
String       argList = module.getArgList(noArgs);
Declarations decl;
String       prfx;
String       sfx;

  if (noArgs == 1) return false;

  notePad << rcdName << _T("* ") << tblName << _T("::find(") << argList << _T(") {") << nCrlf;
  decl.add(iterName, _T("iter(*this)"));
  prfx = rcdName + _T('*');
  decl.add(prfx, _T("rcd"));
  decl.output();
  notePad << nCrlf;

  prfx = _T("  for (rcd = iter(); rcd; rcd = iter++)");
  sfx  = _T("if (rcd->isInRcd(") + module.getArgs() + _T(")) return rcd;");

  notePad << prfx;
  if (prfx.length() + sfx.length() + 1 <= PageWidth) notePad << _T(' ') << sfx;
  else                                               notePad << nCrlf << rightAdj(sfx, PageWidth);
  notePad << nCrlf;
  notePad << nCrlf;

  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf;   return true;
  }


/*
void MemberTbl::display() {
MbrIter    iter(*this);
MemberRcd* rcd;

  notePad << _T("Member Table") << nCrlf;

  notePad << nSetRTab(4) << nSetTab(6) << nSetTab(14);

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }
*/

void RcdSetBdy::display() {
Declarations decl;
String       p = rcdName + _T('*');

  notePad << _T("void ") << tblName << _T("::display() {") << nCrlf;

  decl.add(iterName, _T("iter(*this)"));
  decl.add(p,        _T("rcd"));
  decl.output();
  notePad << nCrlf;

  notePad << _T("  setTabs();") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  notePad << _T(\"") << namePfx << _T(" Table\") << nCrlf;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (rcd = iter(); rcd; rcd = iter++) rcd->display();") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }

/*
void EntityRcd::display() {notePad << nTab << id << nTab << firstName << _T(' ') << lastName << nCrlf;}
*/


void RcdSetBdy::dspRcd() {
FldListIter iter(fieldList);
FieldDsc*   fld;

  notePad << _T("void ") << rcdName << _T("::display() {") << nCrlf;

  notePad << _T("  notePad << nTab << ") << indexName  << _T(';') << nCrlf;

  for (fld = iter(); fld; fld = iter++) {
    if (fld->isSelected) notePad << _T("  notePad << nTab << ") << fld->name << _T(';') << nCrlf;
    }
  notePad << _T("  notePad << nCrlf;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }

/*
void EntityTbl::setTabs() {
EntIter    iter(*this);
EntityRcd* rcd;
int        tab0 = 0;
int        tab1 = 0;
int        tab2 = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->id,        tab0);
    maxLng(rcd->firstName, tab1);
    maxLng(rcd->lastName,  tab2);
    }

  tab1  += tab0 + 4;
  tab2  += tab1 + 2;

  notePad << nClrTabs << nSetRTab(tab0) << nSetTab(tab0 + 2) << nSetTab(tab1) << nSetTab(tab2);
  }
*/
void RcdSetBdy::setTabs() {
FldListIter  iter(fieldList);
FieldDsc*    fld;
Declarations decl;
String       p = rcdName + _T('*');
int          i;
int          j;
int          dx;
String       s;

  notePad << _T("void ") << tblName << _T("::setTabs() {") << nCrlf;

  decl.add(iterName, _T("iter(*this)"));
  decl.add(p,        _T("rcd"));

  for (i = 0, fld = iter(); fld; fld = iter++)
    if (fld->isSelected) {String s = _T("tab"); s += i;  decl.add(_T("int"), s, _T("0"));   i++;}

  decl.output();
  notePad << nCrlf;

  notePad << _T("  for (rcd = iter(); rcd; rcd = iter++) {") << nCrlf;
  notePad << _T("    maxLng(rcd->") << indexName << _T(", tab0);") << nCrlf;

  for (i = 1, fld = iter(), s.clear(); fld; fld = iter++) if (fld->isSelected) {
    if (!s.isEmpty()) notePad << s << nCrlf;
    s =  _T("    maxLng(rcd->") + fld->name + _T(", tab"); s += i; s += _T(");");
    i++;
    }

  notePad << _T("    }") << nCrlf;
  notePad << nCrlf;

  for (i = 0, fld = iter(), s.clear(); fld; fld = iter++) if (fld->isSelected) {
    if (!s.isEmpty()) notePad << s << nCrlf;

    j = i + 1;    dx = i == 0 ? 4 : 2;
    s = _T("  tab"); s += j; s += _T(" += tab"); s += i; s += _T(" + "); s += dx; s += _T(";");
    i++;
    }
  if (i > 1) notePad << nCrlf;

  tabOut();

  notePad << _T("  }") << nCrlf;
  }


/*
  notePad << nClrTabs << nSetRTab(tab0) << nSetTab(tab0 + 2) << nSetTab(tab1) << nSetTab(tab2);
*/

void RcdSetBdy::tabOut() {
FldListIter           iter(fieldList);
FieldDsc*             fld;
String                s;
int                   i;
String                set;

  notePad << _T("  notePad << nClrTabs;") << nCrlf;

  for (i = 0, fld = iter(); fld; fld = iter++) if (fld->isSelected) {

    set = i ? _T("nSetTab") : _T("nSetRTab");

    notePad << _T("  notePad << ") << set << _T("(tab") << i;

    if (i == 0) notePad << _T(") << nSetTab(tab0 + 2");

    notePad << _T(");") << nCrlf;   i++;
    }
  }
/*
notePad << nClrTabs << nSetRTab(tab0) << nSetTab(tab0 + 2) << nSetTab(tab1) << nSetTab(tab2);


notePad << _T("") << nCrlf;
notePad << addTab(_T(""), tab) << _T("") << nCrlf;
notePad << _T("") <<  << _T("") << nCrlf;
notePad << _T("") <<  << _T("") <<  << _T("") << nCrlf;
*/
#endif


#if 0
  load();      notePad << nCrlf << nCrlf;
  rcdLoad();   notePad << nCrlf << nCrlf;
  store();     notePad << nCrlf << nCrlf;
  addNewRcd(); notePad << nCrlf << nCrlf;
  if (noFields == 3) {addRef();  notePad << nCrlf << nCrlf;}
  rcdStore();  notePad << nCrlf << nCrlf;
  if (find())  notePad << nCrlf << nCrlf;
  display();   notePad << nCrlf << nCrlf;
  dspRcd();    notePad << nCrlf << nCrlf;
  setTabs();
               notePad << nCrlf;
#endif
#if 0
  notePad << _T("  bool edit()   ");
  notePad << _T("{try {Edit(); return true;}               catch(...) {return false;}}") << nCrlf;
  notePad << _T("  bool update() ");
  notePad << _T("{try {return Update();}                   catch(...) {return false;}}") << nCrlf;
  notePad << _T("  bool del()    ");
  notePad << _T("{try {Delete(); movePrev(); return true;} catch(...) {return false;}}") << nCrlf;
#endif
//#include "Fields.h"



#if 0
  notePad << _T("  AllocRowset();          // Allocate memory and cache info") << nCrlf;
  notePad << nCrlf;
#endif


