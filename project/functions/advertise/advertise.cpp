#include "advertise.h"
#include <iostream>
#include <string>
#include <sstream>

// HELPER FUNCTION(S)
bool advertiseClass::is_number(const string& s){
    if (s.empty())
       return false;

    bool sawDot = false;
    for (char c : s ){
       if (!(std::isdigit(c) || (c == '.' && !sawDot)))
          return false;
       sawDot = sawDot || (c == '.');
    }
    return true;
}

/*
This is the constructor function, will set the
public variables with initial value
*/
advertiseClass::advertiseClass(){
  itemName = "";
  startingValue = 0.0;
  marketDays = 0;
}

/*
This is the advertise function.
Advertise does not take any argument.
*/
bool advertiseClass::advertise(){
  bool validValue;
  string input;
  double value;
  cout << "\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ADVERTISE+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
  cout << "Item Name (e.g. Macbook Pro, max 25 character including spaces): ";
  cin.ignore();// this will receive space
  getline(cin, input);
  if (input == "cancel"){
    return false;
  } else {
    //alter item name to change space into _
    for (int i = 0; i < input.length(); i++){
        if (input[i] == ' '){
            input[i] = '_';
        }
    }
    itemName = input;
    while(input != "cancel"){
      cout << "Starting Price (e.g. 15.31 for $15.31, max $999.99): $";
      cin >> input;
      validValue = is_number(input);
      if (validValue){
        if ((0.0 <= atof(input.c_str())) && (atof(input.c_str()) <= 999.99)){
          startingValue = atof(input.c_str());
          while(input!="cancel"){
            cout << "Days (e.g. 7 for 7 days, max 999 days): ";
            cin >> input;
            validValue = is_number(input);
            stringstream val(input);
            int day = 0;
            val >> day;
            if (validValue){
              if ((0 < day) && (day < 1000)){
                marketDays = atof(input.c_str());
                return true;
              } else {
                cout << "Days not in range" << endl;
                cout << "Please input days, or cancel to cancel" << endl;
              }
            } else {
              if (input == "cancel"){
                return false;
              } else {
                cout << "Not a valid value" << endl;
                cout << "Please enter valid value, or cancel to cancel" << endl;
              }
            }
          }
        } else {
          cout << "Starting value out of range" << endl;
          cout << "Please input starting price, or cancel to cancel" << endl;
        }
      } else {
        if (input == "cancel"){
          return false;
        } else {
          cout << "Not a valid value" << endl;
          cout << "Please enter valid value, or cancel to cancel" << endl;
        }
      }
    }
  }

  //Assuming that there is no error while the user input, this function will return true
  //later in the main functions, true will be set as advertise successful

  //if cancel is entered during advertise process, will return string false and stop
  //the advertise process

  //For now we just return true because we assume user/admin correctly used function
  return false;
}
