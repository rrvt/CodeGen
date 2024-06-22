// Names of each field in the table


#include "pch.h"
#include "Fields.h"
#include "Database.h"
#include "NotePad.h"


Fields fields;


bool Fields::load(TCchar* path, TCchar* table) {
FldIter    iter(accFldDsc);
AccFldDsc* dsc;

  data.clear();

  if (!accFldDsc.open(path, table)) return false;

  this->table = table;

  for (dsc = iter(); dsc; dsc = iter++) {Field& fld = data.nextData();   fld.load(dsc);}

  accFldDsc.close();   return true;
  }



void Field::load(AccFldDsc* dsc) {
  name     = dsc->name;
  typeName = dsc->typeName;
  length   = dsc->length;

if (dsc->type < 0) {
  notePad << nClrTabs << nSetRTab(20) << nSetTab(22);
  notePad << name << nTab << dsc->type << nTab << _T(" -- ") << typeName;
  notePad << _T("  Length = ") << length << nCrlf;
  }

  switch (dsc->type) {
    case -10: type = LongStgFld; break;
    case  -9: type = StgFld; break;
    case  -7: type = BoolFld; break;
    case   4: type = typeName == _T("COUNTER") ? IdxFld : IntFld; break;
    default : type = FieldType(dsc->type); break;
    }
  }



String Fields::getArgList(int& n) {
FldsIter iter(*this);
Field*   fld;
String   s;

  for (n = 0, fld = iter(); fld; fld = iter++) {

    if (fld->isSelected) {
      if (n) s += _T(", ");

      if (fld->type == StgFld) s += _T("TCchar* ");

      s += fld->name; n++;
      }
    }

  return s;
  }


String Fields::getArgsComp() {
FldsIter iter(*this);
Field*   fld;
String   s;
int      i;

  for (i = 0, fld = iter(); fld; fld = iter++) {

    if (fld->isSelected) {
      if (i) s += _T(" && ");

      s += _T("this->") + fld->name + _T(" == ") + fld->name; i++;
      }
    }

  return s;
  }


String Fields::getArgs() {
FldsIter iter(*this);
Field*   fld;
String   s;
int      i;

  for (i = 0, fld = iter(); fld; fld = iter++) {

    if (fld->isSelected) {if (i) s += _T(", ");    s += fld->name; i++;}
    }

  return s;
  }


void Fields::display() {
FldsIter iter(*this);
Field*   dsc;

  notePad << nCrlf;
  notePad << table << _T(" Table") << nCrlf << nCrlf;

  notePad << nClrTabs << nSetRTab(30) << nSetTab(33) << nSetTab(45);

  for (dsc = iter(); dsc; dsc = iter++) {
    dsc->display();
    }
  }




void Field::display() {
  notePad << name;

  notePad << nTab;

  switch (type) {
    case NilFld     : notePad << _T("NilFld"); break;
    case IdxFld     : notePad << _T("IdxFld"); break;
    case IntFld     : notePad << _T("IntFld"); break;
    case StgFld     : notePad << _T("StgFld"); break;
    case LongStgFld : notePad << _T("LStFld"); break;
    case BoolFld    : notePad << _T("BolFld"); break;
    case UnkFld     : notePad << _T("UnkFld"); break;
    default         : notePad << int(type); break;
    }

  notePad << nTab << typeName;
  if (isIndex) notePad << nTab << _T("Key Index");
  if (isSelected) notePad << nTab << _T("Selected");
  notePad << nCrlf;
  }

