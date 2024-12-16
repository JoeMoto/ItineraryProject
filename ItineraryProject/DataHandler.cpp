#include "DataHandler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
// Default file paths
string DataHandler::TRAVELER_FILE = "travelers.txt";
string DataHandler::ITINERARY_FILE = "itineraries.txt";
string DataHandler::ITINERARY_DETAIL_FILE = "itinerary_details.txt";
const char DataHandler::DELIM = '|';

void DataHandler::saveTraveler(const Traveler &traveler)
{
    ofstream ofs(TRAVELER_FILE, ios::app);
    if (!ofs)
    {
        cerr << "Error opening traveler file.\n";
        return;
    }
    ofs << traveler.getTravelerID() << DELIM
        << traveler.getFirstName() << DELIM
        << traveler.getLastName() << "\n";
}

Traveler *DataHandler::getTraveler(const string &travelerID)
{
    ifstream ifs(TRAVELER_FILE);
    if (!ifs)
    {
        cerr << "Error opening traveler file.\n";
        return nullptr;
    }
    string line;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string tid, fname, lname;
        if (getline(ss, tid, DELIM) && getline(ss, fname, DELIM) && getline(ss, lname, DELIM))
        {
            if (tid == travelerID)
            {
                return new TravelPlanner(tid, fname, lname);
            }
        }
    }
    return nullptr;
}

void DataHandler::updateTraveler(const Traveler &updatedTraveler)
{
    ifstream ifs(TRAVELER_FILE);
    if (!ifs)
    {
        cerr << "Error opening traveler file.\n";
        return;
    }

    vector<string> lines;
    string line;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string tid, fname, lname;
        if (getline(ss, tid, DELIM) && getline(ss, fname, DELIM) && getline(ss, lname, DELIM))
        {
            if (tid == updatedTraveler.getTravelerID())
            {
                line = updatedTraveler.getTravelerID() + string(1, DELIM) +
                       updatedTraveler.getFirstName() + string(1, DELIM) +
                       updatedTraveler.getLastName();
            }
        }
        lines.push_back(line);
    }
    ifs.close();

    ofstream ofs(TRAVELER_FILE, ios::trunc);
    for (auto &l : lines)
    {
        ofs << l << "\n";
    }
}

void DataHandler::saveItinerary(const Itinerary &itinerary)
{
    ofstream ofs(ITINERARY_FILE, ios::app);
    if (!ofs)
    {
        cerr << "Error opening itinerary file.\n";
        return;
    }
    ofs << itinerary.getItineraryID() << DELIM
        << itinerary.getTravelerID() << DELIM
        << itinerary.getStartDate() << DELIM
        << itinerary.getEndDate() << "\n";
}

Itinerary *DataHandler::getItinerary(const string &itineraryID)
{
    ifstream ifs(ITINERARY_FILE);
    if (!ifs)
    {
        cerr << "Error opening itinerary file.\n";
        return nullptr;
    }
    string line;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string iid, tid, sdate, edate;
        if (getline(ss, iid, DELIM) && getline(ss, tid, DELIM) &&
            getline(ss, sdate, DELIM) && getline(ss, edate, DELIM))
        {
            if (iid == itineraryID)
            {
                return new Itinerary(iid, tid, sdate, edate);
            }
        }
    }
    return nullptr;
}

vector<Itinerary> DataHandler::getItinerariesByTravelerID(const string &travelerID)
{
    vector<Itinerary> itineraries;
    ifstream ifs(ITINERARY_FILE);
    if (!ifs)
    {
        cerr << "Error opening itinerary file.\n";
        return itineraries;
    }
    string line;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string iid, tid, sdate, edate;
        if (getline(ss, iid, DELIM) && getline(ss, tid, DELIM) &&
            getline(ss, sdate, DELIM) && getline(ss, edate, DELIM))
        {
            if (tid == travelerID)
            {
                itineraries.emplace_back(iid, tid, sdate, edate);
            }
        }
    }
    return itineraries;
}

void DataHandler::saveItineraryDetail(const ItineraryDetail &detail)
{
    ofstream ofs(ITINERARY_DETAIL_FILE, ios::app);
    if (!ofs)
    {
        cerr << "Error opening itinerary detail file.\n";
        return;
    }
    ofs << detail.getItineraryID() << DELIM
        << detail.getActivityName() << DELIM
        << detail.getStartTime() << DELIM
        << detail.getEndTime() << DELIM
        << detail.getActivityCost() << "\n";
}

vector<ItineraryDetail> DataHandler::getItineraryDetails(const string &itineraryID)
{
    vector<ItineraryDetail> details;
    ifstream ifs(ITINERARY_DETAIL_FILE);
    if (!ifs)
    {
        cerr << "Error opening itinerary detail file.\n";
        return details;
    }
    string line;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string iid, aname, stime, etime, costStr;
        if (getline(ss, iid, DELIM) && getline(ss, aname, DELIM) &&
            getline(ss, stime, DELIM) && getline(ss, etime, DELIM) &&
            getline(ss, costStr, DELIM))
        {
            if (iid == itineraryID)
            {
                double cost = stod(costStr);
                details.emplace_back(iid, aname, stime, etime, cost);
            }
        }
    }
    return details;
}

void DataHandler::updateItinerary(const Itinerary &updatedItinerary)
{
    ifstream ifs(ITINERARY_FILE);
    if (!ifs)
    {
        cerr << "Error opening itinerary file for update.\n";
        return;
    }

    vector<string> lines;
    string line;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string iid, tid, sdate, edate;
        if (getline(ss, iid, DELIM) && getline(ss, tid, DELIM) &&
            getline(ss, sdate, DELIM) && getline(ss, edate, DELIM))
        {
            if (iid == updatedItinerary.getItineraryID())
            {
                line = updatedItinerary.getItineraryID() + string(1, DELIM) +
                       updatedItinerary.getTravelerID() + string(1, DELIM) +
                       updatedItinerary.getStartDate() + string(1, DELIM) +
                       updatedItinerary.getEndDate();
            }
        }
        lines.push_back(line);
    }
    ifs.close();

    ofstream ofs(ITINERARY_FILE, ios::trunc);
    for (auto &l : lines)
    {
        ofs << l << "\n";
    }
}

void DataHandler::removeItineraryDetail(const string &itineraryID, const string &activityName)
{
    ifstream ifs(ITINERARY_DETAIL_FILE);
    if (!ifs)
    {
        cerr << "Error opening itinerary detail file for removal.\n";
        return;
    }

    vector<string> lines;
    string line;
    while (getline(ifs, line))
    {
        stringstream ss(line);
        string iid, aname, stime, etime, costStr;
        if (getline(ss, iid, DELIM) && getline(ss, aname, DELIM) &&
            getline(ss, stime, DELIM) && getline(ss, etime, DELIM) &&
            getline(ss, costStr, DELIM))
        {
            // Keep the line unless it matches both itineraryID and activityName
            if (iid == itineraryID && aname == activityName)
            {
                continue; // skip this line to remove it
            }
        }
        lines.push_back(line);
    }
    ifs.close();

    ofstream ofs(ITINERARY_DETAIL_FILE, ios::trunc);
    for (auto &l : lines)
    {
        ofs << l << "\n";
    }
}
