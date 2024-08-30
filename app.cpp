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

    Hostels(string name, int rooms,string type, bool bookedStatus) {
            hostelName = name;
            noOfRooms = rooms;
            bedType = type;
            isBooked = bookedStatus;
        }

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
    const int numHostels = 3;
    Hostels* hostels[numHostels];
    
    hostels[0] = new Hostels("Mens hotel 1", 50, "Single", false);
    hostels[1] = new Hostels("Mens hotel 2", 30, "Double", false);
    hostels[2] = new Hostels("Ladies hotel 1", 20, "Double", true);

    for (int i = 0; i < numHostels; ++i) {
        hostels[i]->displayHostel();
    }
    for (int i = 0; i < numHostels; ++i) {
        cout << "Attempting to book a room in " << (hostels[i]->isAvailable() ? "available hostel" : "unavailable hostel") << endl;
        hostels[i]->bookRoom();
    }
    for (int i = 0; i < numHostels; ++i) {
        delete hostels[i];
    }

    return 0;
}
