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
private:
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
        std::getline(ss, item, '"'); // Skip the first quote
        std::getline(ss, item, '"'); // Read until the next quote
        return trim(item);
    }

    // parse csv string into array of strings
    std::string* parseArray(const std::string& str) {
        std::stringstream ss(str);
        std::string item;
        int count = 0;

        // get number of items
        while (std::getline(ss, item, ',')) {
            count++;
        }

        // allocate array and reset
        std::string* arr = new std::string[count];
        ss.clear();
        ss.seekg(0, std::ios::beg);

        // fill the array
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
        property.setId(item.empty() ? 0 : std::stoi(trim(item)));

        // load name
        std::getline(ss, item, ',');
        property.setName(trim(item));

        // load completion, convert into int
        std::getline(ss, item, ',');
        property.setCompletion(item.empty() ? 0 : std::stoi(trim(item)));

        // load rent, take only numbers, convert into int
        std::getline(ss, item, ',');
        property.setRentPerMonth(item.empty() ? 0 : getNumeric(trim(item)));
        std::cout << getNumeric(trim(item)) << std::endl;

        // load location
        std::getline(ss, item, ',');
        property.setLocation(trim(item));

        // load type
        std::getline(ss, item, ',');
        property.setType(trim(item));

        // load rooms
        std::getline(ss, item, ',');
        property.setRooms(item.empty() ? 0 : std::stoi(trim(item)));

        // load parking, convert into int
        std::getline(ss, item, ',');
        property.setParking(item.empty() ? 0 : std::stoi(trim(item)));

        // load bathrooms, convert into int
        std::getline(ss, item, ',');
        property.setBathrooms(item.empty() ? 0 : std::stoi(trim(item)));

        // load size, take numeric only, convert into int
        std::getline(ss, item, ',');
        property.setSize(item.empty() ? 0 : getNumeric(trim(item)));

        // load furnished
        std::getline(ss, item, ',');
        property.setFurnished(trim(item));

        // load facilities, load as a string array
        property.setFacilities(parseArray(extractQuotedString(ss)));

        // load additional facilities, load as a string array
        property.setFacilities(parseArray(extractQuotedString(ss)));

        // load region
        std::getline(ss, item, ',');
        property.setRegion(trim(item));
        
        // return Property object 
        return property;
    }

public: 
    // implement main loader here
    // Property loadCSV(const std::string filename, int &size) {
    //     // get size of dataset first
    //     // update size variable indirectly

    //     // create properties array with size of dataset
    //     // run loadline for each line, add to properties array
    //     // return array
    // }
};