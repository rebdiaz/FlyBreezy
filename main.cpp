#include <iostream>
#include <fstream>
#include <map>
#include "AirportData.h"
#include "Airline.h"


/*TO DO
 * 1.
 * 2.
 * 3.
 * 4. Start writing the menu, consider adding the total time for each airport??
 * 5. Look into bridges, SFML
 */

bool enterCity(std::string& userInput, std::map<std::string, Airline>& airlinesMap);
bool enterAirline(std::string& userInput, std::map<std::string, Airline>& airlinesMap);

int main() {
    // Initialize Storage and input stream objects
    std::map<std::string, Airline> airlinesMap;
    //std::vector<std::string> destinations;
    std::fstream airlineData("Airline_Delay_Cause.csv", std::ios_base::in);
    std::string buffer;

    getline(airlineData, buffer, '\n'); // Ignore header of csv
    // Read data until the file is empty
    while(getline(airlineData, buffer, ',')){
        // Read year and month data
        int year = std::stoi(buffer);
        getline(airlineData, buffer, ',');
        int month = std::stoi(buffer);

        // Read Airline data
        getline(airlineData, buffer, ',');
        std::string carrier = buffer;
        getline(airlineData, buffer, ',');
        std::string airlineName = buffer;

        // Read Airport data
        getline(airlineData, buffer, ',');
        std::string airportInitials = buffer;
        getline(airlineData, buffer, ',');
        buffer.erase(buffer.begin()); //Get rid of quotation character
        std::string airportCity = buffer;
        getline(airlineData, buffer, ':');
        buffer.erase(buffer.begin()); //Get rid of space character
        std::string airportState = buffer;
        getline(airlineData, buffer, ',');
        buffer.pop_back(); //Get rid of quotation character
        buffer.erase(buffer.begin()); //Get rid of space character
        std::string airportName = buffer;

        // Create airport data object and set month/year data
        AirportData data(airportInitials, airportCity, airportState, airportName);
        data.setMonthYear(year, month);


        // Read delay data
        getline(airlineData, buffer, ',');
        if(buffer.empty()){
            getline(airlineData, buffer, '\n');
            continue; // A handful of rows are not complete, so they are ignored
        }

        int totalArrivals = std::stoi(buffer);
        getline(airlineData, buffer, ',');
        if(buffer.empty()){
            getline(airlineData, buffer, '\n');
            continue; // A handful of rows are not complete, so they are ignored
        }

        int delaysOver15 = std::stoi(buffer);
        getline(airlineData, buffer, ',');
        double carrierDelays = std::stod(buffer);
        getline(airlineData, buffer, ',');
        double weatherDelays = std::stod(buffer);
        getline(airlineData, buffer, ',');
        double nasDelays = std::stod(buffer);
        getline(airlineData, buffer, ',');
        double securityDelays = std::stod(buffer);
        getline(airlineData, buffer, ',');
        double lateAircraftDelays = std::stod(buffer);
        getline(airlineData, buffer, ',');
        int totalCancellations = std::stoi(buffer);
        getline(airlineData, buffer, ',');
        int totalDiverted = std::stoi(buffer);

        // Set delay data
        data.setDelayInfo(totalArrivals, delaysOver15, carrierDelays, weatherDelays, nasDelays,
                          securityDelays, lateAircraftDelays, totalCancellations, totalDiverted);

        // Read time data
        getline(airlineData, buffer, ',');
        int totalDelayTime = std::stoi(buffer);
        getline(airlineData, buffer, ',');
        int carrierDelayTime = std::stoi(buffer);
        getline(airlineData, buffer, ',');
        int weatherDelayTime = std::stoi(buffer);
        getline(airlineData, buffer, ',');
        int nasDelayTime = std::stoi(buffer);
        getline(airlineData, buffer, ',');
        int securityDelayTime = std::stoi(buffer);
        getline(airlineData, buffer, '\n');
        int lateAircraftDelayTime = std::stoi(buffer);

        // Set time data
        data.setTimeInfo(totalDelayTime, carrierDelayTime, weatherDelayTime, nasDelayTime,
                         securityDelayTime, lateAircraftDelayTime);

        // Add the airport data to the map
        auto airlineIterator = airlinesMap.find(airlineName);
        // If the airline is not found in the map, create a new airline and add the data
        if( airlineIterator == airlinesMap.end() ){
            airlinesMap.emplace(airlineName, Airline(carrier, airlineName));
            airlinesMap.at(airlineName).addAirportData(data);
        } else {
            // If the airline already exists in the map, add the new airport data to this airline
            airlinesMap.at(airlineName).addAirportData(data);
        }
    }

    std::string option = "-2";
    while(option != "-1"){
        std::cout << "FlyBreezy: Pick the Best Airline" << std::endl;
        std::cout << "1 - Destination City" << std::endl;
        std::cout << "2 - Airline" << std::endl;
        std::cout << "3 - Destination Airport" << std::endl;
        std::cout << "Enter -1 to Exit" << std::endl;
        std::cin >> option;

        std::string userInput = "";
        if(option == "1"){
            // Find top 5 airlines for the destination city
            sort("city");

        } else if (option == "2"){
            // Ask user for an airline until a valid one is entered
            getline(std::cin, userInput);
            while(enterAirline(userInput, airlinesMap)){
                auto airlineIterator = airlinesMap.begin();
                std::cout << "Airline not found! Try one of these: " << std::endl;
                // Print out all the valid airlines
                for(; airlineIterator != airlinesMap.end(); airlineIterator++){
                        std::cout << airlineIterator->first << std::endl;
                }
            }

            // Find top 5 destinations for the airline

        } else if(option == "3"){
            // Find top 5 airlines for the destination airport
        }  else {
            std::cout << "Please enter a valid option (1, 2, 3, -1)" << std::endl;
        }
    }


    return 0;
}

// Asks for user inputs and returns whether the city does not exist in the map


// Asks for an airline and returns whether the airline does not exist in the map, 
bool enterAirline(std::string& userInput, std::map<std::string, Airline>& airlinesMap){
    std::cout << "Enter an Airline: ";
    getline(std::cin, userInput);
    auto airlineIterator = airlinesMap.find(userInput);
    return airlineIterator == airlinesMap.end();
}
