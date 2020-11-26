// Table Descriptor Report


#pragma once
#include "ReportBase.h"

class NotePad;


class TableDscRpt : public ReportBase {

String tableName;
int    noPages;
int    maxLng;

public:

  TableDscRpt(NotePad& notePad) : ReportBase(notePad) { }
 ~TableDscRpt() { }

//  void print(CScrView& vw);

  void footer(Display& dev, int pageNo);          // Output page Footer to NotePad

private:

  TableDscRpt() : ReportBase(*(NotePad*)0) { }

  void create();
  void detTabs();
  void detTblTabs(String& name);
  void dspRecords(String& name);

  bool isNewPage(int n);
  int  header(NotePad& ntpd, bool printing);
  };

