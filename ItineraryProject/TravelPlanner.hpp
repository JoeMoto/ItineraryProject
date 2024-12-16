#ifndef TRAVELPLANNER_HPP
#define TRAVELPLANNER_HPP

#include "Traveler.hpp"
#include "Itinerary.hpp"
#include <string>
#include <chrono>

using namespace std;

class TravelPlanner : public Traveler
{
public:
    TravelPlanner(const string &travelerID, const string &firstName, const string &lastName)
        : Traveler(travelerID, firstName, lastName) {}

    Itinerary createItinerary(const string &startDate, const string &endDate)
    {
        string itineraryID = "ITIN-" + to_string(chrono::system_clock::now().time_since_epoch().count());
        return Itinerary(itineraryID, this->travelerID, startDate, endDate);
    }
};

#endif
