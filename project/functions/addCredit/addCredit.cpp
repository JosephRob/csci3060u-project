#include "addCredit.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
// HELPER FUNCTION(S)
bool addCreditClass::isNumber(const string& s){
    if (s.empty())
       return false;

    bool sawDot = false;
    for (char c : s ){
       if (!(isdigit(c) || (c == '.' && !sawDot)))
          return false;
       sawDot = sawDot || (c == '.');
    }
    return true;
}

bool addCreditClass::checkTarget(string userName){
    string line, word;
    ifstream inFile ("files/userList.txt");
    while (getline(inFile, line)){
        stringstream data(line);
        vector<string> theLine;
        while(getline(data,word,' ')){
            if (word != ""){
                theLine.push_back(word);
            }
        }

        if (theLine[0] == userName){
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

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
bool addCreditClass::addCredit(string userType, double maxAddBalanceThisSession){
  double addBalance;
  bool validValue;
  bool targetExists;
  string input;
  string target;

  string maxBalance;
  stringstream val;
  val << fixed << setprecision(2) << maxAddBalanceThisSession;
  maxBalance = val.str();

  cout << "\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=ADD CREDIT=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
  cout << "How much money to add? Max $1000.00 per day. (e.g. 12.45 to add $12.45)" << endl;
  cout << "Your max credit to add this session is only $" + maxBalance << endl;
  cout << "Enter credit or cancel to cancel" << endl;
  cout << "Add balance: $";

  cin.ignore();
  getline(cin, input);
  cout << endl;
  while(input != "cancel"){
    //check if valid should be under the while loop not before.
    validValue = isNumber(input);
    if (validValue) {
      addBalance = atof(input.c_str());
      if ((maxAddBalanceThisSession - addBalance >= 0.0) && (addBalance > 0.0)){
        credit = addBalance;
        //if admin does the addCredit, will ask the target userName
        if (userType == "AA"){
          cout << "Input target username" << endl;
          cout << "Username: ";
          cin >> target;
          cout << endl;
          while(target != "cancel"){
            if (checkTarget(target)){
              targetUserName = target;
              return true;
            } else {
              cout << "User does not exist, please re-input user, or cancel to cancel" << endl;
              cout << "Username: ";
              cin >> target;
              cout << endl;
            }
          }
          return false;
        }
        return true;

      } else {
        if (addBalance > maxAddBalanceThisSession){
          cout << "Cannot add more than maximum balance for this session." << endl;
        }
      }
    } else {
      cout << "\nInput not valid" << endl;
    }
    cout << "Enter new balance to add, or cancel to cancel" << endl;
    cout << "Add balance: $";
    getline(cin, input);
  }
  return false;
}
