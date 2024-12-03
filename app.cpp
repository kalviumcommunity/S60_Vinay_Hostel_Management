#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;

class Hostel {
private:
    string hostelName;
    int roomNumber;
    string bedType;
public:
    void check() {
        cout << "Hello, Rooms are available in this hostel" << endl;
        cout << "This is the hostel object at address: " << this << endl;
    }
};

class User {
private:
    string name;
    int id;
public:
    void bookRoom(int id) {
        cout << "I want a room in your hostel with room number " << id << "." << endl;
        cout << "This is the user object at address: " << this << endl;
    }
};

int main() {
    Hostel *mh3 = new Hostel;
    User *Vinay = new User;
    
    mh3->check(); 
    Vinay->bookRoom(26); 
    
    delete mh3;
    delete Vinay;
    
    return 0;
}
