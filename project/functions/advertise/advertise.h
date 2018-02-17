#ifndef __ADVERTISE_H_INCLUDED__
#define __ADVERTISE_H_INCLUDED__

#include <string>
using namespace std;
/*
This is the class for advertise function
In this class, there are 2 functions, the constructor
and the advertise function itself
*/
class advertiseClass{
public:
  string itemName;
  double startingValue;
  int marketDays;
  advertiseClass();
  bool advertise();
  bool is_number(const string& s);
};
#endif
