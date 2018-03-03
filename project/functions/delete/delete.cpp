#include "delete.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

/*
This is the constructor for delete class
This sets initial value to variables
*/
string deleteClass::spaceFiller(int totChar, string filler, string word){
    string fill;
    for (int i = 0; i < (totChar-word.length());i++){
        fill += filler;
    }
    return fill;
}

//this function set precision of the double value to
//2 digits and return as string
string deleteClass::settingPrecision(double numb){
  string presValue;
  stringstream value;
  value << fixed << setprecision(2) << numb;
  presValue = value.str();
  return presValue;
}

//this is the delete constructor
deleteClass::deleteClass(){
  deleteUserName = "";
  userType = "";
  userBalance = 0.0;
}

//this function checks if the user exists or not
//because if user exists, we cannot have the same username
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
            if (theLine[1] == "AA"){
              return false;
            } else {
              return true;
            }
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
  string balance, appendDelete;
  cout << "Enter username to be deleted" << endl;
  cout << "Username: ";
  while(input != "cancel"){
    cin >> input;
    cout << endl;
    if (input == "cancel"){
      return false;
    } else {
      if (checkUser(input)){
        cout << "Are you sure you want to delete " + input + "? (yes/no):\n> ";
        while(confirmation != "yes"){
          cin >> confirmation;
          cout << endl;
          if (confirmation == "yes"){
            deleteUserName = input;
            balance = settingPrecision(userBalance);
            appendDelete = deleteUserName + spaceFiller(15, " ", deleteUserName) + " ** " + spaceFiller(9, "0", balance) + balance;
            //change the value of userType deleted to **,
            //to tell next session that the user deleted
            //cannot login (delete active immediately)

            string userListInsides, line, word;
            ifstream fileIn ("files/userList.txt");
            while (getline(fileIn,line)){

                stringstream data(line);
                vector<string> theLine;
                while(getline(data,word,' ')){
                    if (word != ""){
                        theLine.push_back(word);
                    }
                }
                if (theLine[0] != deleteUserName){
                  userListInsides += line + "\n";
                } else {
                  userListInsides += appendDelete + "\n";
                }
            }
            fileIn.close();
            ofstream fileOut ("files/userList.txt");
            fileOut << userListInsides;
            fileOut.close();
            return true;
          } else if (confirmation == "no"){
            return false;
          } else {
            cout << "Input invalid" << endl;
          }
        }
      } else {
        cout << "Cannot delete user " + input << endl;
        cout << "Enter username to be deleted or cancel to cancel" << endl;
        cout << "Username: ";
      }
    }
  }

  return false;
}
