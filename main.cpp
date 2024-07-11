#include <iostream>

// headers 
#include "property.h"
#include "loader.h"
#include "sorts.h"

int main() {
    int dataset_size = 0;
    Property** properties = Loader::loadProperties("properties.csv", dataset_size);

    if (properties == nullptr) {
        std::cerr << "Failed to load properties." << std::endl;
        return 1;
    }

    // Use the properties array
    for (int i = 0; i < dataset_size; i++) {
        std::cout << "Property ID: " << properties[i]->getID() << ", Name: " << properties[i]->getName() << std::endl;
        delete properties[i];  // Don't forget to delete each property object
    }

    delete[] properties;  // Finally, delete the array of pointers

    return 0;
} 