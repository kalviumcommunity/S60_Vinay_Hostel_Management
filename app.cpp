#include <iostream>
using namespace std;

class Hostels {
private:
    string hostelName;
    int noOfRooms;
    string bedType;
    bool isBooked;

public:
    Hostels() : hostelName(""), noOfRooms(0), bedType(""), isBooked(false) {}
    
    Hostels(string name, int rooms, string type, bool bookedStatus)
        : hostelName(name), noOfRooms(rooms), bedType(type), isBooked(bookedStatus) {}

    
    void uploadHostel(string name, int rooms, string type, bool bookedStatus) {
        hostelName = name;
        noOfRooms = rooms;
        bedType = type;
        isBooked = bookedStatus;
        cout << "Hostel details updated:\n";
        displayHostel();
    }

    
    void displayHostel() const {
        cout << "Hostel name: " << hostelName << "\n"
             << "Number of rooms: " << noOfRooms << "\n"
             << "Bed type: " << bedType << "\n"
             << "Booked status: " << (isBooked ? "Booked" : "Available") << "\n";
    }

    
    bool isAvailable() const {
        return !isBooked && noOfRooms > 0;
    }

    
    bool bookRoom() {
        if (isAvailable()) {
            isBooked = true;
            cout << "Room successfully booked at " << hostelName << "\n";
            return true;
        } else {
            cout << "No available rooms at " << hostelName << "\n";
            return false;
        }
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
        Hostels hostels[3] = {
            Hostels("Mens hostel 1", 50, "Single", false),
            Hostels("Mens hostel 2", 30, "Double", false),
            Hostels("Ladies hostel 1", 20, "Triple", true)
        };
        for (int i = 0; i < 3; ++i) {
            hostels[i].displayHostel();
        }
        for (int i = 0; i < 3; ++i) {
            cout << "Attempting to book a room in " << hostels[i].isAvailable() << endl;
            hostels[i].bookRoom();
        }
    
    return 0;
}