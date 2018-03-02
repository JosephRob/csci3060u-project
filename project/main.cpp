#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "functions/showMenu/showMenu.h"
#include "functions/advertise/advertise.h"
#include "functions/bid/bid.h"
#include "functions/create/create.h"
#include "functions/addCredit/addCredit.h"
#include "functions/refund/refund.h"
#include "functions/delete/delete.h"

using namespace std;

double maxAddBalanceThisSession = 1000.0;
//HELPER FUNCTIONS
/*
Space filler function will basically fill spaces.
For example,
username has 15 characters max, and say a there is a user with 12 characters for
their username, this function will fill the 3 characters with what ever is passed
as the filler. (either ' ' or '0')
*/
string spaceFiller(int totChar, string filler, string word){
    string fill;
    for (int i = 0; i < (totChar-word.length());i++){
        fill += filler;
    }
    return fill;
}

string settingPrecision(double numb){
  string presValue;
  stringstream value;
  value << fixed << setprecision(2) << numb;
  presValue = value.str();
  return presValue;
}

/*
This function will basically print messages if an account entered functions that
are not permitted for them.
For example, an FS account, entered create.
this function will print the altered message saying that only admin can create
*/
void prompt(string users, string mode){
    cout << "\nYour account type does not support " + mode + "."<< endl;
    cout << "Only " + users + " support this option." << endl;
}

/*
This function will check if user exists in user list file
so that logging in is possible.
This function will a vector with 3 data inside, userLogName, userType
and userBalance, if the user is found in the file. If a user
is not in a file, this function will return a vector with no data.
*/
vector<string> checkUser(string userInput){
    string line, word;
    ifstream inFile ("files/userList.txt");
    vector<string> toReturn;
    while (getline(inFile, line)){
        stringstream data(line);
        vector<string> result;
        while(getline(data,word,' ')){
            if (word != ""){
                result.push_back(word);
            }
        }

        if (result[0] == userInput){
            inFile.close();
            return result;
        }
    }
    inFile.close();
    return toReturn;
}

/*
This function will basically append line passed to this function
to the destination file passed to this function.
*/
void uploadUpdates(string toAppend, string destination){
    string insides, line;
    ifstream fileIn (destination);
    if(fileIn){
        while (getline(fileIn,line)){
            insides += line + "\n";
        }
        fileIn.close();

        ofstream fileOut (destination);
        fileOut << insides + toAppend;
        fileOut.close();
    } else {
        ofstream fileOut (destination);
        fileOut << toAppend;
        fileOut.close();
    }
}

/*
This function will list all the items in itemList.txt
printing them like a table
*/
void list(){
    string insides, theLine, line;
    ifstream duFileI ("files/itemList.txt");
    cout << "Item Name                 Seller          Highest Bidder  Day Value " << endl;
    while (getline(duFileI,theLine)){
        stringstream data(theLine);
        string word;
        vector<string> result;
        while(getline(data,word,' ')){
            result.push_back(word);
        }
        stringstream item(result[0]);
        string firstWord;
        vector<string> itName;
        while(getline(item,firstWord,'_')){
            itName.push_back(firstWord);
        }
        for (int i = 0; i < itName.size(); i++){
            line += itName[i] + " ";
        }
        for (int i = 1; i < result.size(); i++){
            line += result[i] + " ";
        }
        cout << line << endl;
        line = "";
    }
    duFileI.close();
}

