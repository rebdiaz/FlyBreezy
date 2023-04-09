//
// Created by Rebecca Diaz on 3/8/23.
//

#include "Airline.h"

// Constructor,
Airline::Airline(std::string& carrier, std::string& airline) {
    this->carrier = carrier;
    this->airline = airline;
}

// MUTATORS

// Add given data to the vector of data
void Airline::addAirportData(AirportData data) {
    monthlyAirportData.push_back(data);
}
