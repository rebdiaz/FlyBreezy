#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include "AirportData.h"
#include "Airline.h"
#include <vector>
#include <unordered_map>
#include "sorting.h"


bool enterCity(std::string& userInput, std::map<std::string, Airline>& airlinesMap);
bool enterAirline(std::string& userInput, std::map<std::string, Airline>& airlinesMap);
void calculateCityDelayLikelihoods(const std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& cityDelayLikelihoods);
void calculateAirlineDelayLikelihoods(const std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& airlineDelayLikelihoods);
void calculateAirlineDelayForCity(const std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& airlineDelayLikelihoods, std::string destCity);

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
    std::unordered_map<std::string, double> cityDelayLikelihoods;
    std::unordered_map<std::string, double> airlineDelayLikelihoods;
    std::unordered_map<std::string, double> delaysForOneCity;
    std::chrono::system_clock::time_point start, end;
    std::chrono::system_clock::duration timeToRun;

    while (option != "-1") {
        std::cout << "FlyBreezy: View delay likelihood based on:" << std::endl;
        std::cout << "1 - Destination City" << std::endl;
        std::cout << "2 - Airline" << std::endl;
        std::cout << "3 - Entering One Destination City" << std::endl;
        std::cout << "Enter -1 to Exit" << std::endl;
        std::cin >> option;

        int choice;
        if (option == "1") {
            std::cout << "Choose sorting method: " << std::endl;
            std::cout << "1. Merge sort" << std::endl;
            std::cout << "2. Quick sort" << std::endl;
            std::cin >> choice;

            switch (choice) {
                case 1: // sort data by city likelihood using merge sort

                    calculateCityDelayLikelihoods(airlinesMap, cityDelayLikelihoods);
                    start = std::chrono::system_clock::now();
                    //Call to sort
                    printSortedCityDelayLikelihoods(cityDelayLikelihoods);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for MergeSort: " << timeToRun.count() << " milliseconds" << std::endl << std::endl;
                    break;
                case 2: // sort data by city likelihood using other sorting method
                    // Implement the other sorting method here...
                    calculateCityDelayLikelihoods(airlinesMap, cityDelayLikelihoods);
                    start = std::chrono::system_clock::now();
                    /// Other sorting method call HERE
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for QuickSort: " << timeToRun.count() << " milliseconds" << std::endl << std::endl;
                    break;
            }
        } else if (option == "2") {
            std::cout << "Choose sorting method: " << std::endl;
            std::cout << "1. Merge sort" << std::endl;
            std::cout << "2. Quick sort" << std::endl;
            std::cin >> choice;

            switch (choice) {
                case 1: // sort data by Airline likelihood using merge sort

                    calculateAirlineDelayLikelihoods(airlinesMap, airlineDelayLikelihoods);
                    start = std::chrono::system_clock::now();
                    //Call to sort
                    printSortedAirlineDelayLikelihoods(airlineDelayLikelihoods);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for MergeSort: " << timeToRun.count() << " milliseconds" << std::endl << std::endl;


                    break;
                case 2: // sort data by airline likelihood using other sorting method
                    // Implement the other sorting method here...
                    calculateAirlineDelayLikelihoods(airlinesMap, airlineDelayLikelihoods);
                    start = std::chrono::system_clock::now();
                    /// Other sorting method call HERE
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for QuickSort: " << timeToRun.count() << " milliseconds" << std::endl << std::endl;

                    break;
            }
        }  else if(option == "3"){
            std::cout << "Enter your destination city with no spaces:" << std::endl;
            std::string destCity;
            std::cin >> destCity;

            //Fix formatting
            for(int k = 1; k < destCity.length(); k++){
                if(isupper(destCity.at(k))){
                    destCity.insert(k, 1, ' ');
                    k++;
                }
            }

            calculateCityDelayLikelihoods(airlinesMap, cityDelayLikelihoods);
            // Determine if city exists
            bool cityFound = false;
            auto iter = cityDelayLikelihoods.begin();
            for(; iter != cityDelayLikelihoods.end(); iter++){
                //City found! Calculate airline data for that city
                if(iter->first == destCity){
                    std::cout << destCity << ": " << std::endl;
                    calculateAirlineDelayForCity(airlinesMap, delaysForOneCity, destCity);
                    cityFound = true;
                    break;
                }
                auto endMap = iter;
                endMap++;
                if(endMap == cityDelayLikelihoods.end()){
                    std::cout << "City not found." << std::endl;
                }
            }

            choice = -1;
            if(cityFound){
                std::cout << "Choose sorting method: " << std::endl;
                std::cout << "1. Merge sort" << std::endl;
                std::cout << "2. Quick sort" << std::endl;
                std::cin >> choice;
            }

            switch (choice) {
                case 1: // sort data by city likelihood using merge sort

                    start = std::chrono::system_clock::now();
                    //Call to sort
                    printSortedAirlineDelayLikelihoods(delaysForOneCity);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for MergeSort: " << timeToRun.count() << " milliseconds" << std::endl << std::endl;
                    break;
                case 2: // sort data by city likelihood using other sorting method
                    // Implement the other sorting method here...
                    start = std::chrono::system_clock::now();
                    /// Other sorting method call HERE
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for QuickSort: " << timeToRun.count() << " milliseconds" << std::endl << std::endl;
                    break;
            }

        } else if(option != "-1"){
            std::cout << "Please enter a valid option (1, 2, 3, -1)" << std::endl;
        }
    }

    return 0;

}

