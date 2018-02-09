#include "create.h"
#include <iostream>
#include <string>

createClass::createClass(){}
string createClass::create(string userLogName){
  string isCalled = "create function is called";
  string username, usertype, balance;
  double balInDb;
  cout << "Username (15 characters include spaces): ";
  cin.ignore();
  getline(cin, username);
  //check if username between 15 characters, but not now

  cout << "User Type (AA = Admin, FS = Full-Standard, BS = Buy-Standard, SS = Sell-Standard)\n> ";
  cin >> usertype;

  if (usertype == "AA"){
      balance = "999999.99";
  } else if (usertype == "SS") {
      balance = "000000.00";
  } else {
      cout << "Insert balance (e.g. 123.41 for $123.41): $";
      cin >> balance;
      //check if balance not negative, and not more than 999999.99
  }

  //if process of create user successfull,
  //will return a string with format of "newUserName,accountType,balance"

  //if cancel is entered anywhere when asking for username, usertype, balance,
  //will return a string "cancel" and stop creating process

  //but for now we wil return "create function is called"

  return isCalled;
}
