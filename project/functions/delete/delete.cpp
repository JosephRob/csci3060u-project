#include "delete.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

/*
This is the constructor for delete class
This sets initial value to variables
*/
deleteClass::deleteClass(){
  deleteUserName = "";
  userType = "";
  userBalance = 0.0;
}

bool deleteClass::checkUser(string userName){
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
            userType = theLine[1];
            userBalance = atof(theLine[2].c_str());
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

/*
This is the deleteUser function.
It takes 1 argument and it is admin's userLogName
to make sure admin cannot delete himself.
*/
bool deleteClass::deleteUser(string userLogName){
  cout << "\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=CREATE+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
  string userToDel, confirmation;
  string input;
  cout << "Enter username to be deleted" << endl;
  cout << "Username: ";
  while(input != "cancel"){
    cin >> input;
    if (input == "cancel"){
      return false;
    } else {
      if (checkUser(input)){
        cout << "Are you sure you want to delete " + input + "? (yes/no):\n> ";
        while(confirmation != "yes"){
          cin >> confirmation;
          if (confirmation == "yes"){
            deleteUserName = input;
            //change the value of userType deleted to **,
            //item name owned by user to **********
            //to tell next session that the user deleted
            //cannot login (delete active immediately)
            return true;
          } else if (confirmation == "no"){
            return false;
          } else {
            cout << "Input invalid" << endl;
            cout << "Are you sure you want to delete " + input + "? (yes/no):\n> ";
          }
        }
      } else {
        cout << "User not exists" << endl;
        cout << "Enter username to be deleted or cancel to cancel" << endl;
        cout << "Username: ";
      }
    }
  }

  return false;
}
