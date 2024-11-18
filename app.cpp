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
        if (isBooked) {
            totalBookedRooms++;
        }
    }

    // Destructor
    ~Hostels() {
        totalHostels--;
        if (isBooked) {
            totalBookedRooms--;
        }
    }

    string getHostelName() const { return hostelName; }
    void setHostelName(const string& name) { hostelName = name; }

    int getNoOfRooms() const { return noOfRooms; }
    void setNoOfRooms(int rooms) { noOfRooms = rooms; }

    string getBedType() const { return bedType; }
    void setBedType(const string& type) { bedType = type; }

    bool getIsBooked() const { return isBooked; }
    void setIsBooked(bool bookedStatus) { isBooked = bookedStatus; }

    // Method to update hostel details
    void uploadHostel(string name, int rooms, string type, bool bookedStatus) {
        setHostelName(name);
        setNoOfRooms(rooms);
        setBedType(type);
        setIsBooked(bookedStatus);
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

public:
    User(string name) : userName(name) {}

    // Accessor and Mutator Methods for User Name
    string getUserName() const { return userName; }
    void setUserName(const string& name) { userName = name; }

    // Accessor Method for Booked Hostels (no mutator needed here, so only getter)
    vector<Hostels*> getBookedHostels() const { return bookedHostels; }

    // Method to book a hostel for the user
    void bookHostel(Hostels* hostel) {
        if (hostel->bookRoom()) {
            bookedHostels.push_back(hostel);
            cout << userName << " successfully booked a room at " << hostel->getHostelName() << endl;
        }
    }
};

int main() {
    const int numHostels = 3;
    Hostels* hostels[numHostels];
    
    // Using the mutator methods to set initial values
    hostels[0] = new Hostels("Mens hotel 1", 50, "Single", false);
    hostels[1] = new Hostels("Mens hotel 2", 1, "Double", false);
    hostels[2] = new Hostels("Ladies hotel 1", 20, "Double", true);

    // Displaying the details using accessor methods
    for (int i = 0; i < numHostels; ++i) {
        cout << "Displaying hostel capacities fully:\n";
        hostels[i]->displayHostel();
    }
    
    User user1("John Doe");

    for (int i = 0; i < numHostels; ++i) {
        cout << "Attempting to book a room in " << (hostels[i]->isAvailable() ? "available hostel" : "unavailable hostel") << endl;
        user1.bookHostel(hostels[i]);
    }

    for (int i = 0; i < numHostels; ++i) {
        cout << "Displaying updated hostel details:\n";
        hostels[i]->displayHostel();
    }

    Hostels::displayStats();

    for (int i = 0; i < numHostels; ++i) {
        delete hostels[i];
    }
    return 0;
}
