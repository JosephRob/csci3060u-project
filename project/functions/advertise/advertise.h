#ifndef __ADVERTISE_H_INCLUDED__
#define __ADVERTISE_H_INCLUDED__

#include <string>
using namespace std;
class advertiseClass{
public:
  string itemName;
  double startingValue;
  int marketDays;
  advertiseClass();
  bool advertise();
};
//string advertise();
#endif
