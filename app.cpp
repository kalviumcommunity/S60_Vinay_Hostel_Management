#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
using namespace std;


//
//  learn.cpp
//  CPP
//
//  Created by Vinnu Gollakoti on 29/08/24.
//

class Hostel{
private:
    string hostelName;
    int roomNumber;
    string betType;
    
    
public:
    void check() {
        cout << "Hello, Room are available in this hostel" << endl;
    }
};

class User {
private:
    string name;
    int id;
public:
    void bookRoom(int id) {
        cout << "I want a room in your hostel with " << id << " room number." << endl;
    }
};

int main() {
    Hostel mh3;
    User Vinay;
    
    mh3.check();
    Vinay.bookRoom(26);
    return 0;
}
