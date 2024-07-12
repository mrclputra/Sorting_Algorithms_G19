#include <iostream>

// headers 
#include "headers/property.h"
#include "headers/loader.h"

// function prototypes
void testPropertyLine();

int main() {
    testPropertyLine();
    return 0;
}

void testPropertyLine() {
    std::string csv_line = "100203973,Segar Courts,,RM 2 300 per month,Kuala Lumpur - Cheras,Condominium,3,1.0,2.0,1170 sq.ft.,Partially Furnished,"
                           "\"Playground, Parking, Barbeque area, Security, Jogging Track, Swimming Pool, Gymnasium, Lift, Sauna\","
                           "\"Air-Cond, Cooking Allowed, Near KTM/LRT\",Kuala Lumpur";

    Loader loader;
    Property property = loader.loadLine(csv_line);

    // Print out the property details to verify correctness
    std::cout << "Property ID: " << property.getID() << std::endl;
    std::cout << "Name: " << property.getName() << std::endl;
    std::cout << "Completion Year: " << property.getCompletion() << std::endl;
    std::cout << "Monthly Rent:" << property.getMonthlyRent() << std::endl;
    std::cout << "Location: " << property.getLocation() << std::endl;
    std::cout << "Type: " << property.getType() << std::endl;
    std::cout << "Rooms: " << property.getRooms() << std::endl;
    std::cout << "Parking: " << property.getParking() << std::endl;
    std::cout << "Bathrooms: " << property.getBathrooms() << std::endl;
    std::cout << "Size: " << property.getSize() << std::endl;
    std::cout << "Furnished: " << property.getFurnished() << std::endl;

    // Print facilities
    std::cout << "Facilities: ";
    for (int i = 0; i < property.getNumFacilities(); ++i) {
        std::cout << property.getFacilities()[i];
        if (i < property.getNumFacilities() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    // Print additional facilities
    std::cout << "Additional Facilities: ";
    for (int i = 0; i < property.getNumAddFacilities(); ++i) {
        std::cout << property.getAddFacilities()[i];
        if (i < property.getNumAddFacilities() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Region: " << property.getRegion() << std::endl;
}