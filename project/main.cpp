//
//  main.cpp
//  3060Proj
//
//  Created by Clyve Widjaya on 29/01/18.
//  Copyright © 2018 Clyve Widjaya. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <sstream>
#include "functions/showMenu/showMenu.h"
#include "functions/advertise/advertise.h"
#include "functions/bid/bid.h"
#include "functions/create/create.h"
#include "functions/addCredit/addCredit.h"
#include "functions/refund/refund.h"
#include "functions/delete/delete.h"

using namespace std;

//HELPER FUNCTIONS
string spaceFiller(int totChar, string filler, string word){
    string fill;
    for (int i = 0; i < (totChar-word.length());i++){
        fill += filler;
    }
    return fill;
}

void prompt(string users, string mode){
    cout << "\nYour account type does not support " + mode + "."<< endl;
    cout << "Only " + users + " support this option." << endl;
}

vector<string> checkUser(string userInput){
    string line, word;
    ifstream inFile ("files/userList.txt");
    vector<string> toReturn;
    while (!inFile.eof()){
        getline(inFile, line);
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

bool userMenu(string userLogName, string userBalance, string userType){
    bool keepGoing = true;
    string menuInput;
    cout << "\nWelcome to the auction, " + userLogName + "!" << endl;
    cout << "Type: " + userType + "\tBalance: $" + userBalance << endl;
    showMenu(userType);
    while (keepGoing == true){
        cout << "What would you like? (Type 'menu' to display menu) ";
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
                cout << "Output: " + addCredit(userLogName, userBalance, userType) << endl;
                //Take the return value from calling addCredit and make a line to be
                //recorded to userDailyUpdate file
            } else {
                prompt("Admin or Full-Standard or Buy-Standard","add credit");
                showMenu(userType);
            }
        } else if (menuInput == "advertise"){
            if (userType != "BS"){
                //call advertise function
                cout << "Output: " + advertise() << endl;
                //Take the return value from calling advertise and make a line to be
                //recorded to userDailyUpdate file
            } else {
                prompt("Admin or Full-Standard or Sell-Standard","advertise");
                showMenu(userType);
            }
        } else if (menuInput == "bid") {
            if (userType != "SS"){
                //call bid function
                cout << "Output: " + bid(userLogName) << endl;
                //Take the return value from calling bid and make a line to be
                //recorded to userDailyUpdate file
            } else {
                prompt("Admin or Full-Standard or Buy-Standard","bidding");
                showMenu(userType);
            }
        } else if (menuInput == "create"){
            if (userType == "AA"){
                //call create function
                cout << "Output: " + create(userLogName) << endl;
                //Take the return value from calling create and make a line to be
                //recorded to userDailyUpdate file
            } else {
                prompt("Admin","create");
                showMenu(userType);
            }
        } else if (menuInput == "delete"){
            if (userType == "AA"){
                //call delete function
                cout << "Output: " + deleteUser(userLogName) << endl;
                //Take the return value from calling deleteUser and make a line to be
                //recorded to userDailyUpdate file
            } else {
                prompt("Admin","delete");
                showMenu(userType);
            }
        } else if (menuInput == "refund"){
            if (userType == "AA"){
                //call refund function
                cout << "Output: " + refund() << endl;
                //Take the return value from calling refund and make a line to be
                //recorded to userDailyUpdate file
            } else {
                prompt("Admin","refund");
                showMenu(userType);
            }
        } else if (menuInput == "logout") {
            return true; //done
        } else {
            cout << "Wrong input, please re-input!" << endl;
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
    string funcs[] = {"advertise", "bid", "create", "delete", "refund", "add"};

    //user info
    string userLogName, userType, userBalance;

    cout << "Enter command 'login' to login, or 'cancel' to cancel\n> ";
    while(loggedIn == false){
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
                        //everytime login is successfull, create userDailyUpdate. userDailyUpdate file is temporary. Will be deleted after user is logged out, before the system stops.
                        uploadUpdates("10 " + userLogName + spaceFiller(15, " ", userLogName) + " " + userType + " " + spaceFiller(9, "0", userBalance) + userBalance + "\n","files/userDailyUpdate.txt");
                        break;
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
            if (users == true){ //true means logged out is called
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
