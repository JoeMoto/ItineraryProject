#ifndef ITINERARYDETAIL_HPP
#define ITINERARYDETAIL_HPP

#include <string>

using namespace std;

class ItineraryDetail
{
private:
    string itineraryID;
    string activityName;
    string startTime;
    string endTime;
    double activityCost;

public:
    ItineraryDetail(const string &itineraryID, const string &activityName,
                    const string &startTime, const string &endTime, double activityCost)
        : itineraryID(itineraryID), activityName(activityName), startTime(startTime),
          endTime(endTime), activityCost(activityCost) {}

    string getItineraryID() const { return itineraryID; }
    string getActivityName() const { return activityName; }
    string getStartTime() const { return startTime; }
    string getEndTime() const { return endTime; }
    double getActivityCost() const { return activityCost; }

    void setItineraryID(const string &id) { itineraryID = id; }
    void setActivityName(const string &name) { activityName = name; }
    void setStartTime(const string &st) { startTime = st; }
    void setEndTime(const string &et) { endTime = et; }
    void setActivityCost(double cost) { activityCost = cost; }
};

#endif
