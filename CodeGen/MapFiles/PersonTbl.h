// Person Table Extension Template


#pragma once
#include "PersonMap.h"


class PersonTbl : public PersonTable {

public:

  PersonTbl() : PersonTable() { }

  PersonRecord* get(String& firstName, String& lastName);

  PersonRecord* find(const long key) {return PersonTable::find(key);}

private:

  PersonRecord* find(String& firstName, String& lastName);
  };
