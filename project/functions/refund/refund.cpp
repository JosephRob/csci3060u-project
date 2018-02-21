#include "refund.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

/*
This is the refund class constructor
this sets initial values to variables
*/
refundClass::refundClass(){
  sellerName = "";
  buyerName = "";
  credit = 0.0;
}

bool refundClass::isNumber(const string& s){
    if (s.empty()){
      return false;
    }

    bool sawDot = false;
    for (char c : s ){
       if (!(isdigit(c) || (c == '.' && !sawDot)))
          return false;
       sawDot = sawDot || (c == '.');
    }
    return true;
}

double refundClass::getBalance(string userName){
  string line, word;
  double balance;
  ifstream inFile ("files/userList.txt");
  while (getline(inFile, line)){
      stringstream data(line);
      vector<string> theLine;
      while(getline(data,word,' ')){
          if (word != ""){
              theLine.push_back(word);
          }
      }
      if (theLine[0] == userName){
          balance = atof(theLine[2].c_str());
          inFile.close();
          return balance;
      }
  }
  inFile.close();
  return balance;
}

bool refundClass::checkUser(string userName){
    string line, word;
    ifstream inFile ("files/userList.txt");
    while (getline(inFile, line)){
        stringstream data(line);
        vector<string> theLine;
        while(getline(data,word,' ')){
            if (word != ""){
                theLine.push_back(word);
            }
        }
        if (theLine[0] == userName){
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

/*
This is the refund function
*/
bool refundClass::refund(){
  //string seller, buyer;
  string input;
  cout << "\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=REFUND+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
  cout << "Enter BUYER username" << endl;
  cout << "Username: ";
  while(input != "cancel"){
    cin >> input;
    if (checkUser(input)){
      buyerName = input;
      cout << "Enter SELLER username" << endl;
      cout << "Username: ";
      while(input != "cancel"){
        cin >> input;
        if (checkUser(input)){
          sellerName = input;
          cout << "Enter credit to be returned" << endl;
          cout << "Credit: $";
          while (input != "cancel"){
            cin >> input;
            if (isNumber(input)){
              if ((0.0 < atof(input.c_str())) && (atof(input.c_str()) < 1000000.0)){
                //check if balance of buyer is not more than max after the refund
                if ((getBalance(buyerName) + atof(input.c_str())) < 1000000.0) {
                  //check if balance of seller is not negative after the refund
                  if ((getBalance(sellerName) - atof(input.c_str())) > 0.0) {
                    credit = atof(input.c_str());
                    return true;
                  } else {
                    cout << "Balance of SELLER will be negative after refund process" << endl;
                    return false;
                  }
                } else {
                  cout << "Balance of BUYER will be over $999999.99 after refund process" << endl;
                  return false;
                }

              } else {
                cout << "\nCredit out of range" << endl;
              }
            } else {
              cout << "\nCredit not valid" << endl;
            }
            cout << "Credit: $";
          }
        } else {
          if (input == "cancel"){
            return false;
          } else {
            cout << "\nSeller does not exist" << endl;
            cout << "Enter SELLER username or cancel to cancel" << endl;
          }
        }
        cout << "Username: ";
      }
    } else {
      if (input == "cancel"){
        return false;
      } else {
        cout << "\nBuyer does not exist" << endl;
        cout << "Enter BUYER username or cancel to cancel" << endl;
      }
    }
    cout << "Username: ";
  }

  //if refund success, will return true
  //if refund process is cancelled, (balance of seller is negative after deduction or cancel is entered),
  //will return false, and will stop the process.

  //For now we return true
  return false;
}
