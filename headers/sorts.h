#pragma once

#include "property.h"

// convert to template? to allow sorting by other attributes
// also add gui or prints to visualize the sorting process somehow
class Quick {
public:
	// recursive
	static void sort(Property* arr, int low, int high) {
		if (low < high) {
			int pivot_index = partition(arr, low, high);
			sort(arr, low, pivot_index - 1);
			sort(arr, pivot_index + 1, high);
		}
	}

private:
	static int partition(Property* arr, int low, int high) {
		Property pivot = arr[high];		// last element as pivot
		int i = low - 1;				// index of smaller element

		// what the fuck
		for (int j = low; j < high; j++) {
			if (arr[j].getId() < pivot.getId()) {
				i++;
				std::swap(arr[i], arr[j]);
			}
		}
		std::swap(arr[i + 1], arr[high]);
		return i + 1;
	}

};

class Merge {
public:
    static void sort(Property* arr, int size) {
        mergeSort(arr, 0, size - 1);
    }

private:
    // merge 
    static void mergeSort(Property* arr, int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;  // create middle index

            //sort the two halves
            mergeSort(arr, low, mid);
            mergeSort(arr, mid + 1, high);

            // merge the sorted halves
            merge(arr, low, mid, high);
        }
    }

    // merge two halves of array
    static void merge(Property* arr, int low, int mid, int high) {
        int leftSize = mid - low + 1;
        int rightSize = high - mid;

        // Temp arrays
        Property left[leftSize], right[rightSize];
        
        // copy data to temp arrays
        for (int i = 0; i < leftSize; ++i)
            left[i] = arr[low + i];
        for (int j = 0; j < rightSize; ++j)
            right[j] = arr[mid + 1 + j];

        // merge the temporary arrays back into arr[low..high]
        int i = 0;     // initial index of left subarray
        int j = 0;     // initial index of right subarray
        int k = low;   // initial index of merged subarray

        while (i < leftSize && j < rightSize) {
            if (left[i].getId() <= right[j].getId()) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }

        // copy remaining elements of left[] if any
        while (i < leftSize) {
            arr[k++] = left[i++];
        }

        // copy remaining elements of right[] if any
        while (j < rightSize) {
            arr[k++] = right[j++];
        }
    }
};

// replace with merge sort soon
// class Heap {
// public:
// 	static void sort(Property* arr, int size) {
// 		for (int i = size / 2 - 1; i >= 0; i--) {
// 			heapify(arr, size, i);
// 		}

// 		// extract element one by one from heap
// 		for (int i = size - 1; i > 0; i--) {
// 			std::swap(arr[0], arr[i]);
// 			heapify(arr, i, 0);
// 		}
// 	}

// private:
// 	static void heapify(Property* arr, int size, int i) {
// 		int largest = i;
// 		int l = 2 * i + 1;	// left
// 		int r = 2 * i + 2;	// right

// 		if (l < size && arr[l].getId() > arr[largest].getId()) {
// 			largest = l;
// 		}

// 		if (r < size && arr[r].getId() > arr[largest].getId()) {
// 			largest = r;
// 		}

// 		if (largest != i) {
// 			std::swap(arr[i], arr[largest]);
// 			heapify(arr, size, largest);
// 		}
// 	}

// };

// implement a new class sort below