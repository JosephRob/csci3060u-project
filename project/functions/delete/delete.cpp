#include "delete.h"
#include <iostream>
#include <string>

/*
This is the constructor for delete class
This sets initial value to variables
*/
deleteClass::deleteClass(){
  deleteUserName = "";
  userType = "";
  userBalance = 0.0;
}

/*
This is the deleteUser function.
It takes 1 argument and it is admin's userLogName
to make sure admin cannot delete himself.
*/
bool deleteClass::deleteUser(string userLogName){
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
