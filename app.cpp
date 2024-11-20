#include <iostream>
#include <vector>
using namespace std;

// Abstract class for Room
// SRP: The Room class is solely responsible for managing room details.
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
// SRP: The SingleRoom class is responsible only for the details specific to a Single Room.
class SingleRoom : public Room {
public:
    SingleRoom() : Room("Single", 1) {}

    void displayRoomDetails() const override {
        cout << "Single Room - ";
        Room::displayRoomDetails();
    }
};

// Derived class for Double Room
// SRP: The DoubleRoom class is responsible only for the details specific to a Double Room.
class DoubleRoom : public Room {
public:
    DoubleRoom() : Room("Double", 2) {}

    void displayRoomDetails() const override {
        cout << "Double Room - ";
        Room::displayRoomDetails();
    }
};

// Class responsible for managing statistics of hostels and booked rooms
// SRP: The HostelStats class is solely responsible for tracking and displaying hostel statistics.
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
// SRP: The Hostels class is responsible for booking rooms, managing room availability, and related operations.
class Hostels {
private:
    string hostelName;
    int noOfRooms;
    Room* roomType;
    bool isBooked;

public:
    // Constructor for Hostel
    Hostels(string name, int rooms, Room* room, bool bookedStatus)
        : hostelName(name), noOfRooms(rooms), roomType(room), isBooked(bookedStatus) {
        HostelStats::incrementTotalHostels(); // Keep track of total hostels
    }

    // Destructor to manage static variables and delete room objects
    // SRP: The Hostels class is responsible for its own destruction and clean-up.
    virtual ~Hostels() {
        HostelStats::decrementTotalHostels();  // Decrement total hostels on deletion
        if (isBooked) {
            HostelStats::decrementTotalBookedRooms(); // Decrement booked rooms on deletion
        }
        delete roomType;  // Delete dynamically allocated room
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

    // Booking a room at the hostel
    // SRP: The Hostels class is responsible for the booking logic and availability checking.
    bool bookRoom() {
        if (isAvailable()) {
            cout << "Room successfully booked at " << hostelName << "\n";
            noOfRooms--;
            HostelStats::incrementTotalBookedRooms(); // Update booked rooms
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
    // SRP: Handles booking rooms based on room type.
    bool bookRoom(Room* room) {
        if (room && isAvailable()) {
            cout << "Room of type " << room->displayRoomDetails() << " booked at " << hostelName << "\n";
            noOfRooms--;
            HostelStats::incrementTotalBookedRooms(); // Update booked rooms
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
    // SRP: The Hostels class is responsible for providing an interface for its derived classes.
    virtual void displayHostel() const = 0;
};

// Derived class for MensHostel
// SRP: The MensHostel class is responsible for representing the details of a men's hostel.
class MensHostel : public Hostels {
public:
    MensHostel(string name, int rooms, Room* room, bool bookedStatus)
        : Hostels(name, rooms, room, bookedStatus) {}

    // Overriding the pure virtual function
    // SRP: The MensHostel class provides specific implementation for displaying hostel details.
    void displayHostel() const override {
        cout << "Mens Hostel - ";
    }
};

// Derived class for LadiesHostel
// SRP: The LadiesHostel class is responsible for representing the details of a ladies' hostel.
class LadiesHostel : public Hostels {
public:
    LadiesHostel(string name, int rooms, Room* room, bool bookedStatus)
        : Hostels(name, rooms, room, bookedStatus) {}

    // Overriding the pure virtual function
    // SRP: The LadiesHostel class provides specific implementation for displaying hostel details.
    void displayHostel() const override {
        cout << "Ladies Hostel - ";
    }
};

// User class responsible for booking hostels
// SRP: The User class is responsible for managing the user's booking process.
class User {
private:
    string userName;
    vector<Hostels*> bookedHostels;

public:
    User(string name) : userName(name) {}

    string getUserName() const { return userName; }

    vector<Hostels*> getBookedHostels() const { return bookedHostels; }

    // SRP: The User class is responsible for booking hostels, not managing the hostel's internal details.
    void bookHostel(Hostels* hostel) {
        if (hostel->bookRoom()) {
            bookedHostels.push_back(hostel);
            cout << userName << " successfully booked a room at " << hostel->getHostelName() << endl;
        }
    }

    // SRP: The User class is responsible for booking rooms of specific types at a hostel.
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

    HostelStats::displayStats();

    // Cleanup
    for (int i = 0; i < numHostels; ++i) {
        delete hostels[i];  // Clean up allocated memory
    }

    return 0;
}