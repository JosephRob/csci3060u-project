#include "showMenu.h"
#include <iostream>
#include <string>

//this is the show menu function, it takes userType as argument
//to show the correct menu.
void showMenu(string userType){
    cout << "\nMenus: " << endl;
    if (userType == "FS"){
        cout << "add = Add balance" << endl;
        cout << "advertise = Advertise an item" << endl;
        cout << "bid = Bid on an item" << endl;
    } else if (userType == "BS"){
        cout << "add = Add balance" << endl;
        cout << "bid = Bid on an item" << endl;
    } else if (userType == "SS"){
        cout << "advertise = Advertise an item" << endl;
    } else if (userType == "AA"){
        cout << "add = Add balance" << endl;
        cout << "advertise = Advertise an item" << endl;
        cout << "bid = Bid on an item" << endl;
        cout << "create = Create new user" << endl;
        cout << "delete = Delete a user" << endl;
        cout << "refund = Refund an item\n" << endl;
    }
    cout << "list = List all items available\n" << endl;
    cout << "logout = Log out" << endl;
}