//**new additions
//City
void calculateCityDelayLikelihoods(const std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& cityDelayLikelihoods) {
    //maps a city name to a pair of integers
    //first int is the total number of delayed flights for the city, second int is the total number of flights for the city
    std::unordered_map<std::string, std::pair<int, int>> cityDelaysAndTotalFlights;

    //declare const ref airlineEntry to iterate through the airlinesMap

    for (const auto& airlineEntry : airlinesMap) {
        //get an Airline object to use in accessing the monthlyAirportData vector for the airline
        const Airline& airlineDelay = airlineEntry.second;

        //For each Airline object, iterate through its MonthlyAirportData
        for (const auto& airportData : airlineDelay.getMonthlyAirportData()) {
            const std::string& city = airportData.getAirportCity(); //Extract city name from the AirportData object

            //update the cityDelaysAndTotalFlights unordered_map for the current city:
            //updating the total number of delayed flights and total number of flights for each city
            cityDelaysAndTotalFlights[city].first += airportData.getDelayedFlights();
            cityDelaysAndTotalFlights[city].second += airportData.getTotalFlights();
        }
    }
    //iterate through the map
    for (const auto& entry : cityDelaysAndTotalFlights) {
        // Extract city name, number of delayed flights, and the total number of flights
        const std::string& city = entry.first;
        int delayedFlights = entry.second.first;
        int totalFlights = entry.second.second;

        //Store the delay likelihood in a map with the city name as the key
        cityDelayLikelihoods[city] = (static_cast<double>(delayedFlights) / totalFlights) * 100;

    }
}

//Airline
void calculateAirlineDelayLikelihoods(const std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& airlineDelayLikelihoods) {

    for (const auto& airlineEntry : airlinesMap) {
        //For each airline, get the airline name and the Airline delay object
        const std::string& airlineName = airlineEntry.first;
        const Airline& airlineDelay = airlineEntry.second;

        //initialize delayedFlights and totalFlights
        int delayedFlights = 0;
        int totalFlights = 0;

        //iterate through the AirportData objects for each airline using getMonthlyAirportData() member function
        for (const auto& airportData : airlineDelay.getMonthlyAirportData()) {
            //adds the delayed flights and total flights for each airport
            delayedFlights += airportData.getDelayedFlights();
            totalFlights += airportData.getTotalFlights();
        }
        //calculates the delay likelihood after processing all airport data for the airline
        //delay likelihood is then stored in a map
        //airlineName is the key and the delay likelihood is the value.
        airlineDelayLikelihoods[airlineName] = (static_cast<double>(delayedFlights) / totalFlights) * 100;
    }
}

void calculateAirlineDelayForCity(const std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& airlineDelayLikelihoods, std::string destCity){
    for (const auto& airlineEntry : airlinesMap) {
        //For each airline, get the airline name and the Airline delay object
        const std::string& airlineName = airlineEntry.first;
        const Airline& airlineDelay = airlineEntry.second;

        //initialize delayedFlights and totalFlights
        int delayedFlights = 0;
        int totalFlights = 0;

        //iterate through the AirportData objects for each airline using getMonthlyAirportData() member function
        for (const auto& airportData : airlineDelay.getMonthlyAirportData()) {
            //adds the delayed flights and total flights IF its in the destination city
            if(airportData.getAirportCity() == destCity){
                delayedFlights += airportData.getDelayedFlights();
                totalFlights += airportData.getTotalFlights();
            }
        }
        //calculates the delay likelihood after processing all airport data for the airline
        //delay likelihood is then stored in a map
        //airlineName is the key and the delay likelihood is the value.
        if(totalFlights != 0){
            airlineDelayLikelihoods[airlineName] = (static_cast<double>(delayedFlights) / totalFlights) * 100;
        }
    }

}

