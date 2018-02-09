#include "delete.h"
#include <iostream>
#include <string>

deleteClass::deleteClass(){
  deleteUserName = "";
  userType = "";
  userBalance = 0.0;
}

bool deleteClass::deleteUser(string userLogName){//need to pass userLogName to function to make sure admin doesnt delete himself
  string userToDel, confirmation;
  cout << "Enter username to be deleted" << endl;
  cout << "Username: ";
  cin >> userToDel;
  //check if userToDel is not user itself and check if user exist
  //meanwhile checking on userToDel, this program will also record the information of the person
  //the user type and balance.

  cout << "Are you sure you want to delete " + userToDel + " ? (yes/no):\n> ";
  cin >> confirmation;
  if (confirmation == "yes"){
    //if confirmation of delete is a yes
    deleteUserName = userToDel;

  } else {
    //this function will return false if confirmation says no
    //and stop process of delete user
    //return false;
  }

  //For now we will return true
  return true;
}
