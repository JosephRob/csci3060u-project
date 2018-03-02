#ifndef __DELETE_H_INCLUDED__
#define __DELETE_H_INCLUDED__
#include <string>
using namespace std;
/*
This is the delete class,
The class has 2 functions, constructor
and deleteUser function
*/
class deleteClass{
public:
  string deleteUserName, userType;
  double userBalance;
  deleteClass();
  bool deleteUser(string userLogName);
  bool checkUser(string userName);
  string spaceFiller(int totChar, string filler, string word);
  string settingPrecision(double numb);
};
#endif
