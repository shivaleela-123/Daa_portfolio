#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>  // For time-based delay
using namespace std;

// 1. Dynamic Signal Timing Based on Real-Time Traffic Data
void dynamicSignalTiming() {
    map<string, int> trafficData;
    int numRoads;
    cout << "Enter the number of roads: ";
    cin >> numRoads;

    for (int i = 0; i < numRoads; i++) {
        string roadName;
        int trafficVolume;
        cout << "Enter the name of road " << i + 1 << ": ";
        cin >> roadName;
        cout << "Enter traffic volume for " << roadName << ": ";
        cin >> trafficVolume;
        trafficData[roadName] = trafficVolume;
    }

    cout << "Dynamic Signal Timing Based on Real-Time Traffic Data:\n";
    for (auto& road : trafficData) {
        int duration = road.second * 0.5;
        cout << "Green light for " << road.first << ": " << duration << " seconds\n";
    }
    cout << "-----------------------------------\n";
}

// 2. Pedestrian Crossing Integration
void pedestrianSignal() {
    int vehicleCount;
    cout << "Enter vehicle count: ";
    cin >> vehicleCount;
    int pedestrianTime = (vehicleCount > 50) ? 30 : 15;
    cout << "Pedestrian Signal Active for " << pedestrianTime << " seconds\n";
}

// 3. Emergency Vehicle Priority
void emergencyVehicleSignal() {
    bool emergencyDetected;
    cout << "Is there an emergency vehicle? (1 for Yes, 0 for No): ";
    cin >> emergencyDetected;

    if (emergencyDetected) {
        cout << "Emergency Vehicle Detected! Green Signal Activated Immediately.\n";
    } else {
        cout << "Normal Traffic Flow.\n";
    }
}

// 4. Adaptive Traffic Light Synchronization
void synchronizeTrafficLights() {
    int intersections;
    cout << "Enter the number of intersections: ";
    cin >> intersections;

    for (int i = 1; i <= intersections; i++) {
        cout << "Intersection " << i << ": Green for 30 seconds, synchronized.\n";
    }
}

// 5. Detection of Malfunctioning Traffic Signals
void detectMalfunction() {
    bool lightStatus;
    cout << "Is the traffic light functioning? (1 for Yes, 0 for No): ";
    cin >> lightStatus;

    if (!lightStatus) {
        cout << "Error: Traffic Light Malfunction Detected!\n";
    } else {
        cout << "Traffic light is functioning properly.\n";
    }
}

// 6. Traffic Density Prediction
void predictTrafficDensity() {
    string timeOfDay;
    cout << "Enter the time of day (morning, afternoon, evening, night): ";
    cin >> timeOfDay;

    if (timeOfDay == "morning" || timeOfDay == "evening") {
        cout << "High Traffic Expected. Increase Green Signal Duration.\n";
    } else {
        cout << "Low Traffic Expected. Standard Signal Duration.\n";
    }
}

// 7. Lane-Specific Signal Control
void laneSpecificSignal() {
    map<string, int> laneData;
    int numLanes;
    cout << "Enter the number of lanes: ";
    cin >> numLanes;

    for (int i = 0; i < numLanes; i++) {
        string laneType;
        int vehicleCount;
        cout << "Enter lane type (e.g., Left Turn, Straight): ";
        cin >> laneType;
        cout << "Enter vehicle count for " << laneType << ": ";
        cin >> vehicleCount;
        laneData[laneType] = vehicleCount;
    }

    for (auto& lane : laneData) {
        int duration = lane.second * 0.5;
        cout << "Lane " << lane.first << ": Green Light for " << duration << " seconds\n";
    }
}

// 8. Smart Traffic Lights with AI Integration
void smartTrafficSignal() {
    int vehicleCount;
    cout << "Enter the vehicle count: ";
    cin >> vehicleCount;

    if (vehicleCount > 50) {
        cout << "High Traffic Detected. Green Signal Extended.\n";
    } else {
        cout << "Low Traffic Detected. Standard Signal Timing.\n";
    }
}

