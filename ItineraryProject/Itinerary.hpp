#ifndef ITINERARY_HPP
#define ITINERARY_HPP

#include <string>

using namespace std;

class Itinerary
{
private:
    string itineraryID;
    string travelerID;
    string startDate;
    string endDate;

public:
    Itinerary(const string &itineraryID, const string &travelerID,
              const string &startDate, const string &endDate)
        : itineraryID(itineraryID), travelerID(travelerID), startDate(startDate), endDate(endDate) {}

    string getItineraryID() const { return itineraryID; }
    string getTravelerID() const { return travelerID; }
    string getStartDate() const { return startDate; }
    string getEndDate() const { return endDate; }

    void setItineraryID(const string &id) { itineraryID = id; }
    void setTravelerID(const string &tid) { travelerID = tid; }
    void setStartDate(const string &sdate) { startDate = sdate; }
    void setEndDate(const string &edate) { endDate = edate; }
};

#endif
