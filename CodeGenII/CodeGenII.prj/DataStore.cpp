// Sample Data Store


#include "stdafx.h"
#include "DataStore.h"
#include "NotePad.h"
#include "qsort.h"


const int TabVal = 5;


DataStore dataStore;                                        // Global since all classes need access


// The destructor needs to return the Data records to the heap.

DataStore::~DataStore() {
int i;

  for (i = 0; i < data.end(); i++) {
    DataP& dataP = data[i];

    delete dataP.p;  dataP.p = 0;
    }
  }


void DataStore::setName(String& s) {name = s; dt.getToday();}


int DataStore::missionNo() {
  if (!mssnNo) {Date d; d.getToday();   CTimeSpan t = d - dt;  mssnNo = t.GetSeconds() % 60;}

  return mssnNo;
  }


// Load is called from serialize in the Document class
// The basic idea is that the method reads some chunk from the file (Archive is a fileio surrogate)

void DataStore::load(Archive& ar) {
String s;

  while (ar.read(s)) add(s);
  }


void DataStore::store(Archive& ar) {

  }


void DataStore::add(String& s) {data[data.end()].add(s);}



void DataP::add(String& s) {p = new Data;   p->add(s);}


// Parse the data into the record

void Data::add(String& stg) {
int pos = stg.find('\n');

  s = pos >= 0 ? stg.substr(0, pos) : stg;
  }


void DataStore::sort() {qsort(&data[0], &data[data.end()-1]);}




int Data::wrap(Display& dev, CDC* dc) {
int  chWidth = dev.chWidth();

  dev << dCR << dClrTabs << dSetTab(TabVal) << dTab;    // Return to left margin (dCR), clear Tabs and
                                                        // tab to position desired for wrap
    wrp.initialize(dc, dev.remaining(), false);

  dev<< dCR << dClrTabs;                                // return to left margin and clear tabs

  return wrp(s);                                        // wrap string
  }



int Data::display() {
WrapIter iter(wrp);
String*  p;
int      i;

  notePad << nClrTabs << nSetTab(TabVal) << nTab;       // The tab is set to the same value as in wrap

  for (p = iter(), i = 0; p; p = iter++, i++) {
    if (i) notePad << nTab;

    notePad << *p << nCrlf;
    }

  return i;
  }