// 9. Night Mode Traffic Signals
void nightModeSignal() {
    bool isNight;
    cout << "Is it night time? (1 for Yes, 0 for No): ";
    cin >> isNight;

    if (isNight) {
        cout << "Night Mode Activated: Flashing Yellow Light.\n";
    } else {
        cout << "Day Mode: Normal Traffic Light Operation.\n";
    }
}

// 10. Vehicle Count and Classification
void classifyVehicles() {
    int trucks, cars, bikes;
    cout << "Enter the number of trucks: ";
    cin >> trucks;
    cout << "Enter the number of cars: ";
    cin >> cars;
    cout << "Enter the number of bikes: ";
    cin >> bikes;

    cout << "Trucks: " << trucks << "\nCars: " << cars << "\nBikes: " << bikes << endl;
    if (trucks > cars && trucks > bikes) {
        cout << "Priority given to Truck Lane.\n";
    } else if (cars > bikes) {
        cout << "Priority given to Car Lane.\n";
    } else {
        cout << "Priority given to Bike Lane.\n";
    }
}

// 11. Real-Time Traffic Violation Detection
struct Vehicle {
    string plateNumber;
    bool violatedSignal;
};

void detectViolations() {
    int numVehicles;
    cout << "Enter the number of vehicles: ";
    cin >> numVehicles;

    vector<Vehicle> vehicles(numVehicles);
    for (int i = 0; i < numVehicles; i++) {
        cout << "Enter vehicle " << i + 1 << " plate number: ";
        cin >> vehicles[i].plateNumber;
        cout << "Did this vehicle violate the signal? (1 for Yes, 0 for No): ";
        cin >> vehicles[i].violatedSignal;
    }

    cout << "Violating Vehicles:\n";
    for (auto& v : vehicles) {
        if (v.violatedSignal) {
            cout << "Vehicle " << v.plateNumber << " violated the signal!\n";
        }
    }
}

// 12. Signal Control During Special Events
void specialEventMode() {
    bool isEventActive;
    cout << "Is there a special event? (1 for Yes, 0 for No): ";
    cin >> isEventActive;

    if (isEventActive) {
        cout << "Special Event Mode: Extended green signal on main roads.\n";
    } else {
        cout << "Normal Traffic Mode.\n";
    }
}

// 13. Emergency Signal Override System
void overrideTrafficSignal() {
    bool manualOverride;
    cout << "Is manual override active? (1 for Yes, 0 for No): ";
    cin >> manualOverride;

    if (manualOverride) {
        cout << "Manual Override: All signals set to flashing yellow.\n";
    } else {
        cout << "Automatic Signal Control Active.\n";
    }
}

// 14. Traffic Signal Countdown Timer
void countdownTimer() {
    int duration;
    cout << "Enter the countdown duration in seconds: ";
    cin >> duration;

    for (int i = duration; i >= 0; i--) {
        cout << "Time Left: " << i << " seconds\n";

        // Delay using clock function to simulate a 1-second delay
        clock_t start_time = clock();
        while (clock() < start_time + CLOCKS_PER_SEC) {
            // Busy wait to simulate a delay
        }
    }
    cout << "Signal Changed!\n";
}

// 15. Fuel-Efficient Signal Timing
void fuelEfficientSignal() {
    int vehicleCount;
    cout << "Enter the vehicle count: ";
    cin >> vehicleCount;

    int duration = (vehicleCount > 50) ? 45 : 30;
    cout << "Green Signal Duration: " << duration << " seconds (Fuel Optimized)\n";
}

// 16. Integration with Weather Conditions
void adjustForWeather() {
    string weather;
    cout << "Enter the current weather (e.g., Rain, Fog, Clear): ";
    cin >> weather;

    if (weather == "Rain" || weather == "Fog") {
        cout << "Weather Condition: " << weather << " - Extend signal time for safety.\n";
    } else {
        cout << "Normal Weather: Standard signal timing.\n";
    }
}

