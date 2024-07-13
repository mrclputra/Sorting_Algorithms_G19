#pragma once

#include <functional>
[[deprecated("This header is deprecated and broken. Use sorts.h instead.")]]

#include "property.h"
#include "linkedlist.h"

// convert to template? to allow sorting by other attributes
// also add gui or prints to visualize the sorting process somehow
template <typename T>
class Quick {
public:
	static void sort(LinkedList<Property>& list, int (Property::*getter)() const) {
        if (list.getSize() <= 1) {
            return; // if list is alread sorted
        }

        list.head = quicksort(list.head, list.tail, getter);
        
        // update tail pointer
        Node<Property>* tail = list.head;
        while (tail->next) {
            tail = tail->next;
        }
        list.tail = tail;
    }

private:
	static Node<Property>* quicksort(Node<Property>* head, Node<Property>* tail, int (Property::*getter)() const) {
        if (!head || head == tail) {
            return head;
        }

        Node<Property>* newHead = nullptr;
        Node<Property>* newTail = nullptr;

        Node<Property>* pivot = partition(head, tail, getter, &newHead, &newTail);

        if (newHead != pivot) {
            Node<Property>* temp = newHead;
            while (temp->next != pivot) {
                temp = temp->next;
            }
            temp->next = nullptr;

            newHead = quicksort(newHead, temp, getter);

            temp = newHead;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = pivot;
        }

        pivot->next = quicksort(pivot->next, newTail, getter);

        return newHead;
    }

	// lmao
	static Node<Property>* partition(Node<Property>* head, Node<Property>* tail, int (Property::*getter)() const,
                                     Node<Property>** newHead, Node<Property>** newTail) {
        Node<Property>* pivot = tail;
        Node<Property>* prev = nullptr;
        Node<Property>* cur = head;
        Node<Property>* end = pivot;

        while (cur != pivot) {
            if ((cur->data.*getter)() < (pivot->data.*getter)()) {
                if (!*newHead) {
                    *newHead = cur;
                }
                prev = cur;
                cur = cur->next;
            } else {
                if (prev) {
                    prev->next = cur->next;
                }
                Node<Property>* temp = cur->next;
                cur->next = nullptr;
                end->next = cur;
                end = cur;
                cur = temp;
            }
        }

        if (!*newHead) {
            *newHead = pivot;
        }

        *newTail = end;

        return pivot;
    }
};

// class Quick {
// public:
// 	// recursive
// 	static void sort(Property* arr, int low, int high) {
// 		if (low < high) {
// 			int pivot_index = partition(arr, low, high);
// 			sort(arr, low, pivot_index - 1);
// 			sort(arr, pivot_index + 1, high);
// 		}
// 	}

// private:
// 	static int partition(Property* arr, int low, int high) {
// 		Property pivot = arr[high];		// last element as pivot
// 		int i = low - 1;				// index of smaller element

// 		// what the fuck
// 		for (int j = low; j < high; j++) {
// 			if (arr[j].getId() < pivot.getId()) {
// 				i++;
// 				std::swap(arr[i], arr[j]);
// 			}
// 		}
// 		std::swap(arr[i + 1], arr[high]);
// 		return i + 1;
// 	}

// };

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