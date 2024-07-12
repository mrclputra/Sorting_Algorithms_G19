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
        std::string* arr = new std::string[count + 1];

        // reset
        ss.clear();
        ss.seekg(0, std::ios::beg);

        // second pass, fill array
        int i = 0;
        while(std::getline(ss, item, ',')) {
            arr[i++] = trim(item);
        }

        arr[count] = "";

        return arr;
    }

public:
    Property loadLine(const std::string& line) {
        Property property;
        std::stringstream ss(line);
        std::string item;

        // load id
        std::getline(ss, item, ',');
        std::cout << "ID read: " << item << std::endl;
        property.setId(item.empty() ? 0 : std::stoi(trim(item)));

        // load name
        std::getline(ss, item, ',');
        std::cout << "Name read: " << item << std::endl;
        property.setName(trim(item));

        // load completion, convert into int
        std::getline(ss, item, ',');
        std::cout << "Completion read: " << item << std::endl;
        property.setCompletion(item.empty() ? 0 : std::stoi(trim(item)));

        // load rent, take only numbers, convert into int
        std::getline(ss, item, ',');
        std::cout << "Rent read: " << item << std::endl;
        property.setRentPerMonth(item.empty() ? 0 : getNumeric(trim(item)));

        // load location
        std::getline(ss, item, ',');
        std::cout << "Location read: " << item << std::endl;
        property.setLocation(trim(item));

        // load type
        std::getline(ss, item, ',');
        std::cout << "Type read: " << item << std::endl;
        property.setType(trim(item));

        // load rooms
        std::getline(ss, item, ',');
        std::cout << "Rooms read: " << item << std::endl;
        property.setRooms(item.empty() ? 0 : std::stoi(trim(item)));

        // load parking, convert into int
        std::getline(ss, item, ',');
        std::cout << "Parking read: " << item << std::endl;
        property.setParking(item.empty() ? 0 : std::stoi(trim(item)));

        // load bathrooms, convert into int
        std::getline(ss, item, ',');
        std::cout << "Bathrooms read: " << item << std::endl;
        property.setBathrooms(item.empty() ? 0 : std::stoi(trim(item)));

        // load size, take numeric only, convert into int
        std::getline(ss, item, ',');
        std::cout << "Size read: " << item << std::endl;
        property.setSize(item.empty() ? 0 : getNumeric(trim(item)));

        // load furnished
        std::getline(ss, item, ',');
        std::cout << "Furnished read: " << item << std::endl;
        property.setFurnished(trim(item));

        // load facilities
        std::string facilities_str = extractQuotedString(ss);
        std::cout << "Facilities read: " << facilities_str << std::endl;
        property.setFacilities(parseArray(facilities_str));

        // load additional facilities
        std::string add_facilities_str = extractQuotedString(ss);
        std::cout << "Additional Facilities read: " << add_facilities_str << std::endl;
        property.setAdditionalFacilities(parseArray(add_facilities_str));

        // load region
        std::getline(ss, item, ','); // skip comma
        std::getline(ss, item);
        std::cout << "Region read: " << item << std::endl;
        property.setRegion(trim(item));
        
        std::cout << std::endl;

        // return Property object 
        return property;
    }

    // implement main loader here
    // Property loadCSV(const std::string filename, int &size) {
    //     // get size of dataset first
    //     // update size variable indirectly

    //     // create properties array with size of dataset
    //     // run loadline for each line, add to properties array
    //     // return array
    // }
};