/*
This function is where the logic of the menu located. So this function,
will basically loop forever to display menu of what users can do,
and the page where users can interact with the program.
This function will return true if user wants to logout. and it will be received by
the main function, and main function will do process of logout
*/
bool userMenu(string userLogName, string userBalance, string userType){
    bool keepGoing = true;
    string appendLine;
    string menuInput;
    cout << "\nWelcome to the auction, " + userLogName + "!" << endl;
    cout << "Type: " + userType + "\tBalance: $" << atof(userBalance.c_str()) << endl;
    showMenu(userType);
    while (keepGoing == true){
        cout << "\nWhat would you like to do? (Type 'menu' to display menu) ";
        cin >> menuInput;

        if (menuInput == "list"){
            list();
        } else if (menuInput == "login"){
            cout << "Already logged in" << endl;
        } else if (menuInput == "menu"){
            showMenu(userType);
        } else if (menuInput == "add") { //assuming SS cannot add credit
            if (userType != "SS"){
                //call add function
                addCreditClass add;
                if (userType != "AA"){
                  if (maxAddBalanceThisSession > 0.0){
                    if (add.addCredit(userType, maxAddBalanceThisSession) == true){
                      //this is just example of output
                      cout << "Add credit process is done" << endl;

                      string bal = settingPrecision(add.credit);

                      appendLine = "06 " + userLogName + spaceFiller(15, " ", userLogName) + " " + userType + " " + spaceFiller(9, "0", bal) + bal + "\n";
                      maxAddBalanceThisSession -= add.credit;
                      uploadUpdates(appendLine,"files/userDailyUpdate.txt");
                      //cout << appendLine << endl;
                      cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                      appendLine = "";
                    } else {
                      cout << "Process is cancelled" << endl;
                      cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                    }
                  } else {
                    cout << "Cannot add more for this session" << endl;
                  }

                } else if (userType == "AA"){
                  if (add.addCredit(userType, maxAddBalanceThisSession) == true){
                    //this is just example of output
                    cout << "Add credit process is done" << endl;

                    string bal = settingPrecision(add.credit);

                    appendLine = "06 " + add.targetUserName + spaceFiller(15, " ", add.targetUserName) + " " + userType + " " + spaceFiller(9, "0", bal) + bal;
                    uploadUpdates(appendLine,"files/userDailyUpdate.txt");
                    //cout << appendLine << endl;
                    cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                    appendLine = "";
                  } else {
                    cout << "Process is cancelled" << endl;
                    cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                  }
                }

                //append line will then be uploaded to userDailyUpdate.txt
            } else {
                prompt("Admin or Full-Standard or Buy-Standard","add credit");
                showMenu(userType);
            }
        } else if (menuInput == "advertise"){
            if (userType != "BS"){
                //call advertise function
                advertiseClass adver;
                if (adver.advertise() == true){
                  //this is just example of output
                  cout << "Advertise process is done" << endl;

                  string startValue = settingPrecision(adver.startingValue);

                  stringstream ss;
                  ss << adver.marketDays;
                  string marketDays;
                  ss >> marketDays;

                  appendLine = "03 " + adver.itemName + spaceFiller(25, " ", adver.itemName)  + " " + userLogName + spaceFiller(15, " ", userLogName) + " " + spaceFiller(3, "0", marketDays) + marketDays + " " + spaceFiller(6, "0", startValue) + startValue;
                  uploadUpdates(appendLine,"files/userDailyUpdate.txt");
                  //cout << appendLine << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                  appendLine = "";
                } else {
                  cout << "Process is cancelled" << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                }
                //append line will then be uploaded to userDailyUpdate.txt
            } else {
                prompt("Admin or Full-Standard or Sell-Standard","advertise");
                showMenu(userType);
            }
        } else if (menuInput == "bid") {
            if (userType != "SS"){
                //call bid function
                bidClass bid;
                if(bid.bid(userType) == true){
                  //this is just example of output
                  cout << "Bid process is done" << endl;

                  string bidVal = settingPrecision(bid.bidValue);
                  appendLine = "04 " + bid.itemName + spaceFiller(25, " ", bid.itemName) + " " + bid.itemOwner + spaceFiller(15, " ", bid.itemOwner) + " " + userLogName + spaceFiller(15, " ", userLogName) + " " + spaceFiller(6, "0", bidVal) + bidVal;
                  uploadUpdates(appendLine,"files/userDailyUpdate.txt");
                  //cout << appendLine << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                  appendLine = "";
                } else {
                  cout << "Process is cancelled" << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                }
                //append line will then be uploaded to userDailyUpdate.txt
            } else {
                prompt("Admin or Full-Standard or Buy-Standard","bidding");
                showMenu(userType);
            }
        } else if (menuInput == "create"){
            if (userType == "AA"){
                //call create function
                createClass create;
                if(create.create(userLogName) == true){
                  //this is just example of output
                  cout << "Create process is done" << endl;

                  string startVal = settingPrecision(create.newBalance);

                  appendLine = "01 " + create.newUserName + spaceFiller(15, " ", create.newUserName) + " " + create.newUserType + " " + spaceFiller(9, "0", startVal) + startVal;
                  uploadUpdates(appendLine,"files/userDailyUpdate.txt");
                  //cout << appendLine << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                  appendLine = "";
                } else {
                  cout << "Process is cancelled" << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                }
                //append line will then be uploaded to userDailyUpdate.txt
            } else {
                prompt("Admin","create");
                showMenu(userType);
            }
        } else if (menuInput == "delete"){
            if (userType == "AA"){
                //call delete function
                deleteClass deleteC;
                if(deleteC.deleteUser(userLogName) == true){
                  //this is just example of output
                  cout << "Delete process is done" << endl;

                  string curBalance = settingPrecision(deleteC.userBalance);

                  appendLine = "02 " + deleteC.deleteUserName + spaceFiller(15, " ", deleteC.deleteUserName) + " " + deleteC.userType + " " + spaceFiller(9, "0", curBalance) + curBalance;
                  uploadUpdates(appendLine,"files/userDailyUpdate.txt");
                  //cout << appendLine << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                  appendLine = "";
                } else {
                  cout << "Process is cancelled" << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                }
                //append line will then be uploaded to userDailyUpdate.txt
            } else {
                prompt("Admin","delete");
                showMenu(userType);
            }
        } else if (menuInput == "refund"){
            if (userType == "AA"){
                //call refund function
                refundClass refund;
                if(refund.refund() == true){
                  //this is just example of output
                  cout << "Refund process is done" << endl;

                  string refundCredit = settingPrecision(refund.credit);

                  appendLine = "05 " + refund.buyerName + spaceFiller(15, " ", refund.buyerName) + " " + refund.sellerName + spaceFiller(15, " ", refund.sellerName) + " " + spaceFiller(9, "0", refundCredit) + refundCredit;
                  uploadUpdates(appendLine,"files/userDailyUpdate.txt");
                  //cout << appendLine << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                  appendLine = "";
                } else {
                  cout << "Process is cancelled" << endl;
                  cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=END=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
                }
                //append line will then be uploaded to userDailyUpdate.txt
            } else {
                prompt("Admin","refund");
                showMenu(userType);
            }
        } else if (menuInput == "logout") {
            return true; //done
        } else {
            cout << "\nWrong input, please re-input!" << endl;
        }
    }
    return false;
}

