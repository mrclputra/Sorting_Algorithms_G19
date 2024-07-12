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
    std::string* add_facilities;
    std::string region;

public:
    // standard constructor
    Property(int id, const std::string &name, int completion, int monthly_rent, const std::string &location, const std::string &type,
             int rooms, int parking, int bathrooms, int size, const std::string &furnished,
             std::string *facilities, int num_facilities,
             std::string *add_facilities, int num_add_facilities,
             const std::string &region) : id(id), name(name), completion(completion), monthly_rent(monthly_rent), location(location), type(type),
                                          rooms(rooms), parking(parking), bathrooms(bathrooms), size(size), furnished(furnished),
                                          facilities(facilities), add_facilities(add_facilities), region(region) {}

    // empty constructor
    Property() : facilities(nullptr), add_facilities(nullptr) {}

    // deconstructor to free memory
    ~Property() {
        delete[] facilities;
        delete[] add_facilities;
    }

    // display all details
    void display() {
        // modify this to work with empty values as well
        std::cout << "Property ID: " << getID() << std::endl;
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Completion Year: " << getCompletion() << std::endl;
        std::cout << "Monthly Rent: " << getMonthlyRent() << std::endl;
        std::cout << "Location: " << getLocation() << std::endl;
        std::cout << "Type: " << getType() << std::endl;
        std::cout << "Rooms: " << getRooms() << std::endl;
        std::cout << "Parking: " << getParking() << std::endl;
        std::cout << "Bathrooms: " << getBathrooms() << std::endl;
        std::cout << "Size: " << getSize() << std::endl;
        std::cout << "Furnished: " << getFurnished() << std::endl;

        // print facilities
        std::cout << "Facilities: ";
        for (int i = 0; facilities[i] != ""; ++i) {
            std::cout << facilities[i] << (facilities[i + 1] != "" ? ", " : "");
        }
        std::cout << std::endl;

        // print additional facilities
        std::cout << "Additional Facilities: ";
        for (int i = 0; add_facilities[i] != ""; ++i) {
            std::cout << add_facilities[i] << (add_facilities[i + 1] != "" ? ", " : "");
        }
        std::cout << std::endl;

        std::cout << "Region: " << getRegion() << std::endl;
    }

    // setters
    void setId(int id) { this->id = id; }
    void setName(const std::string& name) { this->name = name; }
    void setCompletion(int completion) { this->completion = completion; }
    void setRentPerMonth(int monthly_rent) { this->monthly_rent = monthly_rent; }
    void setLocation(const std::string& location) { this->location = location; }
    void setType(const std::string& type) { this->type = type; }
    void setRooms(int rooms) { this->rooms = rooms; }
    void setParking(int parking) { this->parking = parking; }
    void setBathrooms(int bathrooms) { this->bathrooms = bathrooms; }
    void setSize(int size) { this->size = size; }
    void setFurnished(const std::string& furnished) { this->furnished = furnished; }
    void setFacilities(std::string* facilities) {
        delete[] this->facilities; // clean up previous allocation
        this->facilities = facilities;
    }
    void setAdditionalFacilities(std::string* add_facilities) {
        delete[] this->add_facilities; // clean up previous allocation
        this->add_facilities = add_facilities;
    }
    void setRegion(const std::string& region) { this->region = region; }

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
    const std::string* getAddFacilities() const { return add_facilities; }
    std::string getRegion() const { return region; }
};