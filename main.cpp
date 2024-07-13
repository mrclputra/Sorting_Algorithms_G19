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
    Loader loader;
    LinkedList<Property> properties;

    double time_quickSort, time_mergeSort;

    loader.loadCSV("dataset.csv", properties, 25); // 3rd int defines number of lines, set to -1 to load all
    std::cout << "Finished loading all properties\n" << std::endl;

    // properties.head->data.printBathrooms(); // this is how you call individual prints

    std::cout << "Before Sort :" << std::endl;
    properties.print(&Property::printMonthlyRent); // this is how you call a print all

    Quick::sort(properties, &Property::getMonthlyRent);

    std::cout << std::endl << "After Sort :" << std::endl;
    properties.print(&Property::printMonthlyRent);

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