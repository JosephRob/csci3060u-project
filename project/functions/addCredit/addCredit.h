#ifndef __ADDCREDIT_H_INCLUDED__
#define __ADDCREDIT_H_INCLUDED__
#include <string>
using namespace std;
/*
This is the class for add credit function.
In this function, there are 2 functions, the constructor
and the addCredit function itself
*/
class addCreditClass{
public:
  double credit;
  string targetUserName;
  addCreditClass();
  bool addCredit(string userType, double maxAddBalanceThisSession);
  bool isNumber(const string& s);
  bool checkTarget(string userName);
};
#endif
