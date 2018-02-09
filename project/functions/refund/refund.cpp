#include "refund.h"
#include <iostream>
#include <string>

refundClass::refundClass(){}
string refundClass::refund(){
  string isCalled = "refund function is called";
  string sellerName, buyerName;
  double balanceToReturn;

  cout << "Enter buyer username" << endl;
  cout << "Username: ";
  cin >> buyerName;

  cout << "Enter seller username" << endl;
  cout << "Username: ";
  cin >> sellerName;

  cout << "Enter balance to be returned" << endl;
  cout << "Balance: $";
  cin >> balanceToReturn;

  //check if balance is valid,
  //check if there is enough balance from seller, so seller doesn't have negative balance after
  //return process

  //if refund success, will return string with format of "sellerName,buyerName,balance"
  //if refund process is cancelled, (balance of seller is negative after deduction),
  //will return string "cancel", and will cut the process.
  //For now we return "refund function is called"

  return isCalled;
}
