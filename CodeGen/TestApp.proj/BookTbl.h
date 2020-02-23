// Book Table Extension Template


#pragma once
#include "BookMap.h"


class BookTbl : public BookTable {

public:

  BookTbl() : BookTable() { }

  BookRecord* get(String& title);

  BookRecord* find(const long key) {return BookTable::find(key);}

private:

  BookRecord* find(String& title);
  };
