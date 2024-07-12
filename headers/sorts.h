#pragma once

#include "headers/property.h"

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

		for (int j = low; j < high; j++) {			// help
			if (arr[j].getID() < pivot.getID()) {
				i++;
				std::swap(arr[i], arr[j]);
			}
		}
		std::swap(arr[i + 1], arr[high]);
		return i + 1;
	}

};

// replace with merge sort soon
class Heap {
public:
	static void sort(Property* arr, int size) {
		for (int i = size / 2 - 1; i >= 0; i--) {
			heapify(arr, size, i);
		}

		// extract element one by one from heap
		for (int i = size - 1; i > 0; i--) {
			std::swap(arr[0], arr[i]);
			heapify(arr, i, 0);
		}
	}

private:
	static void heapify(Property* arr, int size, int i) {
		int largest = i;
		int l = 2 * i + 1;	// left
		int r = 2 * i + 2;	// right

		if (l < size && arr[l].getID() > arr[largest].getID()) {
			largest = l;
		}

		if (r < size && arr[r].getID() > arr[largest].getID()) {
			largest = r;
		}

		if (largest != i) {
			std::swap(arr[i], arr[largest]);
			heapify(arr, size, largest);
		}
	}

};

// implement a new class sort below