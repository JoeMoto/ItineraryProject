/*
Final Project Name: Itinerary Planner
Author: Joseph Moto
Date: last modified: 12/13/2024
Description: This program simulates a travel planner application that allows users to create travelers, add activities to their itineraries, and update their information. The application uses a text-based interface and data is stored in separate files.
*/

#include <iostream>
#include <limits>
#include <string>
#include "TravelPlanner.hpp"
#include "DataHandler.hpp"
#include "ItineraryDetail.hpp"
#include "Itinerary.hpp"

using namespace std;

static void createTravelerAndItinerary();
static void retrieveAndUpdate();
static void addActivitiesToItinerary(const string &itineraryID);
static void updateItineraryInfo(const string &itineraryID);
static void removeActivityFromItinerary(const string &itineraryID);

int main()
{
    while (true)
    {
        cout << "\n=== Travel Planner Menu ===\n";
        cout << "1. Create Traveler and Itinerary\n";
        cout << "2. Retrieve Traveler/Itinerary and Update\n";
        cout << "3. Exit\n";
        cout << "Choice: ";

        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            createTravelerAndItinerary();
            break;
        case 2:
            retrieveAndUpdate();
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    }

    return 0;
}

void createTravelerAndItinerary()
{
    string firstName, lastName;
    cout << "Enter Traveler First Name: ";
    getline(cin, firstName);
    cout << "Enter Traveler Last Name: ";
    getline(cin, lastName);

    string travelerID = "TRV-" + to_string(chrono::system_clock::now().time_since_epoch().count());
    TravelPlanner traveler(travelerID, firstName, lastName);
    DataHandler::saveTraveler(traveler);
    cout << "Traveler created with ID: " << travelerID << "\n";

    string startDate, endDate;
    cout << "Enter Itinerary Start Date (MM/DD/YYYY): ";
    getline(cin, startDate);
    cout << "Enter Itinerary End Date (MM/DD/YYYY): ";
    getline(cin, endDate);

    Itinerary itinerary = traveler.createItinerary(startDate, endDate);
    DataHandler::saveItinerary(itinerary);

    cout << "Itinerary created with ID: " << itinerary.getItineraryID() << "\n";
    cout << "Add activities now.\n";
    addActivitiesToItinerary(itinerary.getItineraryID());
}

void retrieveAndUpdate()
{
    cout << "Enter Traveler ID to retrieve: ";
    string travelerID;
    getline(cin, travelerID);

    Traveler *t = DataHandler::getTraveler(travelerID);
    if (!t)
    {
        cout << "Traveler not found.\n";
        return;
    }
    cout << "\nTraveler: " << t->getFirstName() << " " << t->getLastName() << " (ID: " << t->getTravelerID() << ")\n";
    delete t;

    auto itineraries = DataHandler::getItinerariesByTravelerID(travelerID);
    if (itineraries.empty())
    {
        cout << "No itineraries found for this traveler.\n";
        return;
    }

    cout << "Itineraries:\n";
    for (size_t i = 0; i < itineraries.size(); i++)
    {
        cout << i + 1 << ". " << itineraries[i].getItineraryID() << " (" << itineraries[i].getStartDate() << " to " << itineraries[i].getEndDate() << ")\n";
    }

    cout << "Select an itinerary number to view/update: ";
    int index;
    if (!(cin >> index) || index < 1 || (size_t)index > itineraries.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid selection.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Itinerary chosen = itineraries[index - 1];
    cout << "\nSelected Itinerary: " << chosen.getItineraryID() << " (" << chosen.getStartDate() << " to " << chosen.getEndDate() << ")\n";
    auto details = DataHandler::getItineraryDetails(chosen.getItineraryID());
    if (!details.empty())
    {
        double totalCost = 0;
        cout << "Activities:\n";
        for (auto &d : details)
        {
            cout << "- " << d.getActivityName() << ": " << d.getStartTime() << " - " << d.getEndTime() << ", Cost: $" << d.getActivityCost() << "\n";
            totalCost += d.getActivityCost();
        }
        cout << "Total Estimated Cost: $" << totalCost << "\n";
    }
    else
    {
        cout << "No activities for this itinerary.\n";
    }

    cout << "\nWhat would you like to do?\n";
    cout << "1. Update Itinerary Dates\n";
    cout << "2. Add Activities\n";
    cout << "3. Remove an Activity\n";
    cout << "4. Return to Main Menu\n";
    cout << "Choice: ";
    int choice;
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice)
    {
    case 1:
        updateItineraryInfo(chosen.getItineraryID());
        break;
    case 2:
        addActivitiesToItinerary(chosen.getItineraryID());
        break;
    case 3:
        removeActivityFromItinerary(chosen.getItineraryID());
        break;
    default:
        break;
    }
}

void addActivitiesToItinerary(const string &itineraryID)
{
    while (true)
    {
        string activityName;
        cout << "Enter Activity Name (or 'done' to finish): ";
        getline(cin, activityName);
        if (activityName == "done" || activityName == "DONE" || activityName == "Done")
        {
            break;
        }

        string startTime, endTime;
        double activityCost = 0.0;

        cout << "Enter Activity Start Time (HH:MM AM/PM): ";
        getline(cin, startTime);

        cout << "Enter Activity End Time (HH:MM AM/PM): ";
        getline(cin, endTime);

        cout << "Enter Activity Cost: ";
        while (!(cin >> activityCost))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter numeric value: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ItineraryDetail detail(itineraryID, activityName, startTime, endTime, activityCost);
        DataHandler::saveItineraryDetail(detail);
        cout << "Activity added.\n";
    }
}

void updateItineraryInfo(const string &itineraryID)
{
    Itinerary *it = DataHandler::getItinerary(itineraryID);
    if (!it)
    {
        cout << "Itinerary not found.\n";
        return;
    }
    string newStartDate, newEndDate;
    cout << "Enter new Start Date (MM/DD/YYYY): ";
    getline(cin, newStartDate);
    cout << "Enter new End Date (MM/DD/YYYY): ";
    getline(cin, newEndDate);

    it->setStartDate(newStartDate);
    it->setEndDate(newEndDate);
    DataHandler::updateItinerary(*it);
    cout << "Itinerary updated.\n";
    delete it;
}

void removeActivityFromItinerary(const string &itineraryID)
{
    cout << "Enter Activity Name to remove: ";
    string activityName;
    getline(cin, activityName);

    DataHandler::removeItineraryDetail(itineraryID, activityName);
    cout << "Activity removed (if it existed).\n";
}
