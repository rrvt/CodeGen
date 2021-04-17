


#include "stdafx.h"
#include "Module.h"
#include "DAOAccess.h"
#include "DAOrecords.h"
#include "DAOfields.h"
#include "Declarations.h"
#include "NotePad.h"
#include "PrimeKeyDlg.h"
#include "SrchCmpntDlg.h"
#include "Utilities.h"


/*
FieldP Properties
  long         CollatingOrder;
  short        Type;
  _variant_t   Value;
  _bstr_t      Name;
  short        CollectionIndex;
  long         Size;
  _variant_t   OriginalValue;
  _bstr_t      SourceField;
  _bstr_t      SourceTable;
  _variant_t   VisibleValue;
  long         FieldSize;
  long         Attributes;
  short        OrdinalPosition;
  _bstr_t      ValidationText;
  VARIANT_BOOL ValidateOnSet;
  _bstr_t      ValidationRule;
  _variant_t   DefaultValue;
  VARIANT_BOOL Required;
  VARIANT_BOOL AllowZeroLength;
  VARIANT_BOOL DataUpdatable;
  _bstr_t      ForeignName;

Field Attributes Bits
  dbFixedField      = 1,
  dbVariableField   = 2,
  dbAutoIncrField   = 16,
  dbUpdatableField  = 32,
  dbSystemField     = 8192,
  dbHyperlinkField  = 32768,
  dbDescending      = 1
*/



Module::Module(TCchar* name) : namePfx(name),
                               tblName(namePfx  + _T("Tbl")),
                               tblObj(tblName),
                               rcdName(namePfx  + _T("Rcd")),
                               ptrName(rcdName  + _T('P')),
                               daoTbl(daoTables.bSearch(name)),
                               primaryKey(0),
                               noFields(0) {
  Tchar& ch = tblObj[0]; if (_T('A') <= ch && ch <= _T('Z')) ch += _T('a') - _T('A');
  }


bool Module::getSearchFields() {
                                                  if (!daoTbl) return false;
DAOrcdsIter rcdIter(daoTbl);
FieldsP     fields   = rcdIter(DAOdenyWrite);     if (!fields) return false;
DAOfldsIter iter(fields);
DAOfield*   field;
FieldDsc*   indexFld;               // key in memory copy of record

  noFields = fields->Count;

  for (field = iter(); field; field = iter++) fieldList.add(field);

  primaryKey = fieldList.findPrimKey();

  PrimeKeyDlg pkDlg(fieldList);    pkDlg.title = _T("Select Primary Key for") + daoTbl->name;

  pkDlg.tblName = daoTbl->name;

  if (pkDlg.DoModal() != IDOK) return false;

  indexFld = fieldList.findPrimKey();   tblAbbr = pkDlg.abbr;   iterName = tblAbbr + _T("Iter");

  indexName  = indexFld->name;
  indexType  = indexFld->type;    if (indexType == _T("String")) indexType = _T("TCchar*");

  SrchCmpntDlg scDlg(fieldList);    scDlg.title = _T("Select Linear Search Fields");

  if (scDlg.DoModal() != IDOK) return false;

  return true;
  }



String Module::getArgList(int& n) {
FldListIter iter(fieldList);
FieldDsc*   fld;
String      s;

  for (n = 0, fld = iter(); fld; fld = iter++) {

    if (fld->isSelected) {
      if (n) s += _T(", ");

      if (fld->type == _T("String")) s += _T("TCchar* ");
      else                           s += fld->type + _T(" ");

      s += fld->name; n++;
      }
    }

  return s;
  }


String Module::getArgsComp() {
FldListIter iter(fieldList);
FieldDsc*   fld;
String      s;
int         i;

  for (i = 0, fld = iter(); fld; fld = iter++) {

    if (fld->isSelected) {
      if (i) s += _T(" && ");

      s += _T("this->") + fld->name + _T(" == ") + fld->name; i++;
      }
    }

  return s;
  }


String Module::getArgs() {
FldListIter iter(fieldList);
FieldDsc*   fld;
String      s;
int         i;

  for (i = 0, fld = iter(); fld; fld = iter++) {

    if (fld->isSelected) {if (i) s += _T(", ");    s += fld->name; i++;}
    }

  return s;
  }

