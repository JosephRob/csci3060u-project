#ifndef __BID_H_INCLUDED__
#define __BID_H_INCLUDED__
#include <string>
#include <vector>
using namespace std;
/*
This is the class for bid.
This class has 2 functions, constructor and bid
function itself.
*/
class bidClass{
public:
  string itemName, itemOwner;
  double bidValue;
  bidClass();
  bool bid(string userType);
  bool isNumber(const string& s);
  vector<string> checkItem(string itemName);
};
#endif
