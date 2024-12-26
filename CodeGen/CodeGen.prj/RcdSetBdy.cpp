// Module Body Creation


#include "pch.h"
#include "RcdSetBdy.h"
#include "Capitalize.h"
#include "Declarations.h"
#include "ModNames.h"
#include "NotePad.h"
#include "Utilities.h"


static const int PaperWidth = 99;


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
String   s;

  data.clear();
#if 1

  for (fld = iter(); fld; fld = iter++) {

    switch (fld->type) {
      case IdxFld     :
      case IntFld     : s = notCaped(fld->name) + _T("(0)");     break;
      case StgFld     :
      case LongStgFld : s = notCaped(fld->name) + _T("()");      break;
      case BoolFld    : s = notCaped(fld->name) + _T("(false)"); break;
      default         : s = notCaped(fld->name) + _T("()");      break;
      }

    data += s;
    }

#else
int      i;
int      n = 3;
  notePad << modNames.setCls << _T("::") << modNames.setCls << _T("() : AccRcdSet(accessDB.db())");

  for (i = 0, fld = iter(); fld; i++, fld = iter++) {

    if (i < n) notePad << _T(", ");
    else {notePad << _T(",") << nCrlf << _T("          ");   n = 5;}

    switch (fld->type) {
      case IdxFld     :
      case IntFld     : s = notCaped(fld->name) + _T("(0)");     break;
      case StgFld     :
      case LongStgFld : s = notCaped(fld->name) + _T("()");      break;
      case BoolFld    : s = notCaped(fld->name) + _T("(false)"); break;
      default         : s = notCaped(fld->name) + _T("()");      break;
      }

    notePad << s;   data += s;
    }

  notePad << _T(" { }")<< nCrlf;
#endif

  newCnstrctr();
  }


void RcdSetBdy::newCnstrctr() {
CnstrIter iter(*this);
String*   s;
int       tab0 = modNames.setCls.length() * 2 + 7;
int       i;
int       n = nInitWide(PaperWidth - tab0);
int       lastLng = 0;
int       t;

  notePad << modNames.setCls << _T("::") << modNames.setCls << _T("() : AccRcdSet(accessDB.db())");

  for (i = n, s = iter(); s; i++, s = iter++) {
    notePad << _T(',');

    if (i >= n) {notePad << nCrlf << tabStg(tab0);   i = 0;}
    else {
      t = max[i-1] - lastLng + 1;

      notePad << tabStg(t);
      }

    notePad << *s;    lastLng = s->length();
    }

  notePad << _T(" { }")<< nCrlf;
  }


int RcdSetBdy::nInitWide(int maxLng) {
int i;

  for (i = 6; i >= 0; i--) if (initWideTrial(i, maxLng)) return i;
  return 1;
  }


bool RcdSetBdy::initWideTrial(int n, int maxLng) {
CnstrIter iter(*this);
String*   s;
int       i;
int       lng;
int       j;
int       t;

  for (i = 0; i < noElements(max); i++) max[i] = 0;

  for (i = 0, s = iter(); s; i++, s = iter++) {
    lng = s->length();

    if (i >= n) i = 0;

    if (lng > max[i]) max[i] = lng;
    }

  for (t = 0, j = 0; j < n; j++) t += max[j] + 2;    return t+2 <= maxLng;
  }



void RcdSetBdy::open() {

  notePad << _T("bool ") << modNames.setCls << _T("::open(TCchar* path) {") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  if (opened) close();") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  if (!accessDB.isOpen() && !accessDB.open(path)) return false;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  SetState(CRecordset::dynaset, NULL, CRecordset::none);");
  notePad << _T("    // Cache state info and allocate hstmt") << nCrlf;
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
int  n;
bool flag = true;

  notePad << modNames.setCls << _T("* ") << modNames.setIterCls << _T("::find(int id) {") << nCrlf;
  notePad << modNames.setCls << _T("* set = &rcd;") << nCrlf;
  notePad << nCrlf;

  n = modNames.index.length();

  notePad << _T("  for ( ; set && set->") << modNames.index;
  notePad << _T(" <= id; set = (*this)++)");

  if ((n*2 + 75) > PaperWidth) {notePad << nCrlf << tabStg(PaperWidth - 29 - n);}

  notePad << _T(" if (set->") << modNames.index;
  notePad << _T(" == id) return set;") << nCrlf;

  notePad << _T("  for ( ; set && set->") << modNames.index;
  notePad << _T(" >= id; set = (*this)--)");

  if ((n*2 + 75) > PaperWidth) {notePad << nCrlf << tabStg(PaperWidth - 29 - n);   flag = false;}

  notePad << _T(" if (set->") << modNames.index;
  notePad << _T(" == id) return set;") << nCrlf;

  if (flag) notePad << nCrlf;

  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


void RcdSetBdy::edit() {
  notePad << _T("bool ") << modNames.setCls << _T("::edit()") << nCrlf;
  notePad << _T("  {if (!opened) return false;  ");
  notePad << _T("try {Edit(); return true;} catch(...) {return false;}}") << nCrlf;
  }


void RcdSetBdy::addNew() {
  notePad << _T("bool ") << modNames.setCls << _T("::addNew()") << nCrlf;
  notePad << _T("  {if (!opened) return false;  ");
  notePad << _T("try {AddNew(); return true;} catch(...) {return false;}}") << nCrlf;
  }


void RcdSetBdy::update() {
  notePad << _T("bool ") << modNames.setCls << _T("::update()") << nCrlf;
  notePad << _T("  {if (!opened) return false;  ");
  notePad << _T("try {Update(); movePrev(); return true;} catch(...) {return false;}}") << nCrlf;
  }


void RcdSetBdy::remove() {
  notePad << _T("bool ") << modNames.setCls << _T("::remove()") << nCrlf;
  notePad << _T("  {if (!opened) return false;  ");
  notePad << _T("try {Delete(); movePrev(); return true;} catch(...) {return false;}}") << nCrlf;
  }


void RcdSetBdy::fieldExch() {
FldsIter     iter(fields);
Field*       fld;
String       rfx;
String       arg;
Declarations decl;

  notePad << _T("void ") << modNames.setCls << _T("::DoFieldExchange(CFieldExchange* pFX) {");
  notePad << nCrlf << nCrlf;
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
  notePad << _T("  try {Move(-1);} catch (...) {try {Move(-1);} catch (...) {return 0;}}");
  notePad << nCrlf << nCrlf;
  notePad << _T("  return IsBOF() ? 0 : this;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


