#include "bid.h"
#include <iostream>
#include <string>

// HELPER FUNCTION(S)
bool bidClass::is_number(const string& s){
    if (s.empty())
       return false;

    bool sawDot = false;
    for (char c : s ){
       if (!(isdigit(c) || (c == '.' && !sawDot)))
          return false;
       sawDot = sawDot || (c == '.');
    }
    return true;
}

/*
This is the constructor for bid class
This sets initial value for the variables
*/
bidClass::bidClass(){
  itemName = "";
  itemOwner = "";
  bidValue = 0.0;
}

/*
This is the bid function itself.
*/
bool bidClass::bid(){
  string name, owner;
  bool itemExists;
  bool validInput;
  string input;
  double value;
  double itemPrice;
  cout << "\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=BID=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
  cout << "Item name to bid: ";
  cin.ignore();
  getline (cin,name);
  while(input != "cancel"){
    //check item exists
    itemExists = true;

    if (itemExists){
      itemName = name;
      //show seller names if there are 2 items with same name different seller
      //also fetch item price;
      cout << "\nEnter Seller Username" << endl;
      cout << "Username: ";
      cin >> input;
      if (input == "cancel"){
        return false;
      } else {
        itemOwner = input;
        cout << "Bid Value (e.g. 9053 for $9053.00, max $999999): $";
        cin >> input;
        while (input != "cancel"){
          validInput = is_number(input);
          if (validInput){
            // cout ;
            if ( (atof(input.c_str())*1.05 < itemPrice) ){
              cout << "Bid must be 5 percent" << endl;
            } else {
              bidValue = atof(input.c_str());
              return true;
            }
          } else {
            if(input == "cancel"){
              return false;
            } else {
              cout << "Please input valid value, or cancel to cancel" << endl;
            }
          }
          cout << "Bid Value (e.g. 9053 for $9053.00, max $999999): $"
          getline(cin, input);
        }
      }
    } else {
      if (input == "cancel"){
        return false;
      }
      cout << "Item not exist, please input item name, or cancel to cancel" << endl;
    }
    cout << "Item name to bid: ";
    getline (cin,name);
  }

  //check if it itemOwner exists with the item name to be bid.

  //check if bid value is at least 5%, except Admin

  //if success, this function will return true

  //if cancel is entered during bid process, will return false to stop bid process
  //and redirect to menu

  //But for now will return true because we assume user/admin used bid class correctly
  return false;
}
