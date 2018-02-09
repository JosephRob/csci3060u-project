#include "bid.h"
#include <iostream>
#include <string>
string bid(string userLogName){ //we need userLogName passed to bid function so that owner cannot bid his own item
  string isCalled = "bid function is called";
  string name, value, itemOwner;
  int value;

  cout << "\nEnter Seller Username" << endl;
  cout << "\nUsername: ";
  cin >> itemOwner;

  cout << "\nBid Menu" << endl;
  cout << "Item Name: ";
  cin.ignore();
  getline (cin,name);
  //check if name of item exists, but for now we dont, we just assume user input an existing item name

  cout << "Bid Value (e.g. 9053 for $9053.00, max $999999): $";
  cin >> value;
  //check if bid value is at least 5%, except Admin

  //if success, this function will return a string with format of "itemname,itemowner,bid value"
  //separate by comma. But for now will return "bid function is called"
  return isCalled;
}
