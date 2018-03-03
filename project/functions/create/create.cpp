#include "create.h"
#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <fstream>
#include <sstream>

/*
This is the constructor
This sets the variables into initial values
*/
createClass::createClass(){
  newUserName = "";
  newUserType = "";
  newBalance = 0.0;
}

//this function will check if the string has a character
//that is passed to the function
bool createClass::contains(string toBeChecked, char checker){
  for (int i = 0; i < toBeChecked.length(); i++){
    if (toBeChecked[i] == checker){
      return true;
    }
  }
  return false;
}

//this function will check so that the new username doesnt equal to any option name
bool createClass::isFuncName(string toBeChecked){
  locale loc;
  string userFuncs[12] = {"advertise", "bid", "create", "delete", "refund", "showmenu", "addcredit", "cancel", "list", "show", "menu", "add"};
  string lowerCased;
  for (int i = 0; i < toBeChecked.length(); i++){
    lowerCased += tolower(toBeChecked[i], loc);
  }

  for (int i = 0; i < 12; i++){
    if (lowerCased == userFuncs[i]){
      return true;
    }
  }

  return false;
}

//this function checks if the number is a valid number
bool createClass::isNumber(const string& s){
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

//this function checks if the user exists or not
//because if user exists, we cannot have the same username
bool createClass::checkUser(string userName){
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
This is the create function,
current userLogName, so admin,
cannot create another admin with the same name as his.
*/
bool createClass::create(string userLogName){
  string input;
  bool validUsername;
  bool keepCont = false;
  cout << "\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=CREATE+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
  cout << "Username (15 characters, no space): ";
  cin.ignore();
  while(input != "cancel"){
    validUsername = true;
    getline(cin,input);
    cout << endl;

    if (input == "cancel"){
      return false;
    } else {
      if (!checkUser(input)){
        //check if username between 15 characters
        if ((0 < input.length()) && (input.length() <= 15)){
          for (int i = 0 ; i < input.length(); i++){
            if (contains(input, ' ')){
              validUsername = false;
            }
          }
          if (validUsername && (!isFuncName(input))){
            newUserName = input;
            keepCont = true;
          } else {
            cout << "Name is invalid" << endl;
            cout << "Please enter new username, max 15 characters, no space, or cancel to cancel" << endl;
            cout << "Username: ";
          }
        } else {
          if (input.length() == 0){
            cout << "Name cannot be empty" << endl;
            cout << "Please enter new username, max 15 characters, no space, or cancel to cancel" << endl;
            cout << "Username: ";
          } else {
            cout << "Name longer than 15 characters" << endl;
            cout << "Please enter new username, max 15 characters, no space, or cancel to cancel" << endl;
            cout << "Username: ";
          }
        }
        if (keepCont){
          cout << "User Type (AA = Admin, FS = Full-Standard, BS = Buy-Standard, SS = Sell-Standard)\n> ";
          while(input != "cancel"){
            getline(cin,input);
            cout << endl;
            if (input == "cancel"){
              return false;
            } else {
              if ((input == "AA") || (input == "FS") || (input == "BS") || (input == "SS")){
                keepCont = true;
                newUserType = input;
              } else {
                keepCont = false;
                cout << "User type not valid" << endl;
                cout << "Please enter user Type (AA = Admin, FS = Full-Standard, BS = Buy-Standard, SS = Sell-Standard)\n> ";
              }
            }
            if (keepCont){
              if (input == "AA"){
                newBalance = 999999.99;
                return true;
              } else if (input == "SS"){
                newBalance = 000000.00;
                return true;
              } else {
                cout << "Insert balance (e.g. 123.41 for $123.41, max $999999.99): $";
                while (input != "cancel"){
                  getline(cin,input);
                  cout << endl;
                  if (isNumber(input)){
                    if ((0.0 < atof(input.c_str())) && (atof(input.c_str()) < 1000000.00)){
                      newBalance = atof(input.c_str());
                      return true;
                    } else {
                      cout << "Balance out of range" << endl;
                    }
                  } else {
                    if (input == "cancel"){
                      return false;
                    } else {
                      cout << "Value not valid" << endl;
                    }
                  }
                  cout << "Insert balance (e.g. 123.41 for $123.41, max $999999.99): $";
                }
              }
            }
          }
        }
      } else {
        cout << "User exists! Please enter new username (15 characters, no space), or cancel to cancel" << endl;
        cout << "Username (15 characters, no space): ";
      }
    }
  }

  return false;
}
