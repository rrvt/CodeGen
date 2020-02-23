// Book Table Extension Template


#include "stdafx.h"
#include "BookTbl.h"
#include "Utilities.h"


BookRecord* BookTbl::get(String& title) {
BookRecord* r = find(title);   if (r) return r;
BookRecord  rcd;

  rcd.Title = title;    rcd.mark();  BookTable::add(rcd);

  toDatabase();   return find(title);
  }


BookRecord* BookTbl::find(String& title) {
BookRecord* rcd;

  if (isEmpty(&title, 0)) return 0;

  for (rcd = startLoop(); rcd; rcd = nextRecord()) if (rcd->Title == title) return rcd;
  return 0;
  }

