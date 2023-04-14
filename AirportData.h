//
// Created by Rebecca Diaz on 3/6/23.
//

#pragma once
#include <string>

class AirportData {
    // Attributes
    int year;
    int month;
    std::string airportInitials;
    std::string airportCity;
    std::string airportState;
    std::string airportName;
    int totalArrivals;
    int delaysOver15;
    double carrierDelays;
    double weatherDelays;
    double nasDelays;
    double securityDelays;
    double lateAircraftDelays;
    int totalCancellations;
    int totalDiverted;
    int totalDelayTime;
    int carrierDelayTime;
    int weatherDelayTime;
    int nasDelayTime;
    int securityDelayTime;
    int lateAircraftDelayTime;
    //*addition
    int delayedFlights;

public:
    //**new additions
    int getDelayedFlights() const;
    int getTotalFlights() const;
    const std::string& getAirportCity() const;
    
    // Constructor
    AirportData(std::string& airportInitials, std::string& airportCity,
                std::string& airportState, std::string& airportName);

    // Mutators
    void setMonthYear(int year, int month);
    void setDelayInfo(int totalArrivals, int delaysOver15, double carrierDelays, double weatherDelays,
                      double nasDelays, double securityDelays, double lateAircraftDelays, int totalCancellations,
                      int totalDiverted);
    void setTimeInfo(int totalDelayTime, int carrierDelayTime, int weatherDelayTime, int nasDelayTime,
                     int securityDelayTime, int lateAircraftDelayTime);

};


