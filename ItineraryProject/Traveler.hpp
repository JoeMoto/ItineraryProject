#ifndef TRAVELER_HPP
#define TRAVELER_HPP

#include <string>

using namespace std;

class Traveler
{
protected:
    string travelerID;
    string firstName;
    string lastName;

public:
    Traveler(const string &travelerID, const string &firstName, const string &lastName)
        : travelerID(travelerID), firstName(firstName), lastName(lastName) {}

    virtual ~Traveler() = default;

    virtual string getTravelerID() const { return travelerID; }
    virtual string getFirstName() const { return firstName; }
    virtual string getLastName() const { return lastName; }

    virtual void setTravelerID(const string &tid) { travelerID = tid; }
    virtual void setFirstName(const string &fname) { firstName = fname; }
    virtual void setLastName(const string &lname) { lastName = lname; }

    // Abstract class may have pure virtual methods if needed,
    // but here it's just serving as a base class.
};

#endif
