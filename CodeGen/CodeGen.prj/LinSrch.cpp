// Add a linear search to the table classes


#include "pch.h"
#include "LinSrch.h"
#include "Capitalize.h"
#include "ModNames.h"
#include "NotePad.h"
#include "SrchCmpntDlg.h"


LinSrch linSrch;


void LinSrch::getFields() {
SrchCmpntDlg dlg;    dlg.title = _T("Select Linear Search Fields");
FldsIter     iter(fields);
Field*       fld;

  if (dlg.DoModal() != IDOK) return;

  data.clear();   isFnName.clear();   abbrKey.clear();

  for (fld = iter(); fld; fld = iter++) if (fld->isSelected) {
    SrchFld& rcd = data.nextData();
    rcd.name = fld->name;
    rcd.type = fld->type;
    }

  n = nData();

  isFnName = dlg.fnName;   abbrKey = dlg.abbrKey;
  }


void LinSrch::addRcdHdrFn() {
LSrchIter iter(*this);
SrchFld*  fld;
int       i;
String    s;

  notePad << _T("  // Needed for Linear Search with one or more arguments") << nCrlf;
  notePad << _T("  bool contains(");
  for (i = 0, fld = iter(); fld; i++, fld = iter++) {
    if (i) notePad << _T(", ");
    switch (fld->type) {
      case IdxFld     :
      case IntFld     : notePad << _T("int "); break;
      case StgFld     :
      case LongStgFld : notePad << _T("TCchar* "); break;
      case BoolFld    : notePad << _T("bool "); break;
      }
    notePad << notCaped(fld->name);
    }
  notePad << _T(") {") << nCrlf;
  notePad << _T("    return ");

  for (i = 0, fld = iter(); fld; i++, fld = iter++) {
    if (i)  {
      notePad << _T(" &&");
      if (i % 3) notePad << _T(' ');
      else       notePad << nCrlf << _T("         ");
      }
    s = notCaped(fld->name);   notePad << _T("this->") << s << _T(" == ") << s;
    }
  notePad << _T(";") << nCrlf;
  notePad << _T("    }") << nCrlf;
  }


void LinSrch::addTblHdrFn() {
LSrchIter iter(*this);
SrchFld*  fld;
int       i;

  notePad << _T("  ") << modNames.rcdCls << _T("* find(");

  for (i = 0, fld = iter(); fld; i++, fld = iter++) {

    if (i) notePad << _T(", ");

    switch (fld->type) {
      case IdxFld     :
      case IntFld     : notePad << _T("int "); break;
      case StgFld     :
      case LongStgFld : notePad << _T("TCchar* "); break;
      case BoolFld    : notePad << _T("bool "); break;
      }
    notePad << notCaped(fld->name);
    }

  notePad << _T(");") << nCrlf;
  }


void LinSrch::addTblBdyFn() {
LSrchIter iter(*this);
SrchFld*  fld;
int       i;

  notePad << modNames.rcdCls << _T("* ") << modNames.tblCls << _T("::find(");

  for (i = 0, fld = iter(); fld; i++, fld = iter++) {

    if (i) notePad << _T(", ");

    switch (fld->type) {
      case IdxFld     :
      case IntFld     : notePad << _T("int "); break;
      case StgFld     :
      case LongStgFld : notePad << _T("TCchar* "); break;
      case BoolFld    : notePad << _T("bool "); break;
      }
    notePad << notCaped(fld->name);
    }
  notePad << _T(") {") << nCrlf;

  notePad << modNames.tblIter << _T(" iter(*this);") << nCrlf;
  notePad << modNames.rcdCls << _T("* rcd;") << nCrlf;
  notePad << nCrlf;

  notePad << _T("  for (rcd = iter(); rcd; rcd = iter++) if (rcd->contains(");
  for (i = 0, fld = iter(); fld; i++, fld = iter++) {

    if (i) notePad << _T(", ");

    notePad << notCaped(fld->name);
    }

  notePad << _T(")) return rcd;") << nCrlf;
  notePad << nCrlf;
  notePad << _T("  return 0;") << nCrlf;
  notePad << _T("  }") << nCrlf;
  }


/*
  bool    isNonResp(int id);
*/

bool LinSrch::addIsAbbrHdrFn() {
  if (!isAbbrKeyFn()) return false;

  notePad << _T("  bool ") << isFnName << _T("(int id);") << nCrlf;   return true;
  }


/*
bool AsnTbl::isNonResp(int id) {AsnRcd* rcd = find(id);   return rcd && rcd->aPKey == _T("N");}
*/

bool LinSrch::addIsAbbrBdyFn() {
  if (!isAbbrKeyFn()) return false;

  notePad << _T("bool ") << modNames.tblCls << _T("::") << isFnName << _T("(int id) {");
  notePad << modNames.rcdCls << _T("* rcd = find(id);   ");
  notePad << _T("return rcd && rcd->") << notCaped(data[0].name);
  notePad << _T(" == _T(\"") << abbrKey << _T("\");}") << nCrlf;   return true;
  }