// 17. Pedestrian Smart Button System
void pedestrianCrossing() {
    bool buttonPressed;
    cout << "Is the pedestrian button pressed? (1 for Yes, 0 for No): ";
    cin >> buttonPressed;

    if (buttonPressed) {
        cout << "Pedestrian Button Pressed: Activating pedestrian crossing signal.\n";
    } else {
        cout << "No Pedestrian Request Detected.\n";
    }
}

// 18. Lane Clearance System During Accidents
void clearAccidentLane() {
    bool accidentDetected;
    cout << "Is there an accident? (1 for Yes, 0 for No): ";
    cin >> accidentDetected;

    if (accidentDetected) {
        cout << "Accident Detected: Extending green signal for affected lane.\n";
    } else {
        cout << "Normal Lane Operations.\n";
    }
}
// 19. Integration with Smart Vehicles (V2I Communication)
void communicateWithSmartVehicle() {
    bool vehicleConnected;
    cout << "Is the smart vehicle connected? (1 for Yes, 0 for No): ";
    cin >> vehicleConnected;

    if (vehicleConnected) {
        cout << "Smart Vehicle Connected: Sending traffic light status.\n";
    } else {
        cout << "No Smart Vehicle Detected.\n";
    }
}

// 20. Traffic Signal Health Monitoring System
struct TrafficSignal {
    string location;
    bool isFunctional;
};

void monitorSignalHealth() {
    TrafficSignal signal;
    cout << "Enter the location of the traffic signal: ";
    cin >> signal.location;
    cout << "Is the signal functional? (1 for Yes, 0 for No): ";
    cin >> signal.isFunctional;

    if (signal.isFunctional) {
        cout << "Signal at " << signal.location << " is functional.\n";
    } else {
        cout << "Signal at " << signal.location << " is malfunctioning! Maintenance required.\n";
    }
}

// Main Function with Switch-Case Menu
int main() {
    int choice;

    do {
        cout << "\nSelect a function to execute:\n";
        cout << "1. Dynamic Signal Timing\n";
        cout << "2. Pedestrian Signal Integration\n";
        cout << "3. Emergency Vehicle Priority\n";
        cout << "4. Synchronize Traffic Lights\n";
        cout << "5. Detect Malfunctioning Traffic Lights\n";
        cout << "6. Predict Traffic Density\n";
        cout << "7. Lane-Specific Signal Control\n";
        cout << "8. Smart Traffic Signal\n";
        cout << "9. Night Mode Traffic Signals\n";
        cout << "10. Vehicle Count and Classification\n";
        cout << "11. Real-Time Traffic Violation Detection\n";
        cout << "12. Special Event Mode\n";
        cout << "13. Emergency Signal Override\n";
        cout << "14. Traffic Signal Countdown Timer\n";
        cout << "15. Fuel-Efficient Signal Timing\n";
        cout << "16. Weather-Adjusted Signal Timing\n";
        cout << "17. Pedestrian Smart Button System\n";
        cout << "18. Lane Clearance During Accidents\n";
        cout << "19. Integration with Smart Vehicles\n";
        cout << "20. Traffic Signal Health Monitoring\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                dynamicSignalTiming();
                break;
            case 2:
                pedestrianSignal();
                break;
            case 3:
                emergencyVehicleSignal();
                break;
            case 4:
                synchronizeTrafficLights();
                break;
            case 5:
                detectMalfunction();
                break;
            case 6:
                predictTrafficDensity();
                break;
            case 7:
                laneSpecificSignal();
                break;
            case 8:
                smartTrafficSignal();
                break;
            case 9:
                nightModeSignal();
                break;
            case 10:
                classifyVehicles();
                break;
            case 11:
                detectViolations();
                break;
            case 12:
                specialEventMode();
                break;
            case 13:
                overrideTrafficSignal();
                break;
            case 14:
                countdownTimer();
                break;
            case 15:
                fuelEfficientSignal();
                break;
            case 16:
                adjustForWeather();
                break;
            case 17:
                pedestrianCrossing();
                break;
            case 18:
                clearAccidentLane();
                break;
            case 19:
                communicateWithSmartVehicle();
                break;
            case 20:
                monitorSignalHealth();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please select a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}
