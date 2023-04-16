//
// Created by Rebecca Diaz on 3/6/23.
//

#include "AirportData.h"

// Constructor
AirportData::AirportData(std::string& airportInitials, std::string& airportCity,
                         std::string& airportState, std::string& airportName) {
    this->airportInitials = airportInitials;
    this->airportCity = airportCity;
    this->airportState = airportState;
    this->airportName = airportName;

    // Set default values, will be updated later
    this->year = 0;
    this->month = 0;
    totalArrivals = 0;
    delaysOver15 = 0;
    carrierDelays = 0.0;
    weatherDelays = 0.0;
    nasDelays = 0.0;
    securityDelays = 0.0;
    lateAircraftDelays = 0.0;
    totalCancellations = 0;
    totalDiverted = 0;
    totalDelayTime = 0;
    carrierDelayTime = 0;
    weatherDelayTime = 0;
    nasDelayTime = 0;
    securityDelayTime = 0;
    lateAircraftDelayTime = 0;
}

// MUTATORS

// Update month/year data
void AirportData::setMonthYear(int year, int month) {
    this->year = year;
    this->month = month;
}

// Update delay data
void AirportData::setDelayInfo(int totalArrivals, int delaysOver15, double carrierDelays, double weatherDelays,
                               double nasDelays, double securityDelays, double lateAircraftDelays,
                               int totalCancellations, int totalDiverted) {
    this->totalArrivals = totalArrivals;
    this->delaysOver15 = delaysOver15;
    this->carrierDelays = carrierDelays;
    this->weatherDelays = weatherDelays;
    this->nasDelays = nasDelays;
    this->securityDelays = securityDelays;
    this->lateAircraftDelays = lateAircraftDelays;
    this->totalCancellations = totalCancellations;
    this->totalDiverted = totalDiverted;
}

// Update time data
void AirportData::setTimeInfo(int totalDelayTime, int carrierDelayTime, int weatherDelayTime, int nasDelayTime,
                              int securityDelayTime, int lateAircraftDelayTime) {

    this->totalDelayTime = totalDelayTime;
    this->carrierDelayTime = carrierDelayTime;
    this->weatherDelayTime = weatherDelayTime;
    this->nasDelayTime = nasDelayTime;
    this->securityDelayTime = securityDelayTime;
    this->lateAircraftDelayTime = lateAircraftDelayTime;
}

//**additions
void AirportData::setDelaysOver15(int delaysOver15) {
    this->delaysOver15 = delaysOver15;
}

int AirportData::getDelayedFlights() const {
    return delaysOver15;
}

int AirportData::getTotalFlights() const {
    return totalArrivals;
}

const std::string& AirportData::getAirportCity() const {
    return airportCity;
}



