#include "bid.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <iomanip>

// HELPER FUNCTION(S)
//this function checks if the number is a valid number
bool bidClass::isNumber(const string& s){
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

//this function checks the item that the user wants
//this also fetch the item name, item owner, and current bid
vector<string> bidClass::checkItem(string itemName){
  string line, word;
  ifstream inFile ("files/itemList.txt");
  vector<string> toReturn;
  while (getline(inFile, line)){
    stringstream data(line);
    vector<string> result;
    while(getline(data,word,' ')){
      if (word != ""){
        result.push_back(word);
      }
    }

    if (result[0] == itemName){
      toReturn.push_back(result[0]); //item name
      toReturn.push_back(result[1]); //item owner
      toReturn.push_back(result[4]); //current bid
    }
  }
  inFile.close();
  return toReturn;
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
bool bidClass::bid(string userType){
  string name, owner;
  bool itemExists;
  bool sellerExists = false;
  bool validInput;
  bool cont = false;
  int itemsSize = 0;
  string input;
  double currentBid;

  cout << "\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=BID=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
  cout << "Item name to bid: ";
  cin.ignore();
  getline (cin,input);
  cout << endl;
  for (int i = 0; i < input.length(); i++){
    if (input[i] == ' '){
      input[i] = '_';
    }
  }
  while(input != "cancel"){
    //check item exists, fetch item seller, item current price
    vector <string> items;
    items = checkItem(input);
    itemsSize = items.size()/3;
    string itemNames[itemsSize];
    string itemSeller[itemsSize];
    double itemCurrentBid[itemsSize];
    if (items.size() != 0){
      itemName = input;
      //show seller names if there are 2 items with same name different seller
      if (items.size() > 3){ //means there are more than 1 seller with same item name
        for (int i = 0, index = 0; i < itemsSize*3; i+=3){
          itemNames[index] = items[i];
          itemSeller[index] = items[i+1];
          itemCurrentBid[index] = atof(items[i+2].c_str());
          index++;
        }
        cout << "\nItem Name                 Seller          Value " << endl;
        for (int i = 0; i < itemsSize; i++){
          string alteredItemName = itemNames[i];
          for (int x = 0; x < alteredItemName.length(); x++){
            if (alteredItemName[x] == '_'){
              alteredItemName[x] = ' ';
            }
          }
          cout << alteredItemName + " " + itemSeller[i] + " $" << itemCurrentBid[i] << endl;
        }

      } else { //means there is only 1 seller for that item name
        currentBid = atof(items[2].c_str());
        name = items[0];
        owner = items[1];
        string alteredItemName = name;
        for (int x = 0; x < alteredItemName.length(); x++){
          if (alteredItemName[x] == '_'){
            alteredItemName[x] = ' ';
          }
        }
        cout << alteredItemName + " " + owner + " $" << currentBid << endl;
      }
      while(input != "cancel"){
        cout << "\nEnter Seller Username" << endl;
        cout << "Username: ";
        cin >> input;
        cout << endl;
        if (input == "cancel"){
          return false;
        } else {
          if (itemsSize == 1){
            if (input == owner){
              itemOwner = input;
              cont = true;
            } else {
              cout << "Owner not found" << endl;
            }
          } else {
            for (int i = 0; i < itemsSize; i++){
              if (itemSeller[i] == input){
                sellerExists = true;
                currentBid = itemCurrentBid[i];
                cont = true;
                itemOwner = input;
                itemsSize += 1;
              }
            }
            if (!sellerExists){
              cout << "Owner not found" << endl;
            }
          }
          if (cont){
            if (currentBid >= 999.99){
              cout << "Item is in maximum price, you cannot bid on this item anymore\nSorry! :(" << endl;
              return false;
            } else {
              while (input != "cancel"){
                cout << "Bid Value (e.g. 53 for $53.00, max item price is $999.99): $";
                cin >> input;
                cout << endl;
                validInput = isNumber(input);
                if (validInput){
                  if (userType == "AA"){
                    if (atof(input.c_str()) > 999.99){
                      cout << "Maximum item price is $999.99" << endl;
                      cout << "Enter new value, or cancel to cancel" << endl;
                    } else {

                      if (atof(input.c_str()) <= currentBid){
                        cout << "Cannot bid lower or same to current bid" << endl;
                        cout << "Enter new value, or cancel to cancel" << endl;
                      } else {
                        bidValue = atof(input.c_str());
                        return true;
                      }
                    }
                  } else {
                    if ((atof(input.c_str()) < currentBid*1.05)){
                      cout << "Bid must be minimum 5 percent higher than current value" << endl;
                    } else {
                      if(atof(input.c_str()) > 999.99){
                        cout << "Maximum item price is $999.99" << endl;
                        cout << "Enter new value, or cancel to cancel" << endl;
                      } else {
                        bidValue = atof(input.c_str());
                        return true;
                      }
                    }
                  }
                } else {
                  if(input == "cancel"){
                    return false;
                  } else {
                    cout << "Please input valid value, or cancel to cancel" << endl;
                  }
                }
              }
            }
          }
        }
      }
    } else {
      if (input == "cancel"){
        return false;
      }
      cout << "Item not exist, please input item name, or cancel to cancel" << endl;
    }
    cout << "Item name to bid: ";
    getline (cin,input);
    cout << endl;
  }

  return false;
}
