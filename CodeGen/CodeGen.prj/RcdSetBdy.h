// Module RcdSetHdr Creation



#pragma once


class RcdSetBdy {

public:

  RcdSetBdy() { }

  void create();

private:

  void constructor();
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
  };


