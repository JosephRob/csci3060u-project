#ifndef __REFUND_H_INCLUDED__
#define __REFUND_H_INCLUDED__
#include <string>
using namespace std;
/*
This is the refund class
This class has 2 functions, constructor and refund function itself
*/
class refundClass{
public:
  string sellerName, buyerName;
  double credit;
  refundClass();
  bool refund();
  bool checkUser(string userName);
  bool isNumber(const string& s);
  double getBalance(string username);
};
#endif
