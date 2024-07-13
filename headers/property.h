#pragma once

#include <string>
#include "linkedlist.h"

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
    // std::string* facilities;
    // std::string* add_facilities;
    LinkedList<std::string> facilities;
    LinkedList<std::string> add_facilities;
    std::string region;

public:
    // standard constructor, unused
    Property(int id, const std::string &name, int completion, int monthly_rent, const std::string &location, const std::string &type,
             int rooms, int parking, int bathrooms, int size, const std::string &furnished,
             const LinkedList<std::string> &facilities, const LinkedList<std::string> &add_facilities,
             const std::string &region) : id(id), name(name), completion(completion), monthly_rent(monthly_rent), location(location), type(type),
                                          rooms(rooms), parking(parking), bathrooms(bathrooms), size(size), furnished(furnished),
                                          facilities(facilities), add_facilities(add_facilities), region(region) {}

    // default constructor
    Property() {}

    // display all details
    void display() {
        std::cout << "Property ID: " << getId() << std::endl;
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
        std::cout << "Facilities: ";
        facilities.print();
        std::cout << "Additional Facilities: ";
        add_facilities.print();
        std::cout << "Region: " << getRegion() << std::endl;
    }

    void printPropertyId() const {
        std::cout << id << std::endl;
    }
    void printName() const {
        std::cout << name << std::endl;
    }
    void printCompletion() const {
        std::cout << completion << std::endl;
    }
    void printMonthlyRent() const {
        std::cout << monthly_rent << std::endl;
    }       
    void printLocation() const {
        std::cout << location << std::endl;
    }
    void printType() const {
        std::cout << type << std::endl;
    }
    void printRooms() const {
        std::cout << rooms << std::endl;
    }
    void printParking() const {
        std::cout << parking << std::endl;
    }
    void printBathrooms() const {
        std::cout << bathrooms << std::endl;
    }
    void printSize() const {
        std::cout << size << std::endl;
    }
    void printFurnished() const {
        std::cout << furnished << std::endl;
    }
    void printFacilities() const {
        facilities.print();
    }
    void printAdditionalFacilities() const {
        add_facilities.print();
    }
    void printRegion() const {
        std::cout << region << std::endl;
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
    void setFacilities(const LinkedList<std::string>& facilities) { this->facilities = facilities; }
    void setAdditionalFacilities(const LinkedList<std::string>& add_facilities) { this->add_facilities = add_facilities; }
    void setRegion(const std::string& region) { this->region = region; }

    // getters
    int getId() const { return id; }
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
    const LinkedList<std::string>& getFacilities() const { return facilities; }
    const LinkedList<std::string>& getAddFacilities() const { return add_facilities; }
    std::string getRegion() const { return region; }
};