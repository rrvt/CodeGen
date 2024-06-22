// Module RcdSetHdr Creation


#pragma once
#include "Expandable.h"
#include "IterT.h"



class RcdSetBdy;
typedef IterT<RcdSetBdy, String> CnstrIter;


class RcdSetBdy {

Expandable<String, 16> data;
int                    max[6];
public:

  RcdSetBdy() { }

  void create();

private:

  void constructor();
  void newCnstrctr();
  int  nInitWide(int maxLng);
  bool initWideTrial(int n, int maxLng);
  void open();
  void find();
  void edit();
  void addNew();
  void update();
  void remove();
  void moveFirst();
  void moveNext();
  void moveLast();
  void movePrev();

  void fieldExch();

  // returns either a pointer to datum at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int    nData()      {return data.end();}                // Returns number of data items in array,
                                                          // not necessarily private
  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename CnstrIter;
  };


