#include "addCredit.h"
#include <iostream>
#include <string>

/*
This is the constructor function,
sets all the public variables for the first time
*/
addCreditClass::addCreditClass(){
  credit = 0.0;
  targetUserName = "";
}

/*
This is the addCredit function itself.
It is currently not 100% complete.
It takes userType as an argument to check if the user is admin or not, because
if it is admin, this function needs to have the target username.
*/
bool addCreditClass::addCredit(string userType){
  double addBalance;
  string target;

  cout << "How much money to add? Max $1000.00 per day. (e.g. 12.45 to add $12.45)" << endl;
  cout << "Add balance: $";
  cin >> addBalance;
  //check if balance > 0 and <= 1000, print out the add credit is success and return the number of credit added
  //as a string
  credit = addBalance;

  //if admin does the addCredit, will ask the target userName
  if (userType == "AA"){
    cout << "Input target username" << endl;
    cout << "Username: ";
    cin >> target;
    targetUserName = target;
  }

  //if cancel is entered during add credit process, will return false and stop add
  //credit process
  //For now we return true because we assume that admin/user used addCredit correctly;

  return true;
}
