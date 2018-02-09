#ifndef __BID_H_INCLUDED__
#define __BID_H_INCLUDED__
#include <string>
using namespace std;
class bidClass{
public:
  string itemName, itemOwner;
  double bidValue;
  bidClass();
  bool bid();
};
//string bid(string userLogName);
#endif
