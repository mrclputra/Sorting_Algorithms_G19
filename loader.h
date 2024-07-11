#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "property.h"


class Loader {
private:
    // split a quoted CSV field into separate values based on commas
    static void splitQuotedCSVField(const std::string& field, std::string*& result, int& count) {
        std::istringstream ss(field);
        std::string token;
        int index = 0;

        while (std::getline(ss, token, ',')) {
            result[index++] = token;
        }
        count = index;
    }

public:
    static Property** loadProperties(const std::string& filename, int& property_count) {
        std::ifstream file(filename);
        if(!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return nullptr;
        }

        std::string line;
        std::getline(file, line); // skip header file

        // count lines to determine array size
        property_count = 0;
        while(std::getline(file, line)) {
            property_count++;
        }

        // allocate memory for property objects
        Property** properties = new Property*[property_count];
        file.clear();

        file.seekg(0, std::ios::beg); // goto beginning
        std::getline(file, line); // skip header 
        
        int index = 0;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string token;

            int id, completion, rooms, parking, bathrooms;
            double monthly_rent;
            std::string name, location, type, furnished, region;
            std::string facilitiesStr, addFacilitiesStr;
            int size;

            // parse each field from the CSV line
            std::getline(ss, token, ','); id = std::stoi(token);
            std::getline(ss, name, ',');
            std::getline(ss, token, ','); completion = std::stoi(token);
            std::getline(ss, token, ','); monthly_rent = std::stod(token.substr(4));  // skip "RM "
            std::getline(ss, location, ',');
            std::getline(ss, type, ',');
            std::getline(ss, token, ','); rooms = std::stoi(token);
            std::getline(ss, token, ','); parking = std::stoi(token.substr(0, 1));  // Take the first digit
            std::getline(ss, token, ','); bathrooms = std::stoi(token.substr(0, 1));  // take the first digit
            std::getline(ss, token, ','); size = std::stoi(token.substr(0, token.find(" ")));  // extract numerics, ignore 'sqft'
            std::getline(ss, furnished, ',');
            std::getline(ss, facilitiesStr, ',');
            std::getline(ss, addFacilitiesStr, ',');
            std::getline(ss, region, ',');

            // split the facilities and additional facilities by comma
            int num_facilities = 0;
            int num_add_facilities = 0;

            std::string* facilities = nullptr;
            if (!facilitiesStr.empty()) {
                facilities = new std::string[10];  // Adjust size as needed
                splitQuotedCSVField(facilitiesStr, facilities, num_facilities);
            }

            std::string* add_facilities = nullptr;
            if (!addFacilitiesStr.empty()) {
                add_facilities = new std::string[10];  // Adjust size as needed
                splitQuotedCSVField(addFacilitiesStr, add_facilities, num_add_facilities);
            }

            // create Property object
            properties[index++] = new Property(id, name, completion, monthly_rent, location, type, rooms, parking, bathrooms, size, furnished, facilities, num_facilities, add_facilities, num_add_facilities, region);
        }

    file.close();
    return properties;

    }
};