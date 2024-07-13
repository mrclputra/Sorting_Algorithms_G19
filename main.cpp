#include <iostream>
#include <chrono> // std::chrono
#include <thread> // thread control
#include <limits>

// headers 
#include "headers/property.h"
#include "headers/loader.h"
#include "headers/linkedlist.h"
#include "headers/sorts.h"
#include "headers/timer.h"

// function prototypes
void clearInputBuffer();
void clearScreen();
void sleepFor(int ms);

int main() {
    LinkedList<Property> properties;
    const std::string filename = "dataset.csv";
    double time_quickSort, time_mergeSort;

    // program execution here
    clearScreen();

    int choice = 0;
    bool valid_input = false;

    while (!valid_input) {
        std::cout << "Program Initialized" << std::endl;
        std::cout << "File to load : " << filename << std::endl;
        std::cout << "\nOptions: " << std::endl;
        std::cout << "1. Load All Entries from CSV" << std::endl;
        std::cout << "2. Load a Specific Number of Lines from CSV" << std::endl;
        std::cout << "Entry: ";

        std::cin >> choice;

        if (std::cin.fail() || (choice != 1 && choice != 2)) {
            clearInputBuffer();
            std::cout << "Invalid Input" << std::endl;
            sleepFor(1000);
            clearScreen();
        } else {
            valid_input = true;
        }
    }

    clearScreen();

    // proceed on valid input
    if (choice == 1) {
        std::cout << "Loading all entries from " << filename << std::endl;
        sleepFor(1000);
        Loader::loadCSV(filename, properties, -1);

    } else if (choice == 2) {
        int num_lines;
        while(true) {
            std::cout << "Enter number of lines to load : ";
            std::cin >> num_lines;

            if(std::cin.fail() || num_lines < 1) {
                clearInputBuffer();
                std::cout << "Invalid Input, enter a positive Integer" << std::endl;
                sleepFor(1000);
                clearScreen();
            } else {
                std::cout << "Loading " << num_lines << " entries from " << filename << std::endl;
                sleepFor(1000);
                Loader::loadCSV(filename, properties, num_lines);
                break;
            }
        }
    }

    std::cout << "Finished loading all properties\n" << std::endl;
    sleepFor(1000);
    clearScreen();

    // sorting options
    choice = 0;
    valid_input = false;

    // sort and print function pointers
    int (Property::*getAttribute)() const = nullptr;
    void (Property::*printAttribute)() const = nullptr;

    while (!valid_input) {
        std::cout << "Choose sorting criteria:" << std::endl;
        std::cout << "1. Sort by ID" << std::endl;
        std::cout << "2. Sort by Completion Year" << std::endl;
        std::cout << "3. Sort by Monthly Rent" << std::endl;
        std::cout << "4. Sort by Number of Rooms" << std::endl;
        std::cout << "5. Sort by Parking" << std::endl;
        std::cout << "6. Sort by Number of Bathrooms" << std::endl;
        std::cout << "7. Sort by Size" << std::endl;
        std::cout << "Entry: ";

        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 7) {
            clearInputBuffer();
            std::cout << "Invalid Input" << std::endl;
            sleepFor(2000);
            clearScreen();
        } else {
            valid_input = true;
        }
    }

    clearScreen();
    std::cout << "Starting Sorting" << std::endl;

    switch (choice) {
        case 1:
            getAttribute = &Property::getId;
            printAttribute = &Property::printId;
            break;
        case 2:
            getAttribute = &Property::getCompletion;
            printAttribute = &Property::printCompletion;
            break;
        case 3:
            getAttribute = &Property::getMonthlyRent;
            printAttribute = &Property::printMonthlyRent;
            break;
        case 4:
            getAttribute = &Property::getRooms;
            printAttribute = &Property::printRooms;
            break;
        case 5:
            getAttribute = &Property::getParking;
            printAttribute = &Property::printParking;
            break;
        case 6:
            getAttribute = &Property::getBathrooms;
            printAttribute = &Property::printBathrooms;
            break;
        case 7:
            getAttribute = &Property::getSize;
            printAttribute = &Property::printSize;
            break;
        default:
            std::cout << "error unknown sort criteria" << std::endl;
            break;
    }

    // create copy of linkedlist for merge sort
    LinkedList<Property> properties_copy(properties);

    // run quick sort
    Quick::sort(properties, getAttribute);
    std::cout << "Finished QuickSort.\n" << std::endl;

    // run merge sort
    Merge::sort(properties_copy, getAttribute);
    std::cout << "Finished MergeSort.\n" << std::endl;

    sleepFor(1000);

    // // measure time for quick sort
    // {
    //     timer timer_quickSort;
    //     Property* arr_quick = new Property[properties.getSize()];
    //     properties.toArray(arr_quick);
    //     Quick::sort(arr_quick, 0, properties.getSize() - 1);
    //     time_quickSort = timer_quickSort.elapsed();
    //     delete[] arr_quick;
    // }

    // // measure time for merge sort
    // {
    //     timer timer_mergeSort;
    //     Property* arr_merge = new Property[properties.getSize()];
    //     properties.toArray(arr_merge);
    //     Merge::sort(arr_merge, properties.getSize());
    //     time_mergeSort = timer_mergeSort.elapsed();
    //     delete[] arr_merge;
    // }

    // //time taken by each sort
    // std::cout << "Time taken for Quick Sort: " << time_quickSort << " seconds" << std::endl;
    // std::cout << "Time taken for Merge Sort: " << time_mergeSort << " seconds" << std::endl;

    return 0;
}

void clearScreen() {
    // ANSI escape sequence, from reference below
    // https://en.wikipedia.org/wiki/ANSI_escape_code
    std::cout << "\x1b[2J\x1b[1;1H";
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void sleepFor(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}