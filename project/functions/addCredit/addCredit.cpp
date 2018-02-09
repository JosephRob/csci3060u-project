#include "addCredit.h"
#include <iostream>
#include <string>
string addCredit(string userLogName, string userBalance, string userType){
  string isCalled = "add credit function is called";
  double addBalance;
  cout << "How much money do you want to add? Max $1000.00 per day. (e.g. 12.45 to add $12.45)" << endl;
  cout << "Add balance: $";
  cin >> addBalance;

  //if balance > 0 and <= 1000, print out the add credit is success and return the number of credit added
  //as a string
  //For now we just return a message that addCredit is called;

  return isCalled;
}