//Main Function
int main(int argc, const char * argv[]) {
    //for login logout purposes
    bool loggedIn = false;
    bool loggedOut = true; //when system starts, everyone is initially logged out
    string userInput;
    string funcs[] = {"advertise", "bid", "create", "delete", "refund", "add", "list"};

    //user info
    string userLogName, userType, userBalance;

    cout << "Enter command 'login' to login, or 'cancel' to cancel";
    while(loggedIn == false){
      cout << "\n> ";
        cin >> userInput;
        if (userInput == "login"){
            //do the login then break
            while(true){
                cout << "Username: ";
                cin >> userInput;
                if(userInput == "cancel"){
                    break;
                } else {
                    vector<string> result = checkUser(userInput);
                    if (result.size() != 0){
                        userLogName = result[0];
                        userType = result[1];
                        userBalance = result[2];
                        loggedIn = true;
                        loggedOut = false;
                        if (userType != "**"){
                          //everytime login is successfull, create userDailyUpdate. userDailyUpdate file is temporary. Will be deleted after user is logged out, before the system stops.
                          uploadUpdates("10 " + userLogName + spaceFiller(15, " ", userLogName) + " " + userType + " " + spaceFiller(9, "0", userBalance) + userBalance + "\n","files/userDailyUpdate.txt");
                          break;
                        } else {
                          cout << "Your account has been deleted by admin. Sorry!" << endl;
                          cout << "Goodbye!" << endl;
                          return 0;
                        }
                    } else {
                        cout << "Username not found." << endl;
                        cout << "Please re-input username, or 'cancel' to cancel.\n> ";
                    }
                }
            }
            break;
        } else {
            if (userInput == "logout"){
                cout << "You are not even logged in.\nPlease enter command 'login' to login, or 'cancel' to cancel.\n> ";
            } else if (find(begin(funcs), end(funcs), userInput) != end(funcs)){
                cout << "Must be logged in first in order to " + userInput << endl;
                cout << "Please enter command 'login' to login, or 'cancel' to cancel." << endl;
            } else if (userInput == "cancel"){
                break;
            } else {
                cout << "System doesn't understand what you want to do.\nPlease enter command 'login' to login, or 'cancel' to cancel.\n> ";
            }
        }
    }

    while(loggedIn == true && loggedOut == false){
        if ((userType != "AA") || (userType != "FS") || (userType != "BS") || (userType != "SS")){
            bool users = userMenu(userLogName, userBalance, userType);
            if (users == true){ //true means log out is called
                uploadUpdates("00 " + userLogName + spaceFiller(15, " ", userLogName) + " " + userType + " " + spaceFiller(9, "0", userBalance) + userBalance + "\n","files/userDailyUpdate.txt");
                loggedOut = true;
                break;
            }
        }
    }

    cout << "Good bye" << endl;
    //Before system stops, we have to push whats inside userDailyUpdate.txt to dailyUpdate.txt, then delete that userDailyUpdate.txt
    string userDailyInsides, dailyUpdateInsides, line;
    ifstream fileIn ("files/userDailyUpdate.txt");
    while (getline(fileIn,line)){
        userDailyInsides += line + "\n";
    }
    fileIn.close();
    line = "";

    fileIn.open("files/dailyUpdate.txt");
    while (getline(fileIn,line)){
        dailyUpdateInsides += line + "\n";
    }
    fileIn.close();

    ofstream fileOut ("files/dailyUpdate.txt");
    fileOut << dailyUpdateInsides + userDailyInsides;
    fileOut.close();

    remove("files/userDailyUpdate.txt");

    return 0;
}
