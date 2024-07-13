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
// utility functions
private:
    // trim whitespace
    static std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // convert from string, extract numeric values only
    static int getNumeric(const std::string& str) {
        std::string num_str;
        bool has_decimal = false;

        for (char ch : str) {
            if (std::isdigit(ch)) {
                num_str += ch;
            } else if (ch == '.' && !has_decimal) {
                num_str += ch;
                has_decimal = true;
            }
        }

        if (num_str.empty() || num_str == ".") {
            return 0; // handle empty or invalid strings
        }

        double num_double = std::stod(num_str);
        return static_cast<int>(num_double);
    }

    // extract quotes strings
    static std::string extractQuotedString(std::stringstream& ss) {
        std::string item;
        std::getline(ss, item, '"'); // skip the first quote
        std::getline(ss, item, '"'); // read until the next quote
        return trim(item);
    }

    // parse csv string into array of strings
    static LinkedList<std::string> parseArray(const std::string& str) {
        LinkedList<std::string> list;
        std::stringstream ss(str);
        std::string item;

        while (std::getline(ss, item, ',')) {
            list.append(trim(item));
        }

        // copy assignment operator is in use here
        return list;
    }

    static Property loadLine(const std::string& line) {
        Property property;
        std::stringstream ss(line);
        std::string item;

        // load id
        std::getline(ss, item, ',');
        property.setId(item.empty() ? 0 : std::stoi(trim(item)));

        // load name, some names have quotes
        if (ss.peek() == '"') {
            property.setName(extractQuotedString(ss));
            std::getline(ss, item, ',');
        } else {
            std::getline(ss, item, ',');
            property.setName(trim(item));
        }

        // load completion, convert into int
        std::getline(ss, item, ',');
        property.setCompletion(item.empty() ? 0 : getNumeric(trim(item)));

        // load rent, take only numbers, convert into int
        std::getline(ss, item, ',');
        property.setRentPerMonth(item.empty() ? 0 : getNumeric(trim(item)));

        // load location
        std::getline(ss, item, ',');
        property.setLocation(trim(item));

        // load type
        std::getline(ss, item, ',');
        property.setType(trim(item));

        // load rooms
        std::getline(ss, item, ',');
        property.setRooms(item.empty() ? 0 : getNumeric(trim(item)));

        // load parking, convert into int
        std::getline(ss, item, ',');
        property.setParking(item.empty() ? 0 : getNumeric(trim(item)));

        // load bathrooms, convert into int
        std::getline(ss, item, ',');
        property.setBathrooms(item.empty() ? 0 : getNumeric(trim(item)));

        // load size, take numeric only, convert into int
        std::getline(ss, item, ',');
        property.setSize(item.empty() ? 0 : getNumeric(trim(item)));

        // load furnished
        std::getline(ss, item, ',');
        property.setFurnished(trim(item));

        // load facilities
        std::string facilities_str = extractQuotedString(ss);
        property.setFacilities(parseArray(facilities_str));

        // load additional facilities
        std::string add_facilities_str = extractQuotedString(ss);
        property.setAdditionalFacilities(parseArray(add_facilities_str));

        // load region
        std::getline(ss, item, ',');
        std::getline(ss, item);
        property.setRegion(trim(item));

        // return property object 
        return property;
    }


public:
    // main loader, saves indirectly to linked list through pointer
    // element determine number of lines to parse, -1 for all
    static void loadCSV(const std::string& filename, LinkedList<Property>& list, int elements) {
        std::ifstream file(filename);
        if(!file.is_open()) {
            std::cerr << "Failed to open " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(file, line); // skip header line

        int count = 0;
        while (std::getline(file, line)) {
            Property property = loadLine(line);
            list.append(property);
            count++;
            if (elements != -1 && count >= elements) {
                break;
            }
        }

        file.close();
    }
};