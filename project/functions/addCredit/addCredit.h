#ifndef __ADDCREDIT_H_INCLUDED__
#define __ADDCREDIT_H_INCLUDED__
#include <string>
using namespace std;
class addCreditClass{
public:
  double credit;
  string targetUserName;
  addCreditClass();
  bool addCredit(string userLogName, string userBalance, string userType);
};
//string addCredit(string userLogName, string userBalance, string userType);
#endif
