// Table Names


#pragma once


struct FieldDesc;


struct TableNames {
String name;
String abbr;
String obj;
String fileName;
String cls;
String tblCls;
String rcd;
String rcdObj;
String map;
String myDB;
String entry;
String rslt;
String iter;

String keyName;
String keyType;
int    keyIndex;

bool   loaded;

  TableNames(TCchar* tblName) {loaded = load(tblName);}
  TableNames(TCchar* tblName, TCchar* abbr, FieldDesc* fldDesc);

  bool isLoaded() {return loaded;}

private:

  void save();
  bool load(TCchar* tableName);
  void fillInNames();

  TableNames() {}
  };

