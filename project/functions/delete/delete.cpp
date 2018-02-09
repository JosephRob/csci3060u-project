#include "delete.h"
#include <iostream>
#include <string>
string deleteUser(string userLogName){
  string isCalled = "delete function is called";
  string userToDel, confirmation;
  cout << "Enter username to be deleted" << endl;
  cout << "Username: ";
  cin >> userToDel;
  //check if userToDel is not user itself and check if user exist

  cout << "Are you sure you want to delete " + userToDel + " ? (yes/no): " << endl;
  cin >> confirmation;

  //check if yes then delete all assets, if no then cancel deleted
  //For the return, we will return a string with format of "userToDel"
  //If confirmation is equal to "no", then will cancel deleteuser, and return "cancel" that will
  //stop the process of delete user
  //For now we will return "delete function is called"
  return isCalled;
}
