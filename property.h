#pragma once

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
    std::string furnished;
    std::string* facilities;
    int num_facilities;
    std::string* add_facilities;
    int num_add_facilities;
    std::string region;

public:
    // constructor
    Property(int id, const std::string &name, int completion, int monthly_rent, const std::string &location, const std::string &type,
             int rooms, int parking, int bathrooms, int size, const std::string &furnished,
             const std::string *facilities, int num_facilities,
             const std::string *add_facilities, int num_add_facilities,
             const std::string &region) : id(id), name(name), completion(completion), monthly_rent(monthly_rent), location(location), type(type),
                                          rooms(rooms), parking(parking), bathrooms(bathrooms), size(size), furnished(furnished),
                                          num_facilities(num_facilities), num_add_facilities(num_add_facilities), region(region)
    {
        // allocate and set facilities
        this->facilities = new std::string[num_facilities];
        for (int i = 0; i < num_facilities; i++) {
            this->facilities[i] = facilities[i];
        }

        // allocate and set additional facilities
        this->add_facilities = new std::string[num_add_facilities];
        for (int i = 0; i < num_add_facilities; i++) {
            this->add_facilities[i] = add_facilities[i];
        }
    }

    // deconstructor to free memory
    ~Property() {
        delete[] facilities;
        delete[] add_facilities;
    }

    // getters
    int getID() const { return id; }
    std::string getName() const { return name; }
    int getCompletion() const { return completion; }
    int getMonthlyRent() const { return monthly_rent; }
    std::string getLocation() const { return location; }
    std::string getType() const { return type; }
    int getRooms() const { return rooms; }
    int getParking() const { return parking; }
    int getBathrooms() const { return bathrooms; }
    int getSize() const { return size; }
    std::string getFurnished() const { return furnished; }
    const std::string* getFacilities() const { return facilities; }
    int getNumFacilities() const { return num_facilities; }
    const std::string* getAddFacilities() const { return add_facilities; }
    int getNumAddFacilities() const { return num_add_facilities; }
    std::string getRegion() const { return region; }
};