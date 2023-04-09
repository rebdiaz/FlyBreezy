//
// Created by Rebecca Diaz on 3/8/23.
//

#pragma once
#include <string>
#include <vector>
#include "AirportData.h"

class Airline {
    // Attributes
    std::string carrier;
    std::string airline;

    std::vector<AirportData> monthlyAirportData; //Unsorted
    std::vector<AirportData> monthlyAirportDataSortedByCity;
    std::vector<AirportData> monthlyAirportDataSortedByAirport;

public:
    // Constructor
    Airline(std::string& carrier, std::string& airline);

    // Mutators
    void addAirportData(AirportData data);

    // Sorting

};



