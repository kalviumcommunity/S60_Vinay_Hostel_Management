#include <iostream>
#include <vector>
using namespace std;

// Abstract class for Room
class Room {
protected:
    string bedType;
    int maxOccupancy;

public:
    Room(string type, int occupancy) : bedType(type), maxOccupancy(occupancy) {}

    virtual void displayRoomDetails() const {
        cout << "Bed type: " << bedType << "\n"
             << "Max occupancy: " << maxOccupancy << "\n";
    }

    virtual ~Room() {}
};

// Derived class for Single Room
class SingleRoom : public Room {
public:
    SingleRoom() : Room("Single", 1) {}

    void displayRoomDetails() const override {
        cout << "Single Room - ";
        Room::displayRoomDetails();
    }
};

// Derived class for Double Room
class DoubleRoom : public Room {
public:
    DoubleRoom() : Room("Double", 2) {}

    void displayRoomDetails() const override {
        cout << "Double Room - ";
        Room::displayRoomDetails();
    }
};

// New derived class for Deluxe Room (Extension)
class DeluxeRoom : public Room {
public:
    DeluxeRoom() : Room("Deluxe", 3) {}

    void displayRoomDetails() const override {
        cout << "Deluxe Room - ";
        Room::displayRoomDetails();
    }
};

// Class responsible for managing statistics of hostels and booked rooms
class HostelStats {
private:
    static int totalHostels;
    static int totalBookedRooms;

public:
    static void incrementTotalHostels() {
        totalHostels++;
    }

    static void decrementTotalHostels() {
        totalHostels--;
    }

    static void incrementTotalBookedRooms() {
        totalBookedRooms++;
    }

    static void decrementTotalBookedRooms() {
        totalBookedRooms--;
    }

    static void displayStats() {
        cout << "Total hostels: " << totalHostels << "\n";
        cout << "Total booked rooms: " << totalBookedRooms << "\n";
    }
};

int HostelStats::totalHostels = 0;
int HostelStats::totalBookedRooms = 0;

// Abstract class for Hostels
class Hostels {
private:
    string hostelName;
    int noOfRooms;
    Room* roomType;
    bool isBooked;

public:
    Hostels(string name, int rooms, Room* room, bool bookedStatus)
        : hostelName(name), noOfRooms(rooms), roomType(room), isBooked(bookedStatus) {
        HostelStats::incrementTotalHostels(); // Keep track of total hostels
    }

    virtual ~Hostels() {
        HostelStats::decrementTotalHostels();
        if (isBooked) {
            HostelStats::decrementTotalBookedRooms();
        }
        delete roomType;
    }

    string getHostelName() const { return hostelName; }
    int getNoOfRooms() const { return noOfRooms; }
    bool getIsBooked() const { return isBooked; }

    void setHostelName(const string& name) { hostelName = name; }
    void setNoOfRooms(int rooms) { noOfRooms = rooms; }
    void setIsBooked(bool bookedStatus) { isBooked = bookedStatus; }

    bool isAvailable() const {
        return !isBooked && noOfRooms > 0;
    }

    bool bookRoom() {
        if (isAvailable()) {
            cout << "Room successfully booked at " << hostelName << "\n";
            noOfRooms--;
            HostelStats::incrementTotalBookedRooms();
            if (noOfRooms == 0) {
                isBooked = true;
            }
            return true;
        } else {
            cout << "No available rooms at " << hostelName << "\n";
            return false;
        }
    }

    virtual void displayHostel() const = 0;
};

// Derived class for MensHostel
class MensHostel : public Hostels {
public:
    MensHostel(string name, int rooms, Room* room, bool bookedStatus)
        : Hostels(name, rooms, room, bookedStatus) {}

    void displayHostel() const override {
        cout << "Mens Hostel - ";
    }
};

// Derived class for LadiesHostel
class LadiesHostel : public Hostels {
public:
    LadiesHostel(string name, int rooms, Room* room, bool bookedStatus)
        : Hostels(name, rooms, room, bookedStatus) {}

    void displayHostel() const override {
        cout << "Ladies Hostel - ";
    }
};

// New derived class for VIP Hostel (Extension)
class VIPHostel : public Hostels {
public:
    VIPHostel(string name, int rooms, Room* room, bool bookedStatus)
        : Hostels(name, rooms, room, bookedStatus) {}

    void displayHostel() const override {
        cout << "VIP Hostel - ";
    }
};

// User class responsible for booking hostels
class User {
private:
    string userName;
    vector<Hostels*> bookedHostels;

public:
    User(string name) : userName(name) {}

    string getUserName() const { return userName; }

    vector<Hostels*> getBookedHostels() const { return bookedHostels; }

    void bookHostel(Hostels* hostel) {
        if (hostel->bookRoom()) {
            bookedHostels.push_back(hostel);
            cout << userName << " successfully booked a room at " << hostel->getHostelName() << endl;
        }
    }

    void bookRoomByType(Hostels* hostel, Room* room) {
        if (hostel->bookRoom()) {
            bookedHostels.push_back(hostel);
            cout << userName << " successfully booked a " << room->displayRoomDetails() << " at " << hostel->getHostelName() << endl;
        }
    }
};

int main() {
    const int numHostels = 5;
    Hostels* hostels[numHostels];

    Room* room1 = new SingleRoom();
    Room* room2 = new DoubleRoom();
    Room* room3 = new DeluxeRoom(); // New type of room

    hostels[0] = new MensHostel("Mens hotel 1", 50, room1, false);
    hostels[1] = new MensHostel("Mens hotel 2", 1, room2, false);
    hostels[2] = new LadiesHostel("Ladies hotel 1", 20, room2, true);
    hostels[3] = new MensHostel("Mens hotel 3", 10, room1, false);
    hostels[4] = new VIPHostel("VIP hotel 1", 5, room3, false); // New type of hostel

    for (int i = 0; i < numHostels; ++i) {
        cout << "Displaying hostel capacities fully:\n";
        hostels[i]->displayHostel();
    }
    
    User user1("John Doe");

    for (int i = 0; i < numHostels; ++i) {
        cout << "Attempting to book a room in " << (hostels[i]->isAvailable() ? "available hostel" : "unavailable hostel") << endl;
        user1.bookRoomByType(hostels[i], room1);
    }

    for (int i = 0; i < numHostels; ++i) {
        cout << "Displaying updated hostel details:\n";
        hostels[i]->displayHostel();
    }

    HostelStats::displayStats();

    for (int i = 0; i < numHostels; ++i) {
        delete hostels[i]; 
    }

    return 0;
}