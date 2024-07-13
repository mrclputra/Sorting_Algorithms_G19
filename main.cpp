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
    
    bool continue_sorting = true;
    while(continue_sorting) {
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
                sleepFor(1000);
                clearScreen();
            } else {
                valid_input = true;
            }
        }

        clearScreen();

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

        // create copies of loaded linkedlist
        std::cout << "Copying Lists: number of properties = " << properties.size() << std::endl;
        LinkedList<Property> quicksort_copy(properties);
        LinkedList<Property> mergesort_copy(properties);
        std::cout << "Finished Copying Lists" << std::endl;

        // initialize timers
        Timer quicksort_timer;
        Timer mergesort_timer;

        double quick_elapsed = 0.0;
        double merge_elapsed = 0.0;

        // run quick sort thread
        std::thread quicksort_thread([&]() {
            quicksort_timer.reset();
            Quick::sort(quicksort_copy, getAttribute);
            quick_elapsed = quicksort_timer.elapsed();
            std::cout << "Finished QuickSort in " << quick_elapsed << " seconds.\n" << std::endl;
        });

        // quicksort bathrooms breaks at 19389 properties?

        // run merge sort thread
        // std::thread mergesort_thread([&] () {
        //     mergesort_timer.reset();
        //     Merge::sort(mergesort_copy, getAttribute);
        //     merge_elapsed = mergesort_timer.elapsed();
        //     std::cout << "Finished MergeSort in " << merge_elapsed << " seconds.\n" << std::endl;
        // });
        
        // wait for both to finish
        quicksort_thread.join();
        // mergesort_thread.join();

        choice = 0;
        valid_input = false;

        while(!valid_input) {
            std::cout << "Do you want to sort by another attribute?" << std::endl;
            std::cout << "1. Yes" << std::endl;
            std::cout << "2. No" << std::endl;
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

        continue_sorting = (choice == 1);
    }

    properties.clear();
    return 0;
}

void clearScreen() {
    // ANSI escape sequence, read reference below
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