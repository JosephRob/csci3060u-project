#include "bid.h"
#include <iostream>
#include <string>

bidClass::bidClass(){
  itemName = "";
  itemOwner = "";
  bidValue = 0.0;
}

bool bidClass::bid(){
  string name, owner;
  double value;

  cout << "\nBid Menu" << endl;
  cout << "Item Name: ";
  cin.ignore();
  getline (cin,name);
  itemName = name;
  //check if name of item exists, but for now we dont, we just assume user input an existing item name

  cout << "\nEnter Seller Username" << endl;
  cout << "Username: ";
  cin >> owner;
  itemOwner = owner;

  //check if it itemOwner exists with the item name to be bid.

  cout << "Bid Value (e.g. 9053 for $9053.00, max $999999): $";
  cin >> value;
  bidValue = value;
  //check if bid value is at least 5%, except Admin

  //if success, this function will return true

  //if cancel is entered during bid process, will return false to stop bid process
  //and redirect to menu

  //But for now will return true because we assume user/admin used bid class correctly
  return true;
}
