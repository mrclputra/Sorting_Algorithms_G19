#pragma once

/*
csv loader made by Marcelino
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>

#include "property.h"
#include "linkedlist.h"

class Loader {
public:
    // trim whitespace
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // convert from string, extract numeric values only
    int getNumeric(const std::string& str) {
        std::string num_str;
        for(char ch : str) {
            if(std::isdigit(ch)) {
                num_str += ch;
            }
        }
        return std::stoi(num_str);
    }

    // extract quotes strings
    std::string extractQuotedString(std::stringstream& ss) {
        std::string item;
        std::getline(ss, item, '"'); // skip the first quote
        std::getline(ss, item, '"'); // read until the next quote
        return trim(item);
    }

    // parse csv string into array of strings
    std::string* parseArray(const std::string& str) {
        std::stringstream ss(str);
        std::string item;
        int count = 0;

        // first pass, get number of items
        while(std::getline(ss, item, ',')) {
            count++;
        }

        // allocate array with extra slot for null terminator
        std::string* arr = new std::string[count];

        // reset
        ss.clear();
        ss.seekg(0, std::ios::beg);

        // second pass, fill array
        int i = 0;
        while(std::getline(ss, item, ',')) {
            arr[i++] = trim(item);
        }

        return arr;
    }

public:
    Property loadLine(const std::string& line) {
        Property property;
        std::stringstream ss(line);
        std::string item;

        // load id
        std::getline(ss, item, ',');
        std::cout << "ID read: " << item << std::endl; // debug
        property.setId(item.empty() ? 0 : std::stoi(trim(item)));

        // load name
        if (ss.peek() == '"') {
            property.setName(extractQuotedString(ss));
            std::getline(ss, item, ',');
        } else {
            std::getline(ss, item, ',');
            property.setName(trim(item));
        }
        std::cout << "Name read: " << property.getName() << std::endl; // debug

        // load completion, convert into int
        std::getline(ss, item, ',');
        std::cout << "Completion read: " << item << std::endl; // debug
        property.setCompletion(item.empty() ? 0 : getNumeric(trim(item)));

        // load rent, take only numbers, convert into int
        std::getline(ss, item, ',');
        std::cout << "Rent read: " << item << std::endl; // debug
        property.setRentPerMonth(item.empty() ? 0 : getNumeric(trim(item)));

        // load location
        std::getline(ss, item, ',');
        std::cout << "Location read: " << item << std::endl; // debug
        property.setLocation(trim(item));

        // load type
        std::getline(ss, item, ',');
        std::cout << "Type read: " << item << std::endl; // debug
        property.setType(trim(item));

        // load rooms
        std::getline(ss, item, ',');
        std::cout << "Rooms read: " << item << std::endl; // debug
        property.setRooms(item.empty() ? 0 : getNumeric(trim(item)));

        // load parking, convert into int
        std::getline(ss, item, ',');
        std::cout << "Parking read: " << item << std::endl; // debug
        property.setParking(item.empty() ? 0 : getNumeric(trim(item)));

        // load bathrooms, convert into int
        std::getline(ss, item, ',');
        std::cout << "Bathrooms read: " << item << std::endl; // debug
        property.setBathrooms(item.empty() ? 0 : getNumeric(trim(item)));

        // load size, take numeric only, convert into int
        std::getline(ss, item, ',');
        std::cout << "Size read: " << item << std::endl; // debug
        property.setSize(item.empty() ? 0 : getNumeric(trim(item)));

        // load furnished
        std::getline(ss, item, ',');
        std::cout << "Furnished read: " << item << std::endl; // debug
        property.setFurnished(trim(item));

        // load facilities
        std::string facilities_str = extractQuotedString(ss);
        std::cout << "Facilities read: " << facilities_str << std::endl; // debug
        property.setFacilities(parseArray(facilities_str));

        // load additional facilities
        std::string add_facilities_str = extractQuotedString(ss);
        std::cout << "Additional Facilities read: " << add_facilities_str << std::endl; // debug
        property.setAdditionalFacilities(parseArray(add_facilities_str));

        // load region
        std::getline(ss, item, ',');
        std::getline(ss, item);
        std::cout << "Region read: " << item << std::endl; // debug
        property.setRegion(trim(item));
        
        std::cout << std::endl;

        // return property object 
        return property;
    }

    // main loader, saves indirectly to linked list through pointer
    void loadCSV(const std::string& filename, LinkedList<Property>& list) {
        std::ifstream file(filename);
        if(!file.is_open()) {
            std::cerr << "Failed to open " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(file, line); // skip header line

        int count = 0;
        while(std::getline(file, line) && count < 25) {
            Property property = loadLine(line);
            list.append(property);
            count++;
        }

        file.close();
    }
};