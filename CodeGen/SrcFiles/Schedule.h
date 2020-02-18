// Schedule Dummy for Gen and Entry

#pragma once
#include "FileIO.h"


class Schedule {
  
public:
  
  void write(FileIO& fio) {}
  void reset() {}
  void read(FileIO& fio) {}
  };


extern Schedule schedule;
