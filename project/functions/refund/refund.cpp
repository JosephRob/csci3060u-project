#include "refund.h"
#include <iostream>
#include <string>

refundClass::refundClass(){
  sellerName = "";
  buyerName = "";
  balance = 0.0;
}

bool refundClass::refund(){
  string seller, buyer;
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

  sellerName = seller;
  buyerName = buyer;
  balance = balanceToReturn;

  //if refund success, will return true
  //if refund process is cancelled, (balance of seller is negative after deduction or cancel is entered),
  //will return false, and will stop the process.

  //For now we return true
  return true;
}
