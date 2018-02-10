#include "advertise.h"
#include <iostream>
#include <string>

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
  string isCalled = "advertise function is called";
  string name, alteredName;
  int days;
  double value;

  cout << "Item Name (e.g. Macbook Pro, max 25 character including spaces): ";
  cin.ignore();// this will receive space
  getline(cin, name);

  //alter item name to change space into _
  for (int i = 0; i < name.length(); i++){
      if (name[i] != ' '){
          alteredName += name[i];
      } else {
          alteredName += '_';
      }
  }
  itemName = alteredName;

  cout << "Starting Price (e.g. 15.31 for $15.31, max $999.99): $";
  cin >> value;
  startingValue = value;

  cout << "Days (e.g. 7 for 7 days, max 999 days): ";
  cin >> days;
  marketDays = days;

  //Assuming that there is no error while the user input, this function will return true
  //later in the main functions, true will be set as advertise successful

  //if cancel is entered during advertise process, will return string false and stop
  //the advertise process

  //For now we just return true because we assume user/admin correctly used function
  return true;
}
