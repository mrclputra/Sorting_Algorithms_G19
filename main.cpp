#include <iostream>

// headers 
#include "headers/property.h"
#include "headers/loader.h"
#include "headers/linkedlist.h"
#include "headers/sorts.h"
#include "headers/timer.h"

// function prototypes
void testLoadLine();
void testQuotedStringExtract();

int main() {
    double time_quickSort, time_mergeSort;
    Loader loader;
    LinkedList<Property> properties;


    loader.loadCSV("dataset.csv", properties, -1);
    // properties.print(&Property::printName); // this is how you call a print


    // Measure time for Quick Sort
    {
        timer timer_quickSort;
        Property* arr_quick = new Property[properties.getSize()];
        properties.toArray(arr_quick);
        Quick::sort(arr_quick, 0, properties.getSize() - 1);
        time_quickSort = timer_quickSort.elapsed();
        delete[] arr_quick;
    }

    // Measure time for Merge Sort
    {
        timer timer_mergeSort;
        Property* arr_merge = new Property[properties.getSize()];
        properties.toArray(arr_merge);
        Merge::sort(arr_merge, properties.getSize());
        time_mergeSort = timer_mergeSort.elapsed();
        delete[] arr_merge;
    }

    //time taken by each sort
    std::cout << "Time taken for Quick Sort: " << time_quickSort << " seconds" << std::endl;
    std::cout << "Time taken for Merge Sort: " << time_mergeSort << " seconds" << std::endl;

    return 0;
}

// void testQuotedStringExtract() {
//     Loader loader;
//     // std::string line = "100203973,Segar Courts,,RM 2 300 per month,Kuala Lumpur - Cheras,Condominium,3,1.0,2.0,1170 sq.ft.,Partially Furnished,"
//     //                        "\"Playground, Parking, Barbeque area, Security, Jogging Track, Swimming Pool, Gymnasium, Lift, Sauna\","
//     //                        "\"Air-Cond, Cooking Allowed, Near KTM/LRT\",Kuala Lumpur";

//     std::string line = "87950203,Maxim Citilights,2017.0,RM 1 300 per month,Kuala Lumpur - Sentul,Service Residence,3,1.0,2.0,1009 sq.ft.,Fully Furnished,"
//                        "\"Minimart, Jogging Track, Playground, Swimming Pool, Multipurpose hall, Security, Lift, Parking, Gymnasium, Sauna, Barbeque area\","
//                        "\"Air-Cond, Cooking Allowed, Washing Machine\",Kuala Lumpur";

//     std::stringstream ss(line);
//     std::string facilitiesStr = loader.extractQuotedString(ss);
//     std::string additionalFacilitiesStr = loader.extractQuotedString(ss);

//     std::string* facilities = loader.parseArray(facilitiesStr);
//     std::string* additionalFacilities = loader.parseArray(additionalFacilitiesStr);

//     // print facilities
//     std::cout << "Facilities: " << std::endl;
//     for (int i = 0; !facilities[i].empty(); ++i) {
//         std::cout << facilities[i] << std::endl;
//     }
//     std::cout << std::endl;

//     // print additional facilities
//     std::cout << "Additional Facilities: " << std::endl;
//     for (int i = 0; !additionalFacilities[i].empty(); ++i) {
//         std::cout << additionalFacilities[i] << std::endl;
//     }
//     std::cout << std::endl;

//     // Clean up allocated memory
//     delete[] facilities;
//     delete[] additionalFacilities;

// }
// void testLoadLine() {
//     // std::string csv_line = "100203973,Segar Courts,,RM 2 300 per month,Kuala Lumpur - Cheras,Condominium,3,1.0,2.0,1170 sq.ft.,Partially Furnished,"
//     //                        "\"Playground, Parking, Barbeque area, Security, Jogging Track, Swimming Pool, Gymnasium, Lift, Sauna\","
//     //                        "\"Air-Cond, Cooking Allowed, Near KTM/LRT\",Kuala Lumpur";

//     std::string line = "87950203,Maxim Citilights,2017.0,RM 1 300 per month,Kuala Lumpur - Sentul,Service Residence,3,1.0,2.0,1009 sq.ft.,Fully Furnished,"
//                        "\"Minimart, Jogging Track, Playground, Swimming Pool, Multipurpose hall, Security, Lift, Parking, Gymnasium, Sauna, Barbeque area\","
//                        "\"Air-Cond, Cooking Allowed, Washing Machine\",Kuala Lumpur";


//     Loader loader;
//     Property property = loader.loadLine(line);

//     // Print out the property details to verify correctness
//     std::cout << "Property ID: " << property.getId() << std::endl;
//     std::cout << "Name: " << property.getName() << std::endl;
//     std::cout << "Completion Year: " << property.getCompletion() << std::endl;
//     std::cout << "Monthly Rent: " << property.getMonthlyRent() << std::endl;
//     std::cout << "Location: " << property.getLocation() << std::endl;
//     std::cout << "Type: " << property.getType() << std::endl;
//     std::cout << "Rooms: " << property.getRooms() << std::endl;
//     std::cout << "Parking: " << property.getParking() << std::endl;
//     std::cout << "Bathrooms: " << property.getBathrooms() << std::endl;
//     std::cout << "Size: " << property.getSize() << std::endl;
//     std::cout << "Furnished: " << property.getFurnished() << std::endl;

//     // Print facilities
//     std::cout << "Facilities: ";
//     const std::string* facilities = property.getFacilities();
//     for (int i = 0; !facilities[i].empty(); ++i) {
//         std::cout << facilities[i];
//         if (!facilities[i + 1].empty()) std::cout << ", ";
//     }
//     std::cout << std::endl;

//     // Print additional facilities
//     std::cout << "Additional Facilities: ";
//     const std::string* additionalFacilities = property.getAddFacilities();
//     for (int i = 0; !additionalFacilities[i].empty(); ++i) {
//         std::cout << additionalFacilities[i];
//         if (!additionalFacilities[i + 1].empty()) std::cout << ", ";
//     }
//     std::cout << std::endl;

//     std::cout << "Region: " << property.getRegion() << std::endl;
// }