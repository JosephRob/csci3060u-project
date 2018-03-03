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

//this function checks if the number is a valid number
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

//this function checks if the user exists or not
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
  string input;
  cout << "\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=REFUND+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
  cout << "Enter BUYER username" << endl;
  cout << "Username: ";
  cin.ignore();
  while(input != "cancel"){
    getline (cin,input);
    cout << endl;
    if (checkUser(input)){
      buyerName = input;
      cout << "Enter SELLER username" << endl;
      cout << "Username: ";
      while(input != "cancel"){
        getline (cin,input);
        cout << endl;
        if (checkUser(input)){
          sellerName = input;
          cout << "Enter credit to be returned" << endl;
          cout << "Credit: $";
          while (input != "cancel"){
            getline (cin,input);
            cout << endl;
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
                  cout << "Balance of BUYER will be over maximum balance after refund process" << endl;
                  return false;
                }

              } else {
                cout << "Credit out of range" << endl;
              }
            } else {
              cout << "Credit not valid" << endl;
            }
            cout << "Credit: $";
          }
        } else {
          if (input == "cancel"){
            return false;
          } else {
            cout << "Seller does not exist" << endl;
            cout << "Enter SELLER username or cancel to cancel" << endl;
          }
        }
        cout << "Username: ";
      }
    } else {
      if (input == "cancel"){
        return false;
      } else {
        cout << "Buyer does not exist" << endl;
        cout << "Enter BUYER username or cancel to cancel" << endl;
      }
    }
    cout << "Username: ";
  }

  return false;
}
