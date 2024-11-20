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

// Liskov Substitution Principle Test
void testLSP() {
    // We can substitute any derived class (SingleRoom, DoubleRoom, DeluxeRoom) for Room
    Room* room1 = new SingleRoom();
    Room* room2 = new DoubleRoom();
    Room* room3 = new DeluxeRoom(); // New type of room
    
    // Creating hostels with different room types
    Hostels* hostel1 = new MensHostel("Mens Hotel 1", 10, room1, false);
    Hostels* hostel2 = new LadiesHostel("Ladies Hotel 1", 20, room2, false);
    Hostels* hostel3 = new VIPHostel("VIP Hotel 1", 5, room3, false); // New type of hostel

    // **Liskov Substitution Principle in action**:
    // We are able to substitute any derived type (MensHostel, LadiesHostel, VIPHostel) for Hostels
    hostel1->bookRoom(); // Works with MensHostel, as it is a derived class of Hostels
    hostel2->bookRoom(); // Works with LadiesHostel
    hostel3->bookRoom(); // Works with VIPHostel, which is a new derived class of Hostels

    // Deleting dynamically allocated objects
    delete hostel1;
    delete hostel2;
    delete hostel3;
}

int main() {
    // Run LSP test to demonstrate Liskov Substitution Principle
    testLSP();
    
    // Displaying hostel statistics
    HostelStats::displayStats();

    return 0;
}
