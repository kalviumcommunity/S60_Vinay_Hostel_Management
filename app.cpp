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

// Abstract class for Hostels (Abstract because it has a pure virtual function)
class Hostels {
private:
    string hostelName;
    int noOfRooms;
    Room* roomType;
    bool isBooked;

    static int totalHostels;
    static int totalBookedRooms;

public:
    // Constructor for Hostel
    Hostels(string name, int rooms, Room* room, bool bookedStatus)
        : hostelName(name), noOfRooms(rooms), roomType(room), isBooked(bookedStatus) {
        totalHostels++;
        if (isBooked) {
            totalBookedRooms++;
        }
    }

    // Destructor to manage static variables
    virtual ~Hostels() {
        totalHostels--;
        if (isBooked) {
            totalBookedRooms--;
        }
        delete roomType;  // Deleting dynamically allocated room
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

    // Overloaded bookRoom method (Polymorphism: Function Overloading)
    bool bookRoom(Room* room) {
        if (room && isAvailable()) {
            cout << "Room of type " << room->displayRoomDetails() << " booked at " << hostelName << "\n";
            noOfRooms--;
            totalBookedRooms++;
            if (noOfRooms == 0) {
                isBooked = true;
            }
            return true;
        } else {
            cout << "No available rooms of this type at " << hostelName << "\n";
            return false;
        }
    }

    // Pure virtual function (makes Hostels an abstract class)
    virtual void displayHostel() const = 0;

    static void displayStats() {
        cout << "Total hostels: " << totalHostels << "\n";
        cout << "Total booked rooms: " << totalBookedRooms << "\n";
    }
};

int Hostels::totalHostels = 0;
int Hostels::totalBookedRooms = 0;

// Derived class for MensHostel
class MensHostel : public Hostels {
public:
    MensHostel(string name, int rooms, Room* room, bool bookedStatus)
        : Hostels(name, rooms, room, bookedStatus) {}

    // Overriding the pure virtual function
    void displayHostel() const override {
        cout << "Mens Hostel - ";
        Hostels::displayHostel();
    }
};

// Derived class for LadiesHostel
class LadiesHostel : public Hostels {
public:
    LadiesHostel(string name, int rooms, Room* room, bool bookedStatus)
        : Hostels(name, rooms, room, bookedStatus) {}

    // Overriding the pure virtual function
    void displayHostel() const override {
        cout << "Ladies Hostel - ";
        Hostels::displayHostel();
    }
};

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

    // Method to book a specific type of room
    void bookRoomByType(Hostels* hostel, Room* room) {
        if (hostel->bookRoom(room)) {
            bookedHostels.push_back(hostel);
            cout << userName << " successfully booked a " << room->displayRoomDetails() << " at " << hostel->getHostelName() << endl;
        }
    }
};

int main() {
    const int numHostels = 4;
    Hostels* hostels[numHostels];

    // Create rooms first
    Room* room1 = new SingleRoom();
    Room* room2 = new DoubleRoom();

    // Using the derived classes (MensHostel, LadiesHostel) to create hostels
    hostels[0] = new MensHostel("Mens hotel 1", 50, room1, false);
    hostels[1] = new MensHostel("Mens hotel 2", 1, room2, false);
    hostels[2] = new LadiesHostel("Ladies hotel 1", 20, room2, true);
    hostels[3] = new MensHostel("Mens hotel 3", 10, room1, false);

    // Displaying the details using accessor methods
    for (int i = 0; i < numHostels; ++i) {
        cout << "Displaying hostel capacities fully:\n";
        hostels[i]->displayHostel();
    }
    
    User user1("John Doe");

    // Trying to book rooms using the overloaded function (Polymorphism: Function Overloading)
    for (int i = 0; i < numHostels; ++i) {
        cout << "Attempting to book a room in " << (hostels[i]->isAvailable() ? "available hostel" : "unavailable hostel") << endl;
        user1.bookRoomByType(hostels[i], room1);  // Booking a Single Room type specifically
    }

    // Displaying updated hostel details
    for (int i = 0; i < numHostels; ++i) {
        cout << "Displaying updated hostel details:\n";
        hostels[i]->displayHostel();
    }

    Hostels::displayStats();

    // Cleanup
    for (int i = 0; i < numHostels; ++i) {
        delete hostels[i];
    }

    return 0;
}
