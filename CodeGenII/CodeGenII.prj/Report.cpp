// Report -- Essentially the output processing is separated from the file input/output processing


#include "stdafx.h"
#include "Report.h"
#include "DataStore.h"
#include "CodeGenII.h"
#include "Utilities.h"


Report report;



void Report::operator() (bool printing) {
CodeGenIIView& vw  = *view();

  this->printing = printing;

  if (printing) detNoLines(vw);

  detWraps(vw);

  vw.disableWrap();

  if (printing) detNoPages(vw);

//  vw.disableWrap();

  create();
  }


void Report::detNoLines(CodeGenIIView& vw) {
int i;
int mxPgs;

  vw.suppressOutput();   maxLines = 999999;

  notePad.clear();

  // Header simulation
  notePad << nBold << nFSize(160) << _T("ICS 214a Unit Log") << nFont << nFont << nCrlf;
  notePad << nBold << _T("SJ RACES") << nFont << nCrlf << nCrlf;
  notePad << nFSize(90) << _T("4. Unit Name Designator") << nFont << nCrlf;
  notePad << _T("San Jose RACES") << nCrlf << nCrlf;
  notePad << nFSize(90) << _T("Date") << nFont << nCrlf;

  for (i = 8; i < 65; i++) {
    String s; s.format(_T("Line %i"), i);
    notePad  << s << nCrlf;
    }

  vw.trialRun(maxLines, mxPgs);
  }


void Report::detWraps(CodeGenIIView& vw) {
Display& dev = vw.getDev();
CDC*     dc  = dev.getDC();
DSIter   iter(dataStore);
Data*    datum;

  for (datum = iter(); datum; datum = iter++) datum->wrap(dev, dc);
  }


void Report::detNoPages(CodeGenIIView& vw) {int nLns;   create();   vw.trialRun(nLns, maxPages);}


void Report::create() {
int       ttlLines;
String    t;

  if (dataStore.isEmpty()) return;

  notePad.clear();   ttlLines = header();

  ttlLines += body();

  crlf();

  notePad << _T("   Total Lines") << nTab << ttlLines << nTab << _T(" Lines");   crlf();

  if (printing) notePad << nEndPage;
  else          dspFtr();
  }




int Report::header() {

  noLines = 0;

  notePad << nClrTabs << nSetTab(18) << nSetRTab(45);

  notePad << nBold << nFSize(160) << _T("Code Gen II") << nFont << nFont;
  notePad << nTab << nFSize(90) << _T("1. Sample Report");
  notePad << nRight << _T("2. Date, Time Prepared") << nFont;   crlf();

  notePad << nBold  << _T("Report Data") << nFont;
  notePad << nTab   << dataStore.name;
  notePad << nRight << dataStore.date() << _T(" - ") <<  dataStore.time();
  crlf();   crlf();

  notePad << nClrTabs << nSetTab(6) << nSetRTab(17) << nSetTab(18);
  notePad << nFSize(90) << _T("Data") << nFont;   crlf();

  return noLines;
  }


// Output report body to NotePad

int Report::body() {
DSIter iter(dataStore);
Data*  datum;
int    n;
int    nLns = 0;

  for (datum = iter(); datum; datum = iter++) {

    n = datum->noLines();

    if (iter.isLast()) n += 2;

    if (printing && n + noLines > maxLines) {notePad << nEndPage;    nLns += header();}

    noLines += datum->display();   nLns += n;
    }

  return nLns;
  }



void Report::footer(Display& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dClrTabs << dSetTab(7);
  dev << dFSize(90) << _T("ICS 214a") << dTab << _T("8. Prepared By") << dCenter;
  dev << _T("9. Mission Number") << dRight << _T("10. Page No.")  << dPrevFont << dCrlf;

  dev << _T("RACES") << dTab << _T("Bob") << dCenter << dataStore.missionNo();
  dev << dRight << pageN << _T(" of ") << maxPages << dflushFtr;
  }


void Report::dspFtr() {

  notePad << nCrlf;

  notePad << nClrTabs << nSetTab(7);
  notePad << nFSize(90) << _T("ICS 214a") << nTab << _T("8. Prepared By") << nCenter;
  notePad << _T("9. Mission Number") << nRight << _T("10. Page No.")  << nFont << nCrlf;

  notePad << _T("RACES") << nTab << _T("Bob") << nCenter << dataStore.missionNo();
  notePad << nRight << _T("1") << _T(" of ") << _T("1") << nCrlf;
  }

