#ifndef __CREATE_H_INCLUDED__
#define __CREATE_H_INCLUDED__
#include <string>
using namespace std;
/*
This is the create class.
There are 2 functions, constructor and create function itself
*/
class createClass{
public:
  string newUserName, newUserType;
  double newBalance;
  createClass();
  bool create(string userLogName);
};
#endif
