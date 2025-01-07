#include <iostream>
#include <vector>

using namespace std;

// Function to check if the vehicle can afford the weight
bool canAffordWeight(int maxCapacity, int currentWeight, int totalWeight) {
    return currentWeight + totalWeight <= maxCapacity;
}

// Function to add a passenger to the vehicle
bool addPassenger(int& currentWeight, int maxCapacity, vector<int>& passengerWeights, int weight) {
    if (currentWeight + weight <= maxCapacity) {
        passengerWeights.push_back(weight);
        currentWeight += weight;
        cout << "Passenger with weight " << weight << " added successfully.\n";
        return true;
    } else {
        cout << "Cannot add passenger. Vehicle capacity exceeded.\n";
        return false;
    }
}

// Function to remove a passenger from the vehicle
bool removePassenger(int& currentWeight, vector<int>& passengerWeights, int weight) {
    for (auto it = passengerWeights.begin(); it != passengerWeights.end(); ++it) {
        if (*it == weight) {
            passengerWeights.erase(it);
            currentWeight -= weight;
            cout << "Passenger with weight " << weight << " removed successfully.\n";
            return true;
        }
    }
    cout << "Passenger with weight " << weight << " not found.\n";
    return false;
}

// Function to display the current status of the vehicle
void displayStatus(string vehicleName, int currentWeight, int maxCapacity, vector<int>& passengerWeights) {
    cout << "Vehicle Name: " << vehicleName << "\n";
    cout << "Current weight of passengers: " << currentWeight << " kg\n";
    cout << "Remaining capacity: " << (maxCapacity - currentWeight) << " kg\n";
    cout << "Total passengers: " << passengerWeights.size() << "\n";
}

// Function to display the total number of passengers
void displayTotalPassengers(vector<int>& passengerWeights) {
    cout << "Total passengers: " << passengerWeights.size() << "\n";
}

// Function to display the total weight of passengers
void displayTotalWeight(int currentWeight) {
    cout << "Total weight of passengers: " << currentWeight << " kg\n";
}

// Function to clear all passengers from the vehicle
void clearAllPassengers(int& currentWeight, vector<int>& passengerWeights) {
    passengerWeights.clear();
    currentWeight = 0;
    cout << "All passengers removed.\n";
}

// Function to display the remaining capacity of the vehicle
void displayRemainingCapacity(int maxCapacity, int currentWeight) {
    cout << "Remaining capacity: " << (maxCapacity - currentWeight) << " kg\n";
}

// Function to display the list of all passengers' weights
void displayPassengerList(vector<int>& passengerWeights) {
    cout << "Passenger List:\n";
    for (int weight : passengerWeights) {
        cout << weight << " kg\n";
    }
}

// Function to manage the vehicle (adding/removing passengers, checking status)
void manageVehicle() {
    string vehicleName;
    int maxCapacity;
    int currentWeight = 0;  // Initially, no passengers
    vector<int> passengerWeights;

    // Get vehicle details from the user
    cout << "Enter vehicle name: ";
    cin >> vehicleName;
    cout << "Enter maximum weight capacity of the vehicle: ";
    cin >> maxCapacity;

    // Menu for user to interact with the vehicle system
    while (true) {
        int choice;
        cout << "\nMENU:\n";
        cout << "1. Add Passenger\n";
        cout << "2. Remove Passenger\n";
        cout << "3. Check Vehicle Status\n";
        cout << "4. Display Total Passengers\n";
        cout << "5. Check Total Weight\n";
        cout << "6. Clear All Passengers\n";
        cout << "7. Check Remaining Capacity\n";
        cout << "8. Display Passenger List\n";
        cout << "9. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int weight;
                cout << "Enter passenger weight: ";
                cin >> weight;
                addPassenger(currentWeight, maxCapacity, passengerWeights, weight);
                break;
            }
            case 2: {
                int weight;
                cout << "Enter passenger weight to remove: ";
                cin >> weight;
                removePassenger(currentWeight, passengerWeights, weight);
                break;
            }
            case 3:
                displayStatus(vehicleName, currentWeight, maxCapacity, passengerWeights);
                break;
            case 4:
                displayTotalPassengers(passengerWeights);
                break;
            case 5:
                displayTotalWeight(currentWeight);
                break;
            case 6:
                clearAllPassengers(currentWeight, passengerWeights);
                break;
            case 7:
                displayRemainingCapacity(maxCapacity, currentWeight);
                break;
            case 8:
                displayPassengerList(passengerWeights);
                break;
            case 9:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    manageVehicle();
    return 0;
}
