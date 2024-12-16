#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <string>
#include <vector>
#include "Traveler.hpp"
#include "TravelPlanner.hpp"
#include "Itinerary.hpp"
#include "ItineraryDetail.hpp"

using namespace std;

class DataHandler
{
public:
    static string TRAVELER_FILE;
    static string ITINERARY_FILE;
    static string ITINERARY_DETAIL_FILE;
    static const char DELIM;

    static void saveTraveler(const Traveler &traveler);
    static Traveler *getTraveler(const string &travelerID);

    static void updateTraveler(const Traveler &traveler);
    static void saveItinerary(const Itinerary &itinerary);
    static Itinerary *getItinerary(const string &itineraryID);
    static vector<Itinerary> getItinerariesByTravelerID(const string &travelerID);

    static void saveItineraryDetail(const ItineraryDetail &detail);
    static vector<ItineraryDetail> getItineraryDetails(const string &itineraryID);

    static void updateItinerary(const Itinerary &itinerary);
    static void removeItineraryDetail(const std::string &itineraryID, const std::string &activityName);
};

#endif
