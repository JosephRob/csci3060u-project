#ifndef __CREATE_H_INCLUDED__
#define __CREATE_H_INCLUDED__
#include <string>
using namespace std;
class createClass{
public:
  string newUserName, newUserType;
  double newBalance;
  createClass();
  bool create(string userLogName);
};
//string create(string userLogName);
#endif
