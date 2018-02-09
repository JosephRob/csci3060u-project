#include "addCredit.h"
#include <iostream>
#include <string>

addCreditClass::addCreditClass(){}
string addCreditClass::addCredit(string userLogName, string userBalance, string userType){
  string isCalled = "add credit function is called";
  double addBalance;
  string targetUsername;

  cout << "How much money to add? Max $1000.00 per day. (e.g. 12.45 to add $12.45)" << endl;
  cout << "Add balance: $";
  cin >> addBalance;

  //if admin does the addCredit, will ask the target userName
  cout << "Input target username" << endl;
  cout << "Username: ";
  cin >> targetUsername;

  //if balance > 0 and <= 1000, print out the add credit is success and return the number of credit added
  //as a string

  //if cancel is entered during add credit process, will return string "cancel" and stop add
  //credit process
  //For now we just return a message that addCredit is called;

  return isCalled;
}
