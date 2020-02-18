// Person Table Extension Template


#include "stdafx.h"
#include "PersonTbl.h"
#include "Utilities.h"


PersonRecord* PersonTbl::get(String& firstName, String& lastName) {
PersonRecord* r = find(firstName, lastName);   if (r) return r;
PersonRecord  rcd;

  rcd.FirstName = firstName;    rcd.LastName = lastName;    rcd.mark();  PersonTable::add(rcd);

  toDatabase();   return find(firstName, lastName);
  }


PersonRecord* PersonTbl::find(String& firstName, String& lastName) {
PersonRecord* rcd;

  if (isEmpty(&firstName, &lastName, 0)) return 0;

  for (rcd = startLoop(); rcd; rcd = nextRecord())
                                if (rcd->FirstName == firstName && rcd->LastName == lastName) return rcd;
  return 0;
  }

