// Add a linear search to the table classes


#include "stdafx.h"
#include "LinSrch.h"
#include "Capitalize.h"
#include "ModNames.h"
#include "NotePad.h"
#include "SrchCmpntDlg.h"


LinSrch linSrch;


void LinSrch::getFields() {
SrchCmpntDlg scDlg;    scDlg.title = _T("Select Linear Search Fields");
FldsIter     iter(fields);
Field*       fld;

  scDlg.DoModal();

  data.clear();

  for (fld = iter(); fld; fld = iter++) if (fld->isSelected) {
    SrchFld& rcd = data.nextData();
    rcd.name = fld->name;
    rcd.type = fld->type;
    }

  n = nData();
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

#if 0
CityStateRcd* CityStateTbl::find(TCchar* city, TCchar* zip) {
CtyIter       iter(*this);
CityStateRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->isInRcd(city, zip)) return rcd;

  return 0;
  }
#endif




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



