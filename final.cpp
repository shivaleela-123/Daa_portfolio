#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits>
#include <queue>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>


using namespace std;
// Structure to represent a location with coordinates and an address
struct Location {
    double x, y;        // x and y coordinates
    string address;     // Address of the location
};

// Structure to represent a driver with their details
struct Driver {
    string name;         // Name of the driver
    double maxCapacity;  // Maximum load capacity
    double currentCapacity; // Current load
    Location location;   // Current location of the driver
};

// Structure to represent a delivery with its details
struct Delivery {
    Location location;   // Delivery location
    double weight;       // Weight of the delivery
    string status;       // Status of the delivery (e.g., "Pending")
};

// Utility function to calculate the Euclidean distance between two locations
double calculateDistance(Location a, Location b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Function to insert a new city into the system
void insertCity(vector<Location>& cities) {
    Location newCity;

    cout << "Enter the coordinates of the city (x y): ";
    cin >> newCity.x >> newCity.y; // Input city coordinates

    cout << "Enter the name of the city: ";
    cin.ignore();

    getline(cin, newCity.address); // Input city address

    cities.push_back(newCity); // Add city to the list
    cout << "City added successfully!\n";
}

// Function to insert a new driver into the system
void insertDriver(vector<Driver>& drivers) {
    Driver newDriver;

    cout << "Enter the driver's name: ";
    cin.ignore();

    getline(cin, newDriver.name); // Input driver's name
    cout << "Enter the driver's maximum capacity: ";
    cin >> newDriver.maxCapacity; // Input max capacity

    cout << "Enter the driver's current capacity: ";
    cin >> newDriver.currentCapacity; // Input current capacity

    cout << "Enter the driver's location (x y): ";
    cin >> newDriver.location.x >> newDriver.location.y; // Input location coordinates

    cout << "Enter the address of the location: ";
    cin.ignore();

    getline(cin, newDriver.location.address); // Input location address
    drivers.push_back(newDriver); // Add driver to the list

    cout << "Driver added successfully!\n";
}

// Function to insert a new delivery into the system
void insertDelivery(vector<Delivery>& deliveries)
 {
    Delivery newDelivery;

    cout << "Enter the delivery location coordinates (x y): ";
    cin >> newDelivery.location.x >> newDelivery.location.y; // Input delivery location

    cout << "Enter the delivery location address: ";
    cin.ignore();

    getline(cin, newDelivery.location.address); // Input location address
    cout << "Enter the weight of the delivery: ";
    cin >> newDelivery.weight; // Input weight

    newDelivery.status = "Pending"; // Set initial status
    deliveries.push_back(newDelivery); // Add delivery to the list

    cout << "Delivery added successfully!\n";
}

// Function to display distances of all cities from the warehouse
void case1(const vector<Location>& cities)
 {
    cout << "Available cities and their distances from Warehouse: \n";
    Location warehouse = cities[0]; // Assume the first city is the warehouse

    for (int i = 1; i < cities.size(); ++i) {
        double distance = calculateDistance(warehouse, cities[i]); // Calculate distance
        cout << cities[i].address << ": " << distance << " km" << endl;
    }
}

// Function to calculate the shortest distance and time between two cities using Prim's Algorithm
void case2(const vector<Location>& cities)
 {
    cout << "Available cities: \n";
    for (int i = 0; i < cities.size(); ++i) {
        cout << i + 1 << ". " << cities[i].address << endl;
    }
