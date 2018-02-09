#include "create.h"
#include <iostream>
#include <string>

createClass::createClass(){
  newUserName = "";
  newUserType = "";
  newBalance = 0.0;
}

bool createClass::create(string userLogName){
  string username, usertype, balance;
  double balInDb;
  cout << "Username (15 characters include spaces): ";
  cin.ignore();
  getline(cin, username);
  //check if username between 15 characters, but not now
  newUserName = username;

  cout << "User Type (AA = Admin, FS = Full-Standard, BS = Buy-Standard, SS = Sell-Standard)\n> ";
  cin >> usertype;
  newUserType = usertype;

  if (usertype == "AA"){
      balance = "999999.99";
  } else if (usertype == "SS") {
      balance = "000000.00";
  } else {
      cout << "Insert balance (e.g. 123.41 for $123.41): $";
      cin >> balance;
      //check if balance not negative, and not more than 999999.99
  }
  balInDb = atof(balance.c_str());
  newBalance = balInDb;

  //if process of create user successfull,
  //will return true

  //if cancel is entered anywhere when asking for username, usertype, balance,
  //will return a string false and stop creating process

  //but for now we wil return true
  return true;
}
