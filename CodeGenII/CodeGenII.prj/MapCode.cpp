// Create Data Base Map Code


#include "stdafx.h"
#include "MapCode.h"
#include "NotePad.h"
#include "TableExtension.h"


#if 0
void MapCode::createTableExtensions() {
TDIter         iter(tableDscrs);
TableDsc*      dsc;

  for (dsc = iter(); dsc; dsc = iter++)
    if (dsc->selected) {TableExtension ext(dsc->name); if (!ext(*dsc)) break;}
  }
#endif

