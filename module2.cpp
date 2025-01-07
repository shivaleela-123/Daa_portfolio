#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Global variables
int trafficDensity = 0;
int temperature = 25; // Starting temperature in Celsius
int humidity = 50;    // Percentage of humidity
int pollutionLevel = 20; // Pollution level in percentage
string weatherCondition = "Clear";  // Initial weather condition

// Function to simulate traffic density
void generateTrafficDensity() {
    trafficDensity = rand() % 101;  // Random density between 0 and 100
    cout << "Traffic Density: " << trafficDensity << "%" << endl;
}

// Function to simulate weather based on traffic
void simulateWeather() {
    if (trafficDensity > 70) {
        temperature += 5; // Higher temperature due to heavy traffic
        humidity += 10;   // Increased humidity with high traffic
        pollutionLevel += 15;  // Increased pollution with high traffic
        weatherCondition = "Smoggy";
    } else if (trafficDensity < 30) {
        temperature -= 3; // Lower temperature with less traffic
        humidity -= 5;    // Decreased humidity with less traffic
        pollutionLevel -= 5; // Decreased pollution
        weatherCondition = "Clear";
    } else {
        temperature += 2;
        humidity += 2;
        pollutionLevel += 5; // Moderate pollution with moderate traffic
        weatherCondition = "Partly Cloudy";
    }

    // Display the simulated weather based on traffic density
    cout << "Current Weather: " << weatherCondition << endl;
    cout << "Temperature: " << temperature << "°C" << endl;
    cout << "Humidity: " << humidity << "%" << endl;
    cout << "Pollution Level: " << pollutionLevel << "%" << endl;
}

// Function to simulate random weather effects
void randomWeatherEffects() {
    int randomEffect = rand() % 5; // Random number between 0 and 4
    if (randomEffect == 0) {
        cout << "Clear weather. No rain." << endl;
    } else if (randomEffect == 1) {
        cout << "Light rain expected." << endl;
        temperature -= 2;
    } else if (randomEffect == 2) {
        cout << "Heavy rain expected. Traffic may slow down further." << endl;
        temperature -= 4;
        humidity += 20;
    } else if (randomEffect == 3) {
        cout << "Snowstorm expected. Temperature will drop significantly." << endl;
        temperature -= 10;
        humidity += 30;
        weatherCondition = "Snowstorm";
    } else {
        cout << "Foggy conditions. Visibility reduced." << endl;
        temperature -= 1;
        humidity += 15;
        weatherCondition = "Foggy";
    }
}

// Function to simulate hourly changes in weather and traffic
void hourlyWeatherChange(int hour) {
    cout << "\nHour " << hour << " Weather and Traffic Update:" << endl;
    generateTrafficDensity();
    simulateWeather();
    randomWeatherEffects();
}

// Function to predict the next few hours of weather
void forecastWeather(int hours) {
    cout << "\nForecast for the next " << hours << " hours:" << endl;
    for (int i = 1; i <= hours; i++) {
        cout << "\nHour " << i << ": ";
        int forecastTraffic = rand() % 101;
        cout << "Traffic Density: " << forecastTraffic << "%" << endl;
        if (forecastTraffic > 70) {
            cout << "Heavy traffic, expect high temperatures and pollution." << endl;
        } else if (forecastTraffic < 30) {
            cout << "Light traffic, expect cooler temperatures and lower pollution." << endl;
        } else {
            cout << "Moderate traffic, mild weather expected." << endl;
        }
    }
}

// Function to simulate a long-term weather pattern over multiple days
void dailyWeatherSimulation(int days) {
    for (int day = 1; day <= days; day++) {
        cout << "\nDay " << day << " Weather and Traffic Update:" << endl;
        generateTrafficDensity();
        simulateWeather();
        randomWeatherEffects();
    }
}

// Function to display the current weather report
void displayWeatherReport() {
    cout << "\nCurrent Weather Report:" << endl;
    cout << "Temperature: " << temperature << "°C" << endl;
    cout << "Humidity: " << humidity << "%" << endl;
    cout << "Pollution Level: " << pollutionLevel << "%" << endl;
    cout << "Current Condition: " << weatherCondition << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed for random number generation

    int choice, hours, days;

    // Main menu for the weather simulation
    do {
        cout << "\nWeather Simulation Menu:" << endl;
        cout << "1. Simulate Hourly Weather Changes" << endl;
        cout << "2. Forecast Weather for the Next Few Hours" << endl;
        cout << "3. Simulate Daily Weather Over Multiple Days" << endl;
        cout << "4. Display Current Weather Report" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the hour (1-24): ";
                cin >> hours;
                hourlyWeatherChange(hours);
                break;

            case 2:
                cout << "Enter the number of hours to forecast: ";
                cin >> hours;
                forecastWeather(hours);
                break;

            case 3:
                cout << "Enter the number of days to simulate: ";
                cin >> days;
                dailyWeatherSimulation(days);
                break;

            case 4:
                displayWeatherReport();
                break;

            case 5:
                cout << "Exiting the simulation..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
