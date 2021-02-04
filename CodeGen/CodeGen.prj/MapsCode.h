// Maps Code, i.e. MapData and Maps declarations


#pragma once


class MapsCode {

public:

  MapsCode() { }

  void createMapDataHdr();
  void createMapDataCpp();

  void createMapsHdr();
  void createMapsCpp();

private:

  void mapObjDecl(bool isExtern);
  };
