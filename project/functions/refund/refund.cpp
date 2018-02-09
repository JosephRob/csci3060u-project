#include "refund.h"
#include <iostream>
#include <string>

refundClass::refundClass(){
  sellerName = "";
  buyerName = "";
  credit = 0.0;
}

bool refundClass::refund(){
  string seller, buyer;
  double balanceToReturn;

  cout << "Enter buyer username" << endl;
  cout << "Username: ";
  cin >> buyer;

  cout << "Enter seller username" << endl;
  cout << "Username: ";
  cin >> seller;

  cout << "Enter balance to be returned" << endl;
  cout << "Balance: $";
  cin >> balanceToReturn;

  //check if balance is valid,
  //check if there is enough balance from seller, so seller doesn't have negative balance after
  //return process

  sellerName = seller;
  buyerName = buyer;
  credit = balanceToReturn;

  //if refund success, will return true
  //if refund process is cancelled, (balance of seller is negative after deduction or cancel is entered),
  //will return false, and will stop the process.

  //For now we return true
  return true;
}
