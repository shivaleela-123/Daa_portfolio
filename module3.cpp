#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <map>
#include <string>
#include <limits>
#include <iomanip>
#include<fstream>
  // For time-based delay
using namespace std;

// 1. Dynamic Signal Timing Based on Real-Time Traffic Data
void dynamicSignalTiming() {
    map<string, int> trafficData;
    int numRoads;

    cout << "Enter the number of roads: ";
    while (!(cin >> numRoads) || numRoads <= 0) {
        cout << "Please enter a valid positive integer for the number of roads: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }

    for (int i = 0; i < numRoads; i++) {
        string roadName;
        int trafficVolume;

        cout << "Enter the name of road " << i + 1 << ": ";
        cin >> roadName;

        cout << "Enter traffic volume for " << roadName << ": ";
        while (!(cin >> trafficVolume) || trafficVolume < 0) {
            cout << "Please enter a valid non-negative integer for traffic volume: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        trafficData[roadName] = trafficVolume;
    }

    // Customizable duration calculation
    double durationFactor;
    cout << "Enter the duration factor (seconds per unit of traffic volume): ";
    while (!(cin >> durationFactor) || durationFactor <= 0) {
        cout << "Please enter a valid positive number for the duration factor: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nDynamic Signal Timing Based on Real-Time Traffic Data:\n";
    double totalTrafficVolume = 0;
    double totalDuration = 0;

    for (const auto& road : trafficData) {
        int trafficVolume = road.second;
        double duration = trafficVolume * durationFactor; // Calculate duration based on user-defined factor
        totalTrafficVolume += trafficVolume;
        totalDuration += duration;

        // Categorize traffic volume
        string category;
        if (trafficVolume < 20) {
            category = "Low";
        } else if (trafficVolume < 50) {
            category = "Medium";
        } else {
            category = "High";
        }

        // Convert duration from seconds to minutes
        double durationInMinutes = duration / 60;

        cout << "Green light for " << road.first << ": " << fixed << setprecision(2)
             << durationInMinutes << " minutes (Traffic Volume: " << trafficVolume << ", Category: " << category << ")\n";
    }

    // Calculate and display totals and averages
    double averageDuration = totalDuration / numRoads;
    double averageDurationInMinutes = averageDuration / 60;  // Convert average duration to minutes

    cout << "\nTotal Traffic Volume: " << totalTrafficVolume << "\n";
    cout << "Average Green Light Duration: " << fixed << setprecision(2) << averageDurationInMinutes << " minutes\n";
    cout << "-----------------------------------\n";
}

// 2. Pedestrian Crossing Integration
void pedestrianSignal() {
    int vehicleCount;

    // Input validation for vehicle count
    cout << "Enter vehicle count: ";
    while (!(cin >> vehicleCount) || vehicleCount < 0) {
        cout << "Please enter a valid non-negative integer for vehicle count: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }

    // Determine pedestrian signal time based on vehicle count
    int pedestrianTime;
    if (vehicleCount > 50) {
        pedestrianTime = 30; // Longer time for high vehicle count
        cout << "High vehicle count detected. ";
    } else {
        pedestrianTime = 15; // Shorter time for low vehicle count
        cout << "Low vehicle count detected. ";
    }

    cout << "Pedestrian Signal Active for " << pedestrianTime << " seconds\n";
}


// 3. Emergency Vehicle Priority
void emergencyVehicleSignal() {
    bool emergencyDetected;
    int vehicleCount;

    // Input validation for emergency vehicle detection
    cout << "Is there an emergency vehicle? (1 for Yes, 0 for No): ";
    while (!(cin >> emergencyDetected) || (emergencyDetected != 0 && emergencyDetected != 1)) {
        cout << "Please enter 1 for Yes or 0 for No: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }

    if (emergencyDetected) {
        cout << "Emergency Vehicle Detected!\n";

        // Input for the number of emergency vehicles
        cout << "Enter the number of emergency vehicles: ";
        while (!(cin >> vehicleCount) || vehicleCount <= 0) {
            cout << "Please enter a valid positive integer for the number of emergency vehicles: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        // Determine signal duration based on the number of emergency vehicles
        int signalDuration = 10 + (vehicleCount * 5); // Base duration + additional time per vehicle
        cout << "Green Signal Activated Immediately for " << signalDuration << " seconds.\n";
        cout << "Please be aware that normal traffic flow will be interrupted during this time.\n";
    } else {
        cout << "Normal Traffic Flow.\n";
    }
}

// 4. Adaptive Traffic Light Synchronization
// Function to simulate real-time traffic data for each intersection
map<int, int> getTrafficVolume(int intersections) {
    map<int, int> trafficData;
    for (int i = 1; i <= intersections; i++) {
        trafficData[i] = rand() % 100 + 20;  // Simulated vehicle count for each intersection
    }
    return trafficData;
}

// Function to synchronize traffic lights
void synchronizeTrafficLights() {
    int intersections;
    cout << "Enter the number of intersections: ";
    cin >> intersections;

    // Simulate real-time traffic data collection
    map<int, int> trafficData = getTrafficVolume(intersections);

    // Open a log file for storing synchronization details
    ofstream logFile("synchronization_log.txt", ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    logFile << "Synchronization started at " << dt << "\n";

    // Synchronize traffic lights based on traffic data
    for (int i = 1; i <= intersections; i++) {
        // Check traffic volume for the intersection
        int vehicleCount = trafficData[i];
        int greenDuration = 30;  // Default green light duration

        // Adjust green light duration based on traffic
        if (vehicleCount > 70) {
            greenDuration += 15;  // Heavily congested, extend the duration
        } else if (vehicleCount < 40) {
            greenDuration -= 10;  // Low traffic, shorten the duration
        }

        // Simulate emergency vehicle detection
        bool emergencyVehicleDetected = rand() % 10 < 1;  // 10% chance of emergency vehicle
        if (emergencyVehicleDetected) {
            cout << "Emergency vehicle detected at Intersection " << i << "! Extending green light.\n";
            greenDuration += 20;  // Give priority to the emergency vehicle
        }

        // Display synchronization info
        cout << "Intersection " << i << ": Green for " << greenDuration << " seconds, synchronized.\n";

        // Log the synchronization
        logFile << "Intersection " << i << ": Green for " << greenDuration << " seconds, vehicle count: " << vehicleCount << "\n";
        if (emergencyVehicleDetected) {
            logFile << "Emergency vehicle detected at Intersection " << i << "\n";
        }
    }

    // End of synchronization log entry
    logFile << "-----------------------------------\n";
    logFile.close();
}

// 5. Detection of Malfunctioning Traffic Signals
struct TrafficLight {
    string intersection;
    bool isFunctional;
    string malfunctionDetails;  // Store details if malfunction occurs
};

// Function to simulate real-time malfunction detection
void detectMalfunction() {
    int numLights;
    cout << "Enter the number of traffic lights to check: ";
    cin >> numLights;

    // Open a log file for storing malfunction details
    ofstream logFile("malfunction_log.txt", ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    logFile << "Malfunction Check Started at " << dt << "\n";

    // Array of traffic lights
    TrafficLight lights[numLights];

    for (int i = 0; i < numLights; i++) {
        cout << "Enter intersection name for traffic light " << i + 1 << ": ";
        cin >> lights[i].intersection;

        // Randomly simulate malfunction detection
        bool lightStatus = rand() % 2;  // 0 or 1 (simulating malfunction or functional status)

        if (!lightStatus) {
            cout << "Traffic light at " << lights[i].intersection << " is malfunctioning!\n";
            cout << "Enter malfunction details (e.g., blinking, off, partial failure): ";
            cin >> lights[i].malfunctionDetails;

            // Log the malfunction
            logFile << "Malfunction detected at Intersection " << lights[i].intersection
                    << ": " << lights[i].malfunctionDetails << "\n";

            // Notify for maintenance
            cout << "Maintenance required for " << lights[i].intersection << "!\n";
        } else {
            cout << "Traffic light at " << lights[i].intersection << " is functioning properly.\n";
            logFile << "Traffic light at Intersection " << lights[i].intersection << " is functional.\n";
        }

        cout << endl;
    }

    // End of malfunction log entry
    logFile << "-----------------------------------\n";
    logFile.close();
}


// 6. Traffic Density Prediction
void predictTrafficDensity() {
    string timeOfDay, dayOfWeek;
    int trafficVolume;

    // Get the time of day
    cout << "Enter the time of day (morning, afternoon, evening, night): ";
    cin >> timeOfDay;

    // Get the day of the week
    cout << "Enter the day of the week (Monday, Tuesday, etc.): ";
    cin >> dayOfWeek;

    // Simulate traffic volume based on time of day and day of the week
    trafficVolume = rand() % 100 + 50;  // Generate a random traffic volume between 50 and 150

    // Log the traffic prediction
    ofstream logFile("traffic_density_log.txt", ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    logFile << "Traffic Density Prediction at " << dt << "\n";
    logFile << "Time of Day: " << timeOfDay << ", Day of the Week: " << dayOfWeek << "\n";
    logFile << "Simulated Traffic Volume: " << trafficVolume << "\n";

    // Predict traffic density and adjust signal timing
    if (timeOfDay == "morning" || timeOfDay == "evening") {
        cout << "High Traffic Expected. Increase Green Signal Duration.\n";
        logFile << "High Traffic Expected. Green Signal Duration Extended.\n";
    }
    else if (timeOfDay == "afternoon") {
        if (trafficVolume > 100) {
            cout << "Afternoon Rush. Increase Green Signal Duration.\n";
            logFile << "Afternoon Rush Detected. Green Signal Duration Extended.\n";
        } else {
            cout << "Moderate Traffic in the Afternoon. Standard Signal Duration.\n";
            logFile << "Moderate Traffic in the Afternoon. Standard Signal Duration.\n";
        }
    }
    else if (timeOfDay == "night") {
        cout << "Low Traffic Expected at Night. Standard Signal Duration.\n";
        logFile << "Low Traffic Expected at Night. Standard Signal Duration.\n";
    }

    // Special case for weekends or holidays (e.g., Sunday or public holidays)
    if (dayOfWeek == "Saturday" || dayOfWeek == "Sunday") {
        cout << "Weekend Traffic: Expect less congestion.\n";
        logFile << "Weekend Traffic: Expect less congestion.\n";
    }
    else if (dayOfWeek == "Monday" || dayOfWeek == "Friday") {
        cout << "High Traffic Due to Weekday Rush.\n";
        logFile << "Weekday Rush Detected. Increase Signal Duration.\n";
    }

    // Log the result and close the log file
    logFile << "-----------------------------------\n";
    logFile.close();
}

// 7. Lane-Specific Signal Control
struct LaneData {
    int vehicleCount;
    int truckCount;
    int carCount;
    int bikeCount;
    string laneType;
};

void laneSpecificSignal() {
    map<string, LaneData> laneData;
    int numLanes;
    cout << "Enter the number of lanes: ";
    cin >> numLanes;

    for (int i = 0; i < numLanes; i++) {
        LaneData laneDetails;
        cout << "Enter lane type (e.g., Left Turn, Straight): ";
        cin >> laneDetails.laneType;

        // Get vehicle counts for each lane
        cout << "Enter total vehicle count for " << laneDetails.laneType << ": ";
        cin >> laneDetails.vehicleCount;

        // Simulate vehicle type distribution (or ask for it if needed)
        cout << "Enter truck count for " << laneDetails.laneType << ": ";
        cin >> laneDetails.truckCount;
        cout << "Enter car count for " << laneDetails.laneType << ": ";
        cin >> laneDetails.carCount;
        cout << "Enter bike count for " << laneDetails.laneType << ": ";
        cin >> laneDetails.bikeCount;

        laneData[laneDetails.laneType] = laneDetails;
    }

    // Log the data to a file for record-keeping
    ofstream logFile("lane_signal_log.txt", ios::app);
    logFile << "Lane Specific Signal Log:\n";

    // Adjust signal durations based on the traffic volume in each lane
    for (auto& lane : laneData) {
        int duration = lane.second.vehicleCount * 0.5;  // Base duration for the lane
        // Prioritize signal time based on vehicle types
        if (lane.second.truckCount > lane.second.carCount && lane.second.truckCount > lane.second.bikeCount) {
            duration += 15;  // Trucks take priority and require more time
            cout << "Lane " << lane.first << ": Priority given to trucks. Extended green light.\n";
        } else if (lane.second.carCount > lane.second.bikeCount) {
            duration += 10;  // Cars take priority
            cout << "Lane " << lane.first << ": Priority given to cars. Extended green light.\n";
        } else {
            cout << "Lane " << lane.first << ": Priority given to bikes. Extended green light.\n";
        }

        // Calculate final signal duration based on the number of vehicles
        cout << "Lane " << lane.first << ": Green Light for " << duration << " seconds\n";
        logFile << "Lane " << lane.first << ": Vehicle Count = " << lane.second.vehicleCount
                << ", Truck Count = " << lane.second.truckCount << ", Car Count = " << lane.second.carCount
                << ", Bike Count = " << lane.second.bikeCount << ", Signal Duration = " << duration << " seconds\n";
    }

    // Log end of lane signal data
    logFile << "-----------------------------------\n";
    logFile.close();
}


// 8. Smart Traffic Lights with AI Integration
void smartTrafficSignal() {
    int vehicleCount;
    string weatherCondition;
    string timeOfDay;

    // Prompt user for vehicle count
    cout << "Enter the vehicle count: ";
    cin >> vehicleCount;

    // Ask for weather condition (could be dynamic or simulated)
    cout << "Enter the current weather (Clear, Rain, Fog): ";
    cin >> weatherCondition;

    // Ask for time of day (morning, afternoon, evening, night)
    cout << "Enter the time of day (morning, afternoon, evening, night): ";
    cin >> timeOfDay;

    // Adjust signal duration based on traffic volume
    int greenSignalDuration = (vehicleCount > 50) ? 60 : 30; // Base duration

    // Adjust signal based on time of day
    if (timeOfDay == "morning" || timeOfDay == "evening") {
        greenSignalDuration += 10; // More vehicles expected during these times
        cout << "Peak traffic time detected. Adjusting signal duration.\n";
    }

    // Adjust signal duration based on weather conditions
    if (weatherCondition == "Rain" || weatherCondition == "Fog") {
        greenSignalDuration += 15; // Add more time for safety in adverse weather
        cout << "Weather condition " << weatherCondition << " detected. Extending signal time for safety.\n";
    }

    // Vehicle type prioritization (simulated here as a random count)
    int truckCount = rand() % vehicleCount; // Random number of trucks
    int carCount = rand() % vehicleCount;   // Random number of cars
    int bikeCount = vehicleCount - truckCount - carCount;

    // Prioritize signals based on vehicle types (Example: trucks take more time)
    if (truckCount > carCount && truckCount > bikeCount) {
        greenSignalDuration += 20; // Trucks need more time to pass
        cout << "Priority given to trucks. Extending green light.\n";
    } else if (carCount > bikeCount) {
        greenSignalDuration += 10; // Cars need slightly more time
        cout << "Priority given to cars. Extending green light.\n";
    } else {
        greenSignalDuration += 5;  // Bikes need the least time
        cout << "Priority given to bikes. Extending green light.\n";
    }

    // Log the decisions to a file
    ofstream logFile("traffic_signal_log.txt", ios::app);
    logFile << "--------------------------------------\n";
    logFile << "Vehicle Count: " << vehicleCount << "\n";
    logFile << "Weather: " << weatherCondition << "\n";
    logFile << "Time of Day: " << timeOfDay << "\n";
    logFile << "Truck Count: " << truckCount << ", Car Count: " << carCount << ", Bike Count: " << bikeCount << "\n";
    logFile << "Signal Duration: " << greenSignalDuration << " seconds\n";
    logFile << "--------------------------------------\n";
    logFile.close();

    // Output the result to the user
    cout << "Green Signal Duration: " << greenSignalDuration << " seconds\n";
}

// 9. Night Mode Traffic Signals
void nightModeSignal() {
    // Get the current system time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Check if the current time is between 8 PM (20:00) and 6 AM (06:00)
    bool isNight = (ltm->tm_hour >= 20 || ltm->tm_hour < 6);

    // Logging file to record night mode events
    ofstream logFile("traffic_mode_log.txt", ios::app);

    if (isNight) {
        // If it is night, activate night mode
        cout << "Night Mode Activated: Flashing Yellow Light.\n";
        logFile << "Night Mode Activated: Flashing Yellow Light at " << ltm->tm_hour << ":" << ltm->tm_min << "\n";

        // Additional night mode logic based on traffic conditions
        int vehicleCount;
        cout << "Enter the vehicle count for night traffic: ";
        cin >> vehicleCount;

        if (vehicleCount < 10) {
            cout << "Low Traffic Volume: Extend flashing yellow light duration.\n";
            logFile << "Low Traffic Volume detected. Extending flashing yellow light duration.\n";
        } else {
            cout << "Moderate Traffic Volume: Normal flashing yellow duration.\n";
            logFile << "Moderate Traffic Volume detected. Normal flashing yellow light duration.\n";
        }

        // Safety measures for night mode (e.g., extend yellow light for safety)
        cout << "Safety Measure: Extending yellow light for 5 seconds for night driving safety.\n";
        logFile << "Safety Measure: Extended yellow light duration for night driving safety.\n";

    } else {
        // If it's not night time, operate in day mode
        cout << "Day Mode: Normal Traffic Light Operation.\n";
        logFile << "Day Mode: Normal Traffic Light Operation at " << ltm->tm_hour << ":" << ltm->tm_min << "\n";
    }

    // Close the log file after the operation
    logFile.close();
}

// 10. Vehicle Count and Classification
void classifyVehicles() {
    // Declare variables to store vehicle counts
    int trucks, cars, bikes, emergencyVehicles;
    cout << "Enter the number of trucks: ";
    cin >> trucks;
    cout << "Enter the number of cars: ";
    cin >> cars;
    cout << "Enter the number of bikes: ";
    cin >> bikes;
    cout << "Enter the number of emergency vehicles (if any): ";
    cin >> emergencyVehicles;

    // Output the basic vehicle counts
    cout << "\nVehicle Classification:\n";
    cout << "Trucks: " << trucks << "\nCars: " << cars << "\nBikes: " << bikes << "\nEmergency Vehicles: " << emergencyVehicles << endl;

    // Logic to handle emergency vehicles first
    if (emergencyVehicles > 0) {
        cout << "Emergency Vehicle Detected! Immediate priority given to Emergency Vehicle Lane.\n";
        return;  // Exit after giving priority to emergency vehicles
    }

    // Classify lanes based on vehicle counts
    if (trucks > cars && trucks > bikes) {
        cout << "Priority given to Truck Lane.\n";
    } else if (cars > bikes) {
        cout << "Priority given to Car Lane.\n";
    } else {
        cout << "Priority given to Bike Lane.\n";
    }

    // Lane capacity consideration
    int maxLaneCapacity = 50;  // Arbitrary lane capacity
    if (trucks > maxLaneCapacity) {
        cout << "Truck lane exceeds maximum capacity! Consider rerouting some trucks.\n";
    }
    if (cars > maxLaneCapacity) {
        cout << "Car lane exceeds maximum capacity! Consider rerouting some cars.\n";
    }
    if (bikes > maxLaneCapacity) {
        cout << "Bike lane exceeds maximum capacity! Consider rerouting some bikes.\n";
    }

    // Safety considerations for bike lanes
    if (bikes > 0) {
        cout << "Safety measures applied for Bike Lane: Extending green light for bike safety.\n";
    }

    // Traffic Pattern Consideration (Day/Night Time)
    string timeOfDay;
    cout << "Enter the time of day (morning, afternoon, evening, night): ";
    cin >> timeOfDay;

    if (timeOfDay == "morning" || timeOfDay == "evening") {
        cout << "Peak traffic hours detected. Adjusting signal timing for higher traffic.\n";
    } else {
        cout << "Off-peak hours detected. Normal signal timing.\n";
    }

    // Suggest lane changes based on traffic flow
    if (cars > trucks && cars > bikes) {
        cout << "Consider opening additional lanes for cars during peak hours.\n";
    } else if (trucks > cars && trucks > bikes) {
        cout << "Consider creating dedicated truck lanes during peak hours.\n";
    } else {
        cout << "Consider opening additional lanes for bikes during off-peak hours.\n";
    }
}

// 11. Real-Time Traffic Violation Detection
struct Vehicle {
    string plateNumber;
    bool violatedSignal;
    string vehicleType; // Added vehicle type
    string violationTime; // Added time of violation
    string intersection; // Added intersection info
    string violationSeverity; // Added violation severity
};

void detectViolations() {
    int numVehicles;
    cout << "Enter the number of vehicles: ";
    cin >> numVehicles;

    vector<Vehicle> vehicles(numVehicles);

    // Collect data for each vehicle
    for (int i = 0; i < numVehicles; i++) {
        cout << "Enter vehicle " << i + 1 << " plate number: ";
        cin >> vehicles[i].plateNumber;

        cout << "Enter vehicle type (Car, Truck, Bike): ";
        cin >> vehicles[i].vehicleType;

        cout << "Enter the intersection where violation occurred: ";
        cin >> vehicles[i].intersection;

        cout << "Enter the violation time (e.g., 10:30 AM): ";
        cin >> vehicles[i].violationTime;

        cout << "Did this vehicle violate the signal? (1 for Yes, 0 for No): ";
        cin >> vehicles[i].violatedSignal;

        // Determine violation severity based on vehicle type or time
        if (vehicles[i].violatedSignal) {
            cout << "Was it a severe violation? (1 for Yes, 0 for No): ";
            int severity;
            cin >> severity;
            vehicles[i].violationSeverity = (severity == 1) ? "Severe" : "Minor";
        } else {
            vehicles[i].violationSeverity = "No Violation";
        }
    }

    // Process violations and provide reports
    cout << "\nViolating Vehicles Report:\n";
    int totalViolations = 0;
    map<string, int> violationCount; // To count violations by vehicle type

    for (auto& v : vehicles) {
        if (v.violatedSignal) {
            totalViolations++;
            violationCount[v.vehicleType]++;
            cout << "Vehicle " << v.plateNumber << " (Type: " << v.vehicleType << ") violated the signal!\n";
            cout << "Violation Severity: " << v.violationSeverity << "\n";
            cout << "Violation Time: " << v.violationTime << " at " << v.intersection << "\n";
            cout << "--------------------------------------------\n";
        }
    }

    // Display violation statistics
    cout << "\nTotal Violations: " << totalViolations << endl;
    cout << "Violation Breakdown by Vehicle Type:\n";
    for (auto& type : violationCount) {
        cout << type.first << ": " << type.second << " violations\n";
    }

    // Optionally log violations to a file
    ofstream logFile("violations_log.txt", ios::app); // Append to log file
    logFile << "Violating Vehicles Report - Total Violations: " << totalViolations << "\n";
    for (auto& v : vehicles) {
        if (v.violatedSignal) {
            logFile << "Plate Number: " << v.plateNumber << ", Type: " << v.vehicleType
                    << ", Violation Time: " << v.violationTime << ", Intersection: " << v.intersection
                    << ", Severity: " << v.violationSeverity << "\n";
        }
    }
    logFile << "============================================\n";
    logFile.close();
}

// 12. Signal Control During Special Events
void specialEventMode() {
    bool isEventActive;
    string eventType;
    int eventDuration;
    string eventTime;

    // Ask if there is a special event
    cout << "Is there a special event? (1 for Yes, 0 for No): ";
    cin >> isEventActive;

    if (isEventActive) {
        // If there is an event, ask for more details
        cout << "Enter the type of event (e.g., concert, parade, sports): ";
        cin >> eventType;

        cout << "Enter the duration of the green signal extension (in seconds): ";
        cin >> eventDuration;

        cout << "Enter the scheduled time of the event (e.g., 2:00 PM): ";
        cin >> eventTime;

        cout << "Special Event Mode Activated: ";
        cout << "Event Type: " << eventType << "\n";
        cout << "Event Duration: " << eventDuration << " seconds\n";
        cout << "Scheduled Time: " << eventTime << "\n";

        // Customize traffic adjustments based on the event type
        if (eventType == "concert" || eventType == "parade") {
            cout << "Priority: Extended green signal on main roads and routes leading to the event.\n";
        } else if (eventType == "sports") {
            cout << "Priority: Increased green signal duration on access roads to stadiums.\n";
        } else {
            cout << "Normal Event Priority: Green signals will be extended on major routes.\n";
        }

        // Ask for more specific road adjustments based on event
        string roadType;
        map<string, int> roadAdjustments;
        char moreAdjustments = 'y';

        while (moreAdjustments == 'y' || moreAdjustments == 'Y') {
            cout << "Enter the road type to adjust (Main, Secondary, Detour): ";
            cin >> roadType;

            int greenTime;
            cout << "Enter the extended green signal duration for " << roadType << " road: ";
            cin >> greenTime;

            roadAdjustments[roadType] = greenTime;
            cout << "Do you want to add more road adjustments? (y/n): ";
            cin >> moreAdjustments;
        }

        // Display all road adjustments
        cout << "\nRoad Adjustments During Event:\n";
        for (auto& adjustment : roadAdjustments) {
            cout << "Road: " << adjustment.first << " - Green Light for " << adjustment.second << " seconds\n";
        }

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
        // Ask for the type of override
        int overrideType;
        cout << "\nSelect Override Type:\n";
        cout << "1. Flashing Yellow (Caution)\n";
        cout << "2. Flashing Red (Stop)\n";
        cout << "3. All Green (Emergency)\n";
        cout << "4. No Signals (Maintenance)\n";
        cout << "Enter your choice: ";
        cin >> overrideType;

        // Ask for the reason for the override
        string reason;
        cout << "Enter the reason for the manual override (e.g., Emergency, Maintenance, etc.): ";
        cin.ignore();  // To clear the newline from previous input
        getline(cin, reason);

        // Provide override details
        switch (overrideType) {
            case 1:
                cout << "Override: Flashing Yellow (Caution) for all signals.\n";
                break;
            case 2:
                cout << "Override: Flashing Red (Stop) for all signals.\n";
                break;
            case 3:
                cout << "Override: All Green signals (Emergency).\n";
                break;
            case 4:
                cout << "Override: No Signals (Maintenance).\n";
                break;
            default:
                cout << "Invalid choice. Reverting to Automatic Signal Control.\n";
                return;
        }

        // Output the reason for override
        cout << "Reason for override: " << reason << endl;

        // Ask for the duration of the override (optional)
        int duration;
        cout << "Enter the duration of the override in minutes (0 for indefinite): ";
        cin >> duration;
        if (duration > 0) {
            cout << "Override will last for " << duration << " minutes.\n";
        } else {
            cout << "Override is set to be indefinite.\n";
        }

        // Ask if the override applies to specific intersections or globally
        char applyToSpecific;
        cout << "Apply override to specific intersections? (y/n): ";
        cin >> applyToSpecific;
        if (applyToSpecific == 'y' || applyToSpecific == 'Y') {
            int numIntersections;
            cout << "Enter the number of intersections to override: ";
            cin >> numIntersections;
            for (int i = 0; i < numIntersections; i++) {
                string intersection;
                cout << "Enter the name of intersection " << i + 1 << ": ";
                cin >> intersection;
                cout << "Override applied to " << intersection << ".\n";
            }
        } else {
            cout << "Override applied to all intersections.\n";
        }

        // Notify authorities or log the override event (simulation)
        cout << "\nOverride log: Manual override activated. Reason: " << reason << ". Duration: ";
        if (duration > 0) {
            cout << duration << " minutes.";
        } else {
            cout << "Indefinite duration.";
        }
        cout << "\nOverride applied to all intersections.\n";
    } else {
        cout << "Automatic Signal Control Active.\n";
    }
}

// 14. Traffic Signal Countdown Timer
void countdownTimer() {
    int duration;
    cout << "Enter the countdown duration in seconds: ";
    cin >> duration;

    // Using clock() based delay instead of sleep_for
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

    // Ask for the type of vehicles
    int trucks, cars, bikes;
    cout << "Enter the number of trucks: ";
    cin >> trucks;
    cout << "Enter the number of cars: ";
    cin >> cars;
    cout << "Enter the number of bikes: ";
    cin >> bikes;

    // Calculate total vehicle count
    int totalVehicles = trucks + cars + bikes;

    // Fuel-efficient logic based on total vehicle count and type
    int duration = 30;  // Default duration for lower traffic

    // If vehicle count is more than 50, extend the green light duration
    if (vehicleCount > 50) {
        duration = 45;
    }

    // Additional conditions based on vehicle types
    if (trucks > 0 && cars > 0) {
        duration += 10;  // Increase signal time if there are both trucks and cars
    }

    // Adjust signal timing based on time of day (peak hours)
    string timeOfDay;
    cout << "Enter time of day (morning, afternoon, evening, night): ";
    cin >> timeOfDay;

    if (timeOfDay == "morning" || timeOfDay == "evening") {
        duration += 10;  // Increase green light duration during peak hours
    }

    // Adjust based on weather conditions (e.g., rain, fog)
    string weather;
    cout << "Enter weather condition (clear, rain, fog): ";
    cin >> weather;

    if (weather == "rain" || weather == "fog") {
        duration += 5;  // Slightly increase green light duration during bad weather
    }

    // Provide fuel efficiency tips
    if (vehicleCount > 100) {
        cout << "High traffic detected! Consider adjusting the signal timing to optimize fuel usage for the entire flow.\n";
    }

    // Display fuel-efficient signal timing
    cout << "Total vehicles: " << totalVehicles << "\n";
    cout << "Green Signal Duration: " << duration << " seconds (Fuel Optimized)\n";

    // Additional notifications for vehicle types
    if (trucks > 0) {
        cout << "Trucks detected. Longer green duration recommended for heavy vehicles.\n";
    }
    if (bikes > 0) {
        cout << "Bikes detected. Shorter green duration for bike lanes can save fuel.\n";
    }

    // Provide overall fuel optimization suggestions based on conditions
    if (duration > 40) {
        cout << "Fuel optimization: Longer signal times are beneficial for traffic flow but may increase fuel consumption in the long term.\n";
    } else {
        cout << "Fuel optimization: Shorter signal times help reduce idle times and fuel consumption.\n";
    }
}


// 16. Integration with Weather Conditions
void adjustForWeather() {
    string weather;
    cout << "Enter the current weather (e.g., Rain, Fog, Clear, Snow, Wind): ";
    cin >> weather;

    // Extended Weather Conditions
    if (weather == "Rain" || weather == "Fog") {
        cout << "Weather Condition: " << weather << " - Extend signal time for safety.\n";
        cout << "Warning: Increased stopping distance due to poor visibility.\n";
        // You could adjust signal duration based on weather severity, for example:
        int duration = 45;  // Extended green signal time
        cout << "Adjusted Signal Duration: " << duration << " seconds.\n";
    }
    else if (weather == "Snow") {
        cout << "Weather Condition: Snow - Extended green signal duration for smoother traffic flow.\n";
        cout << "Warning: Possible slippery roads. Reduce speed and remain cautious.\n";
        int duration = 50;  // Longer green time for smoother flow in snowy conditions
        cout << "Adjusted Signal Duration: " << duration << " seconds.\n";
    }
    else if (weather == "Wind") {
        cout << "Weather Condition: Wind - Adjusting traffic flow for wind conditions.\n";
        cout << "Warning: Strong winds may affect vehicle stability. Caution required.\n";
        int duration = 40;  // Moderate signal duration to control traffic efficiently
        cout << "Adjusted Signal Duration: " << duration << " seconds.\n";
    }
    else if (weather == "Clear") {
        cout << "Weather Condition: Clear - Normal traffic signal timing.\n";
        int duration = 30;  // Default signal duration
        cout << "Adjusted Signal Duration: " << duration << " seconds.\n";
    } else {
        cout << "Unknown weather condition. Please enter a valid weather type (e.g., Rain, Fog, Clear, Snow, Wind).\n";
    }

    // Additional user input for actions based on weather
    char actionChoice;
    cout << "Would you like to adjust traffic signals manually based on weather? (y/n): ";
    cin >> actionChoice;

    if (actionChoice == 'y' || actionChoice == 'Y') {
        cout << "Manual Adjustment: Apply extended green signal for smooth traffic flow.\n";
        // Implement manual override logic (for example, extending green time)
        int manualDuration;
        cout << "Enter the desired extended green signal duration (in seconds): ";
        cin >> manualDuration;
        cout << "Manual Adjustment: Signal will remain green for " << manualDuration << " seconds.\n";
    } else {
        cout << "Normal automated traffic control is active.\n";
    }

    // Weather-based safety recommendations
    cout << "Safety Reminder: Always drive cautiously and adjust your speed according to weather conditions.\n";
}

// 17. Pedestrian Smart Button System
void pedestrianCrossing() {
    bool buttonPressed;
    cout << "Is the pedestrian button pressed? (1 for Yes, 0 for No): ";
    cin >> buttonPressed;

    if (buttonPressed) {
        cout << "Pedestrian Button Pressed: Activating pedestrian crossing signal.\n";

        // Log the current time when the button is pressed
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << "Request received at: " << dt << endl;

        // Determine traffic flow condition
        string trafficFlow;
        cout << "Enter the current traffic flow (Light, Moderate, Heavy): ";
        cin >> trafficFlow;

        int crossingTime = 10;  // Default crossing time

        if (trafficFlow == "Heavy") {
            crossingTime = 20;  // Increase pedestrian crossing time if traffic is heavy
            cout << "Heavy traffic detected. Pedestrian crossing time extended to " << crossingTime << " seconds.\n";
        } else if (trafficFlow == "Moderate") {
            crossingTime = 15;  // Moderate crossing time for moderate traffic
            cout << "Moderate traffic detected. Pedestrian crossing time set to " << crossingTime << " seconds.\n";
        } else {
            cout << "Light traffic detected. Pedestrian crossing time set to " << crossingTime << " seconds.\n";
        }

        // Simulate pedestrian crossing signal being active for the designated time
        cout << "Pedestrian signal active for " << crossingTime << " seconds.\n";

        // Simulating the time it takes for the pedestrian to cross using clock() method
        for (int i = crossingTime; i > 0; i--) {
            cout << "Time remaining for crossing: " << i << " seconds.\n";

            // Using clock() to simulate a 1-second delay
            clock_t start_time = clock();
            while (clock() < start_time + CLOCKS_PER_SEC) {
                // Busy-wait to simulate a delay
            }
        }
        cout << "Pedestrian crossing completed.\n";
    } else {
        cout << "No Pedestrian Request Detected.\n";
    }

    // Check if the pedestrian signal was successfully completed
    char userFeedback;
    cout << "Was the pedestrian crossing safe and completed? (y/n): ";
    cin >> userFeedback;

    if (userFeedback == 'y' || userFeedback == 'Y') {
        cout << "Pedestrian crossing was completed successfully.\n";
    } else {
        cout << "Please ensure pedestrian safety before continuing.\n";
    }
}

// 18. Lane Clearance System During Accidents
void clearAccidentLane() {
    bool accidentDetected;
    cout << "Is there an accident? (1 for Yes, 0 for No): ";
    cin >> accidentDetected;

    if (accidentDetected) {
        // Collect additional details about the accident
        string accidentLocation, affectedLane;
        cout << "Enter the location of the accident: ";
        cin >> accidentLocation;

        cout << "Which lane is affected (e.g., Left Turn, Right Turn, Straight)? ";
        cin >> affectedLane;

        // Log the accident event with timestamp
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << "Accident detected at " << accidentLocation << " on lane " << affectedLane << ".\n";
        cout << "Incident logged at: " << dt << endl;

        // Simulate extending the green signal for the affected lane
        int extensionTime;
        cout << "Enter how many additional seconds to extend the green signal for lane " << affectedLane << ": ";
        cin >> extensionTime;

        // Check if emergency vehicles are approaching
        bool emergencyVehicleApproaching;
        cout << "Are emergency vehicles approaching? (1 for Yes, 0 for No): ";
        cin >> emergencyVehicleApproaching;

        if (emergencyVehicleApproaching) {
            cout << "Emergency vehicles approaching. Giving priority to them.\n";
            extensionTime += 10;  // Extend the green signal for emergency vehicles
        }

        // Log the extended green signal duration
        cout << "Extending green signal for " << affectedLane << " for " << extensionTime << " seconds.\n";

        // Simulating time for the green signal extension without this_thread::sleep_for
        for (int i = extensionTime; i > 0; i--) {
            cout << "Time remaining for green light on " << affectedLane << ": " << i << " seconds.\n";

            // Using clock() to simulate 1 second delay
            clock_t start_time = clock();
            while (clock() < start_time + CLOCKS_PER_SEC) {
                // Busy-wait to simulate a 1-second delay
            }
        }
        cout << "Green light extended for " << affectedLane << ". Accident clearance in progress.\n";

        // Notify authorities about the accident
        cout << "Sending accident report to authorities...\n";

        // Simulate time taken to send the report using clock()
        clock_t start_time_report = clock();
        while (clock() < start_time_report + 2 * CLOCKS_PER_SEC) {
            // Busy-wait to simulate the 2-second delay for sending the report
        }

        cout << "Accident report sent successfully.\n";

        // Simulate clearance of accident
        cout << "Accident cleared. Resuming normal traffic flow.\n";

    } else {
        cout << "No accident detected. Normal lane operations.\n";
    }
}
// 19. Integration with Smart Vehicles (V2I Communication)
void communicateWithSmartVehicle() {
    bool vehicleConnected;
    cout << "Is the smart vehicle connected? (1 for Yes, 0 for No): ";
    cin >> vehicleConnected;

    if (vehicleConnected) {
        // Gather more details about the smart vehicle and its connection
        string vehicleType;
        cout << "Enter the type of smart vehicle (e.g., Car, Truck, Bus): ";
        cin >> vehicleType;

        string communicationProtocol;
        cout << "Enter the communication protocol (e.g., V2X, 5G, Bluetooth): ";
        cin >> communicationProtocol;

        cout << "Smart Vehicle (" << vehicleType << ") connected using " << communicationProtocol << " protocol.\n";

        // Simulate the data exchange with the smart vehicle
        string trafficLightStatus = "Green";  // This can be dynamic based on the real-time signal status
        cout << "Sending traffic light status: " << trafficLightStatus << " to smart vehicle.\n";

        // Simulate a response from the smart vehicle
        string vehicleResponse;
        cout << "Smart Vehicle Response: (e.g., 'Proceed', 'Stop', 'Route Update') ";
        cin >> vehicleResponse;

        // Log the communication for future reference
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << "Communication log at: " << dt << endl;
        cout << "Vehicle Response: " << vehicleResponse << endl;

        // Based on response, adjust traffic signal (if needed)
        if (vehicleResponse == "Proceed") {
            cout << "Allowing vehicle " << vehicleType << " to pass.\n";
        } else if (vehicleResponse == "Stop") {
            cout << "Traffic light status: " << trafficLightStatus << " will be kept.\n";
        } else if (vehicleResponse == "Route Update") {
            cout << "Requesting alternative route for vehicle.\n";
        } else {
            cout << "Invalid response received. No change to traffic signal.\n";
        }

        // Simulate sending traffic signal status updates
        cout << "Sending traffic signal status updates to connected smart vehicle...\n";

        // Replace sleep with clock() function for delay simulation
        clock_t start_time = clock();
        while (clock() < start_time + 2 * CLOCKS_PER_SEC) {
            // Busy-wait to simulate 2-second delay
        }

        cout << "Status updates sent successfully.\n";

    } else {
        cout << "No Smart Vehicle Detected.\n";
    }
}

// 20. Traffic Signal Health Monitoring System
struct TrafficSignal {
    string location;
    bool isFunctional;
    string lastMaintenanceDate; // Track last maintenance date
    string malfunctionType; // Type of malfunction (if any)
};

void monitorSignalHealth() {
    int numSignals;
    cout << "Enter the number of traffic signals to monitor: ";
    cin >> numSignals;

    vector<TrafficSignal> signals(numSignals);

    // Collecting data for multiple traffic signals
    for (int i = 0; i < numSignals; i++) {
        cout << "\nEnter details for Signal " << i + 1 << ":\n";
        cout << "Location: ";
        cin >> signals[i].location;
        cout << "Is the signal functional? (1 for Yes, 0 for No): ";
        cin >> signals[i].isFunctional;

        // If the signal is malfunctioning, ask for the malfunction type and last maintenance date
        if (!signals[i].isFunctional) {
            cout << "Enter the type of malfunction (e.g., 'Power Outage', 'Signal Flashes'): ";
            cin >> signals[i].malfunctionType;

            // Ask for last maintenance date if the signal is malfunctioning
            cout << "Enter the last maintenance date (format: YYYY-MM-DD): ";
            cin >> signals[i].lastMaintenanceDate;

            // Suggest maintenance based on the last maintenance date
            time_t current_time = time(0);
            struct tm *now = localtime(&current_time);
            int currentYear = now->tm_year + 1900; // Current year

            int lastMaintenanceYear = stoi(signals[i].lastMaintenanceDate.substr(0, 4)); // Extract the year from the date

            if (currentYear - lastMaintenanceYear >= 1) {
                cout << "Maintenance due for Signal at " << signals[i].location << "!\n";
            } else {
                cout << "Signal at " << signals[i].location << " was recently maintained.\n";
            }
        }
    }

    // Displaying health status for all signals
    cout << "\n--- Traffic Signal Health Report ---\n";
    for (const auto& signal : signals) {
        if (signal.isFunctional) {
            cout << "Signal at " << signal.location << " is functional.\n";
        } else {
            cout << "Signal at " << signal.location << " is malfunctioning! Type: " << signal.malfunctionType
                 << ", Last Maintenance Date: " << signal.lastMaintenanceDate << endl;
        }
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
                srand(time(0));  // Seed for random traffic generation
                synchronizeTrafficLights();
                break;
            case 5:
                srand(time(0));
                detectMalfunction();
                break;
            case 6:
                srand(time(0));
                predictTrafficDensity();
                break;
            case 7:
                laneSpecificSignal();
                break;
            case 8:
                srand(time(0));
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
