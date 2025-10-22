// Create Table Body File


#pragma once


class TableBdy {

public:

  TableBdy() { }

  void create();
  void createDsp();

private:

  void constructor();
  void clear();
  void load();
  void loadRcd();
  void store();
  void storeRcd();
  void addRcd();
  void copySet();
  void copyRcd();
  void copyFld(TCchar* fld, int max);
  void add();

  void display();
  void dispRcd();
  void setTabs();
  };

