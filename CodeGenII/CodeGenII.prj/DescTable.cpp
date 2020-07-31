// Descriptor Table and Entries


#include "stdafx.h"
#include "DescTable.h"
#include "NotePad.h"
#include "Utilities.h"


int DescTable::load(Maps& maps, TCchar* tableName) {
AceFieldNames  fldDscs;
AFNIter        iter(fldDscs);
AceFldNameDsc* dsc;
int            i;
FieldDesc*     fldDesc;

  maxFldLng = 0;   name = tableName;

  if (!maps.openFldDscs(tableName, fldDscs)) return false;

  for (dsc = iter(), clear(), i = 0; dsc; dsc = iter++, i++) {

    fldDesc = Add();

    fldDesc->fieldIndex = i;
    fldDesc->name       = normalizeName(dsc->name);
    fldDesc->lng        = fldDesc->name.length();
    fldDesc->v.vt       = VT_EMPTY;
    fldDesc->x          = dsc->type;
    fldDesc->isIndex    = (dsc->attr & dbAutoIncrField) != 0;

    if (fldDesc->lng > maxFldLng) maxFldLng = fldDesc->lng;
    }

  AceRecordSet records;   if (!maps.openRcdSet(tableName, DaoReadOnly, records)) return 0;
  AceFields    fields(records);
  AFIter       afIter(fields);
  DTIter       dtIter(*this);
  AceFieldDsc* valDsc;

  for (valDsc = afIter(), fldDesc = dtIter(); valDsc; valDsc = afIter++, fldDesc = dtIter++) {

    if (!fldDesc)
              {notePad << _T("More field data than field names") << nCrlf << nCrlf; return desc.end();}

    fldDesc->v = valDsc->value;
    }

  if (fldDesc && !dtIter.isLast())
         {notePad << _T("Field scan less that record name scan") << nCrlf << nCrlf; return desc.end();}

  return desc.end();
  }


FieldDesc* DescTable::getKeyDesc() {
int i;
int n = desc.end();

  for (i = 0; i < n; i++) if (desc[i].isIndex) return &desc[i];

  return 0;
  }

