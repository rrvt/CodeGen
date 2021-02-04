// Sample Data Store


#pragma once
#include "Archive.h"
#include "Date.h"
#include "Device.h"
#include "ExpandableP.h"
#include "IterT.h"
#include "Wrap.h"



// This is the Data record.  It can be a complex as necessary.
// Set will accept any reasonable group of entities and then will divide up the input into fields in
// the data.
// Get will return any grouping of data desired from the record, or there might be multiple get methods
// that will retrieve invidual or groups of fields.
// Note, the copy constructor and operator often call a private function that will do all the copying.

class Data {
String s;
Wrap   wrp;

public:

  Data()        { }                                       // Copy constructor: Data a = b;
  Data(Data& d) {s = d.s;}
 ~Data()        { }

  void    set(String& s) {this->s = s;}
  String& get() {return s;}

  void    add(String& stg);                               // Parse the data into the record

  int     wrap(Device& dev, CDC* dc);
  int     noLines() {return wrp.noLines();}

  int     display();

  Data&   operator= (Data& d) {s = d.s; return *this;}    // Copy operator: a = b;

  bool    operator== (Data& data) {return s == data.s;}
  bool    operator>  (Data& data) {return s >  data.s;}
  bool    operator<= (Data& data) {return s <= data.s;}
  };


// Define the iterator used to look at the data in the datastore.  It is here so that it can be friended

typedef RcdPtrT<Data> DataP;
class DataStore;
typedef IterT<DataStore, Data> DSIter;                        // Iterator for the DataStore


// This is the main store.  I think of it as a permanent home for the data while the program is running.
// The Expandable array deals with the uncertainty of the amount of data as it expands by doubling in
// length each time it has to expand.
// In this example, we provide a way to load it from a file, the details of which are up to the Data
// class.  The data can be stored in a file, again the details of each record are enclosed in the Data
// class.  We can add something to the store from the user or some other source (TBD).  In this example
// a sort option is provided to change the order of the data in the array.
// Finally, the destructor returns the allocated Data records back to the heap (see cpp file).

class DataStore {

ExpandableP<Data, DataP,  4> data;

public:

String name;
Date   dt;
int    mssnNo;

  DataStore() : mssnNo(0) { }
 ~DataStore();

  void setName(String& s);
  String date()           {return dt.getDate();}
  String time()           {return dt.getTime();}
  int    missionNo();

  void load(Archive& ar);
  void store(Archive& ar);

  bool isEmpty() {return data.end() == 0;}

  void add(String& s);

  void sort();

private:

  // returns either a pointer to data (or datum) at index i in array or zero
  Data* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  // returns number of data items in array
  int   nData()      {return data.end();}

  friend typename DSIter;
  };


extern DataStore dataStore;                                   // Sometimes there only needs to one object

