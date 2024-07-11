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
    // implement utility functions here
    Property loadLine(const std::string& line) {
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