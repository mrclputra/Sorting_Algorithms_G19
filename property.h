#pragma once

#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>

class Property {
private:
    // csv headers
    int id;
    std::string name;
    int completion;
    int monthly_rent;
    std::string location;
    std::string type;
    int rooms;
    int parking;
    int bathrooms;
    int size;

    // standard arrays
    std::string* facilities;
    std::string* add_facilities;

    std::string region;

public:
    // constructor to build the objects on the fly
    Property() {

    }

    // deconstructor
    ~Property() {
        delete[] facilities;
        delete[] add_facilities;
    }

    // getters
    int getID() { return id; };
    std::string getName() { return name; };
    int getCompletion() { return completion; };
    int getMonthlyRent() { return monthly_rent; };
    std::string getLocation() { return location; };
    std::string getType() { return type; };
    int getRooms() { return rooms; };
    int getParking() { return parking; };
    int getBathrooms() { return bathrooms; };
    int getSize() { return size; };
    std::string* getFacilities() { return facilities; };
    std::string* getAddFacilities() { return add_facilities; };
    std::string getRegion() { return region; };

    // implement a loader here or as a separate class?

    // print entry information in standard format
    void display() {

    }

};