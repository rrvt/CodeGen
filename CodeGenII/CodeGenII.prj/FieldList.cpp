// List of Fields in a Table


#include "stdafx.h"
#include "FieldList.h"


void FieldList::add(DAOfield* field)
    {FieldDsc fldDsc; fldDsc.add(field); data += fldDsc;}


void FieldDsc::add(DAOfield* field) {

  name = field->name();
//  Tchar& ch = name[0];  if (_T('A' <= ch && ch <= _T('Z'))) ch += _T('a') - _T('A');
  changeCase(name);

  type = field->type();  isIndex = field->index();

  if (isIndex && type == _T("long")) name = _T("id");
  }


void FieldDsc::changeCase(String& name) {
int i;
int n = name.length();

  for (i = 0; i < n; i++) {
    Tchar& ch = name[i];

    if (i < 3 && _T('A' <= ch && ch <= _T('Z'))) {ch += _T('a') - _T('A');  continue;}

    if (i <= 1) return;

    if (ch == _T('a')) return;
    if (ch == _T('e')) return;
    if (ch == _T('i')) return;
    if (ch == _T('o')) return;
    if (ch == _T('u')) return;

    if (_T('a') <= ch && ch <= _T('z')) ch += _T('A') - _T('a');        return;
    }
  }


void FieldDsc::copy(FieldDsc& fd)
                      {name = fd.name; type = fd.type; isIndex = fd.isIndex; isSelected = fd.isSelected;}


FieldDsc* FieldList::findPrimKey() {
FldListIter iter(*this);
FieldDsc*   fld;

  for (fld = iter(); fld; fld = iter++) if (fld->isIndex) return fld;

  return 0;
  }


int FieldList::maxLength() {
FldListIter iter(*this);
FieldDsc*   fld;
int         lng;
int         max;

  for (max = 0, fld = iter(); fld; fld = iter++) {
    lng = fld->name.length();
    if (lng > max) max = lng;
    }

  return max;
  }




FieldDsc* FieldList::findSelected() {
FldListIter iter(*this);
FieldDsc*   fld;

  for (fld = iter(); fld; fld = iter++) if (fld->isSelected) return fld;

  return 0;
  }


