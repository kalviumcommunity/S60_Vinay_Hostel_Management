#include <iostream>
#include <vector>
using namespace std;

class Hostels {
private:
    string hostelName;
    int noOfRooms;
    string bedType;
    bool isBooked;

    static int totalHostels;
    static int totalBookedRooms;

public:
    Hostels() : hostelName(""), noOfRooms(0), bedType(""), isBooked(false) {
        totalHostels++;
    }

    Hostels(string name, int rooms, string type, bool bookedStatus)
        : hostelName(name), noOfRooms(rooms), bedType(type), isBooked(bookedStatus) {
        totalHostels++;
    }

    ~Hostels() {
        totalHostels--;
        if (isBooked) {
            totalBookedRooms--;
        }
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
            cout << "Room successfully booked at " << hostelName << "\n";
            noOfRooms -= 1;
            totalBookedRooms++;
            if (noOfRooms == 0) {
                isBooked = true;
            }
            return true;
        } else {
            cout << "No available rooms at " << hostelName << "\n";
            return false;
        }
    }

    static void displayStats() {
        cout << "Total hostels: " << totalHostels << "\n";
        cout << "Total booked rooms: " << totalBookedRooms << "\n";
    }
};

int Hostels::totalHostels = 0;
int Hostels::totalBookedRooms = 0;

class User {
private:
    string userName;
    vector<Hostels*> bookedHostels;
};

int main() {
    const int numHostels = 3;
        Hostels* hostels[numHostels];
        
        hostels[0] = new Hostels("Mens hotel 1", 50, "Single", false);
        hostels[1] = new Hostels("Mens hotel 2", 1, "Double", false);
        hostels[2] = new Hostels("Ladies hotel 1", 20, "Double", true);
        
        for (int i = 0; i < numHostels; ++i) {
            cout << "Displaying hostel capacities fully \n";
            hostels[i]->displayHostel();
        }
        
        for (int i = 0; i < numHostels; ++i) {
            cout << "Attempting to book a room in " << (hostels[i]->isAvailable() ? "available hostel" : "unavailable hostel") << endl;
            hostels[i]->bookRoom();
        }
        
        for (int i = 0; i < numHostels; ++i) {
            cout << "Displaying of rooms available in each hostels \n";
            hostels[i]->displayHostel();
        }

        for (int i = 0; i < numHostels; ++i) {
            cout << "Attempting to book a room in " << (hostels[i]->isAvailable() ? "available hostel" : "unavailable hostel") << endl;
            hostels[i]->bookRoom();
        }
        Hostels::displayStats();
        for (int i = 0; i < numHostels; ++i) {
            delete hostels[i];
        }

        return 0;
    }
