#pragma once

/*
csv loader made by Marcelino
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "property.h"

class Loader {
private:
    // trim whitespace
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // convert rent string to int, numeric only
    int rentToInt(const std::string& str) {
        std::string num_str;
        for(char ch : str) {
            if(std::isdigit(ch)) {
                num_str += ch;
            }
        }
        return std::stoi(num_str);
    }

    // parse csv string into array of strings
    std::string* parseArray(const std::string& str, int& count) {
        std::stringstream ss(str);
        std::string item;
        count = 0;

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

    Property loadLine(const std::string& line) {
        std::stringstream ss(line);
        std::string item;

        // load id
        // load name
        // load completion, convert into int
        // load rent, take only numbers, convert into int
        // load location
        // load type
        // load rooms
        // load parking, convert into int
        // load bathrooms, convert into int
        // load size, take numeric only, convert into int
        // load furnished
        // load facilities, load as a string array
        // load additional facilities, load as a string array
        // load region
        
        // return Property object 
    }

public: 
    // implement main loader here
    Property loadCSV(const std::string filename, int &size) {
        // get size of dataset first
        // update size variable indirectly

        // create properties array with size of dataset
        // run loadline for each line, add to properties array
        // return array
    }
};