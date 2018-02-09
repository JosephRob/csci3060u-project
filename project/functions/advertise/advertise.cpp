#include "advertise.h"
#include <iostream>
#include <string>

string advertise(){
  string isCalled = "advertise function is called";
  string name, days, alteredName;
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

  cout << "Starting Price (e.g. 15.31 for $15.31, max $999.99): $";
  cin >> value;
  cout << "Days (e.g. 7 for 7 days, max 999 days): ";
  cin >> days;

  //Assuming that there is no error while the user input, this function will return a string with
  //format of "alteredName,value,days". so each value divided by comma

  //if cancel is entered during advertise process, will return string "cancel" and stop
  //the advertise process
  
  //For now we just return the string "advertise function is called"
  return isCalled;
}
