// Books Table Extension Template


#pragma once
#include "BooksMap.h"


class BooksTbl : public BooksTable {

public:

  BooksTbl() : BooksTable() { }

  BooksRecord* get(String& title);

  BooksRecord* find(const long key) {return BooksTable::find(key);}

private:

  BooksRecord* find(String& title);
  };
