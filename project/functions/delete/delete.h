#ifndef __DELETE_H_INCLUDED__
#define __DELETE_H_INCLUDED__
#include <string>
using namespace std;
class deleteClass{
public:
  string deleteUserName, userType;
  double userBalance;
  deleteClass();
  bool deleteUser(string userLogName);
};
//string deleteUser(string userLogName);
#endif
