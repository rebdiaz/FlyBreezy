#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include "AirportData.h"
#include "Airline.h"
#include <vector>
#include <unordered_map>
#include "sorting.h"



void calculateCityDelay(std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& cityDelayCalc);
void calculateAirlineDelay(std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& airlineDelayCalc);
void calculateAirlineDelayForCity(std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& airlineDelayCalc, std::string destCity);

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
    std::unordered_map<std::string, double> cityDelayCalc;
    std::unordered_map<std::string, double> airlineDelayCalc;
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

                    calculateCityDelay(airlinesMap, cityDelayCalc);
                    start = std::chrono::system_clock::now();
                    //Call to sort
                    sortedCityDelayM(cityDelayCalc);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for MergeSort: " << timeToRun.count() << " nanoseconds" << std::endl << std::endl;
                    break;
                case 2: // sort data by city likelihood using other sorting method
                    // Implement the other sorting method here...
                    calculateCityDelay(airlinesMap, cityDelayCalc);
                    start = std::chrono::system_clock::now();
                    /// Other sorting method call HERE
                    sortedCityDelayQ(cityDelayCalc);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for QuickSort: " << timeToRun.count() << " nanoseconds" << std::endl << std::endl;
                    break;
            }
        } else if (option == "2") {
            std::cout << "Choose sorting method: " << std::endl;
            std::cout << "1. Merge sort" << std::endl;
            std::cout << "2. Quick sort" << std::endl;
            std::cin >> choice;

            switch (choice) {
                case 1: // sort data by Airline likelihood using merge sort

                    calculateAirlineDelay(airlinesMap, airlineDelayCalc);
                    start = std::chrono::system_clock::now();
                    //Call to sort
                    sortedAirlineDelayM(airlineDelayCalc);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for MergeSort: " << timeToRun.count() << " nanoseconds" << std::endl << std::endl;


                    break;
                case 2: // sort data by airline likelihood using other sorting method
                    // Implement the other sorting method here...
                    calculateAirlineDelay(airlinesMap, airlineDelayCalc);
                    start = std::chrono::system_clock::now();
                    /// Other sorting method call HERE
                    sortedAirlineDelayQ(airlineDelayCalc);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for QuickSort: " << timeToRun.count() << " nanoseconds" << std::endl << std::endl;
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

            calculateCityDelay(airlinesMap, cityDelayCalc);
            // Determine if city exists
            bool cityFound = false;
            auto iter = cityDelayCalc.begin();
            for(; iter != cityDelayCalc.end(); iter++){
                //City found! Calculate airline data for that city
                if(iter->first == destCity){
                    std::cout << destCity << ": " << std::endl;
                    calculateAirlineDelayForCity(airlinesMap, delaysForOneCity, destCity);
                    cityFound = true;
                    break;
                }
                auto endMap = iter;
                endMap++;
                if(endMap == cityDelayCalc.end()){
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
                    sortedAirlineDelay(delaysForOneCity);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for MergeSort: " << timeToRun.count() << " nanoseconds" << std::endl << std::endl;
                    break;
                case 2: // sort data by city likelihood using other sorting method
                    // Implement the other sorting method here...
                    start = std::chrono::system_clock::now();
                    /// Other sorting method call HERE
                    sortedAirlineDelayQ(delaysForOneCity);
                    end = std::chrono::system_clock::now();
                    timeToRun = end - start;
                    std::cout << "Time for QuickSort: " << timeToRun.count() << " nanoseconds" << std::endl << std::endl;
                    break;
            }

        } else if(option != "-1"){
            std::cout << "Please enter a valid option (1, 2, 3, -1)" << std::endl;
        }
    }

    return 0;

}

//**new additions

void calculateCityDelay(std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& cityDelayCalc) {

    std::unordered_map<std::string, std::pair<int, int>> trackCityMap; //map to keep track of city, total number of delayed and total number of flights

    for (auto& airlinedata : airlinesMap) {
        Airline& airlineDelay = airlinedata.second;

        for (auto& airport_iter : airlineDelay.getMonthlyAirportData()) { //iterate through MonthlyAirportData for each airline
            std::string& city = const_cast<std::string &>(airport_iter.getAirportCity());        //Get the city

            trackCityMap[city].first += airport_iter.getDelayedFlights(); // update to get the total number of delayed flights
            trackCityMap[city].second += airport_iter.getTotalFlights(); //update to get the total number of flights
        }
    }

    for (auto& city_iter : trackCityMap) { //get the city, number of delayed and total flights
        std::string& city = const_cast<std::string &>(city_iter.first);
        int delayedFlights = city_iter.second.first;
        int totalFlights = city_iter.second.second;

        cityDelayCalc[city] = (static_cast<double>(delayedFlights) / totalFlights) * 100; //calculate the percentage delay and store in map

    }
}
//Airline
void calculateAirlineDelay(std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& airlineDelayCalc) {
    for (auto& airlinedata : airlinesMap) {
        std::string& airlineName = const_cast<std::string &>(airlinedata.first); //get airline
        Airline& airlineDelay = airlinedata.second;   //get the delay

        int delayedFlights = 0; //initialize variables for delayed and total flight data for airline
        int totalFlights = 0;

        for (auto& airport_iter : airlineDelay.getMonthlyAirportData()) { // get the total delayed and total flights for calculation

            delayedFlights += airport_iter.getDelayedFlights();
            totalFlights += airport_iter.getTotalFlights();
        }
        airlineDelayCalc[airlineName] = (static_cast<double>(delayedFlights) / totalFlights) * 100; //calculate the percentage delay and store in the map
    }
}
void calculateAirlineDelayForCity(std::map<std::string, Airline>& airlinesMap, std::unordered_map<std::string, double>& airlineDelayCalc, std::string destCity){
    for (auto& airlinedata : airlinesMap) {
        //For each airline, get the airline name and the Airline delay
        std::string& airlineName = const_cast<std::string &>(airlinedata.first);
        Airline& airlineDelay = airlinedata.second;

        //initialize delayedFlights and totalFlights
        int delayedFlights = 0;
        int totalFlights = 0;

        for (auto& airport_iter : airlineDelay.getMonthlyAirportData()) {
            //adds the delayed flights and total flights IF its in the destination city
            if(airport_iter.getAirportCity() == destCity){
                delayedFlights += airport_iter.getDelayedFlights();
                totalFlights += airport_iter.getTotalFlights();
            }
        }
        //calculates the delay likelihood after processing all airport data for the airline
        //delay likelihood is then stored in a map
        //airlineName is the key and the delay likelihood is the value.
        if(totalFlights != 0){
            airlineDelayCalc[airlineName] = (static_cast<double>(delayedFlights) / totalFlights) * 100;
        }
    }
}
