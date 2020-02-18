// Descriptor Table and Entries


#include "stdafx.h"
#include "DescTable.h"
#include "NotePad.h"
#include "Utilities.h"


int DescTable::load(Maps& maps, String& tableName) {
AceFieldNames fldDscs;
int           i;
AceFldNameDsc dsc;
bool          rslt;
FieldDesc*    fldDesc;

  maxFldLng = 0;   name = tableName;

  if (!maps.openFldDscs(tableName, fldDscs)) return false;

  for (rslt = fldDscs.startLoop(dsc), clear(), i = 0; rslt; rslt = fldDscs.nextDesc(dsc), i++) {

    fldDesc = Add();

    fldDesc->fieldIndex = i;
    fldDesc->name       = normalizeName(dsc.name);
    fldDesc->lng        = fldDesc->name.length();
    fldDesc->v.vt       = VT_EMPTY;
    fldDesc->x          = dsc.type;
    fldDesc->isIndex    = (dsc.attr & dbAutoIncrField) != 0;

    if (fldDesc->lng > maxFldLng) maxFldLng = fldDesc->lng;
    }

  AceRecordSet records;   if (!maps.openRcdSet(tableName, DaoReadOnly, records)) return 0;
  AceFields    fields(records);
  AceFieldDsc  valDsc;

  for (rslt = fields.startLoop(valDsc), fldDesc = startLoop(); rslt;
                                                rslt = fields.nextField(valDsc), fldDesc = nextDesc()) {

    if (!fldDesc)
              {notePad << _T("More field data than field names") << nCrlf << nCrlf; return desc.end();}

    fldDesc->v = valDsc.value;
    }

  if (fldDesc && !last())
         {notePad << _T("Field scan less that record name scan") << nCrlf << nCrlf; return desc.end();}

  return desc.end();
  }


FieldDesc* DescTable::getKeyDesc() {
int i;
int n = desc.end();

  for (i = 0; i < n; i++) if (desc[i].isIndex) return &desc[i];

  return 0;
  }

