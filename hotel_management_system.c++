#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Room class to represent individual rooms in the hotel
class Room {
public:
    int roomNumber;
    string roomType;
    double price;
    bool isBooked;

    Room(int number, string type, double cost)
        : roomNumber(number), roomType(type), price(cost), isBooked(false) {}

    void displayDetails() const {
        cout << "Room Number: " << roomNumber
             << ", Type: " << roomType
             << ", Price: $" << price
             << ", Status: " << (isBooked ? "Booked" : "Available") << endl;
    }
};

// Customer class to represent booking details
class Customer {
public:
    string name;
    int roomNumber;

    Customer(string customerName, int roomNum)
        : name(customerName), roomNumber(roomNum) {}
};

// Hotel class to manage rooms and bookings
class Hotel {
private:
    vector<Room> rooms;
    vector<Customer> customers;

public:
    Hotel() {
        // Initializing some rooms
        rooms.push_back(Room(101, "Single", 100.0));
        rooms.push_back(Room(102, "Double", 150.0));
        rooms.push_back(Room(103, "Suite", 250.0));
        rooms.push_back(Room(104, "Double", 150.0));
        rooms.push_back(Room(105, "Suite", 250.0));
    }

    void displayAvailableRooms() const {
        cout << "\nAvailable Rooms:\n";
        for (const auto& room : rooms) {
            if (!room.isBooked) {
                room.displayDetails();
            }
        }
    }

    void bookRoom() {
        string customerName;
        int roomNumber;

        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, customerName);

        cout << "Enter room number to book: ";
        cin >> roomNumber;

        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber) {
                if (room.isBooked) {
                    cout << "Error: Room is already booked.\n";
                    return;
                }
                room.isBooked = true;
                customers.push_back(Customer(customerName, roomNumber));
                cout << "Room " << roomNumber << " successfully booked for " << customerName << ".\n";
                return;
            }
        }
        cout << "Error: Room number " << roomNumber << " does not exist.\n";
    }

    void checkoutRoom() {
        int roomNumber;
        cout << "Enter room number to checkout: ";
        cin >> roomNumber;

        for (size_t i = 0; i < customers.size(); ++i) {
            if (customers[i].roomNumber == roomNumber) {
                for (auto& room : rooms) {
                    if (room.roomNumber == roomNumber) {
                        room.isBooked = false;
                        break;
                    }
                }
                cout << "Room " << roomNumber << " successfully checked out for " << customers[i].name << ".\n";
                customers.erase(customers.begin() + i);
                return;
            }
        }
        cout << "Error: Room " << roomNumber << " is not currently booked.\n";
    }

    void displayBookings() const {
        cout << "\nCurrent Bookings:\n";
        if (customers.empty()) {
            cout << "No bookings at the moment.\n";
            return;
        }
        for (const auto& customer : customers) {
            cout << "Customer Name: " << customer.name
                 << ", Room Number: " << customer.roomNumber << endl;
        }
    }
};

int main() {
    Hotel hotel;
    int choice;

    do {
        cout << "\n--- Hotel Booking Management System ---\n";
        cout << "1. Display Available Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. Checkout a Room\n";
        cout << "4. View All Bookings\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.displayAvailableRooms();
                break;
            case 2:
                hotel.bookRoom();
                break;
            case 3:
                hotel.checkoutRoom();
                break;
            case 4:
                hotel.displayBookings();
                break;
            case 5:
                cout << "Thank you for using the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
