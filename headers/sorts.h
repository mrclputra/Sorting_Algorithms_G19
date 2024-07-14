#pragma once
#include <stack>

#include "linkedlist.h"
#include "property.h"

// my modified linked list quicksort intrepretation, adapted from
// https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
class Quick {
public:
    // start the quicksort on the given linkedlist
    static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
        recursion_depth = 0;
        max_recursion_depth = 0;
        list.head = recursive(list.head, getTail(list.head), getAttribute);
        std::cout << "Maximum Quicksort Recursion Depth: " << max_recursion_depth << std::endl;
    }

private:
    // track space complexity
    static inline int recursion_depth = 0;
    static inline int max_recursion_depth = 0;

    // get last node
    static Node<Property>* getTail(Node<Property>* curr) {
        while (curr != nullptr && curr->next != nullptr)
            curr = curr->next;
        return curr;
    }

    // partition linked list
    static Node<Property>* partition(Node<Property>* head, Node<Property>* end, Node<Property>** new_head, Node<Property>** new_end, int (Property::*getAttribute)() const) {
        // check if any of the pointers are null, return empty pointer if so
        if (!head || !end || !new_head || !new_end) return nullptr;

        // select the last element as a pivot, basic
        Node<Property>* pivot = end;            // set pivot to last element in list
        Node<Property>* prev = nullptr;         // previous node, initially null
        Node<Property>* curr = head;            // current node, start at head of list
        Node<Property>* tail = pivot;           // tail node, start at pivot

        // partition the list
        while (curr != pivot) {
            // check if current node is less than pivot node attribute
            if ((curr->data.*getAttribute)() < (pivot->data.*getAttribute)()) {
                // defins start of partition
                // is new head is null, set to current
                if ((*new_head) == nullptr)
                    (*new_head) = curr;

                // move previous and current pointers forward
                prev = curr;
                curr = curr->next;

            } else {
                // if previous node exists, link it to the next node, skip current node
                if (prev)
                    prev->next = curr->next;

                Node<Property>* temp = curr->next;  // temp store next node
                curr->next = nullptr;               // unlink current ndoe
                tail->next = curr;                  // link current node to end of the list
                tail = curr;                        // move the tail to the current node
                curr = temp;                        // move the current pointer to the next node
            }
        }

        // If new_head is still null, set it to the pivot (only pivot in the list)
        if ((*new_head) == nullptr)
            (*new_head) = pivot;

        (*new_end) = tail;

        // return pivot node, recursive
        return pivot;
    }

    static Node<Property>* recursive(Node<Property>* head, Node<Property>* end, int (Property::*getAttribute)() const) {
        // // base condition: if the list is empty or has one element, return head
        if (!head || head == end)
            return head;

        // increment recursion depth, update max recursion depth
        recursion_depth++;
        max_recursion_depth = std::max(max_recursion_depth, recursion_depth); // update max

        Node<Property>* new_head = nullptr; // new head after partitioning
        Node<Property>* new_end = nullptr; // new end after partitioning

        // partition the list and get the pivot node
        Node<Property>* pivot = partition(head, end, &new_head, &new_end, getAttribute);

        // if the new head is different from the pivot
        if (new_head != pivot) {
            Node<Property>* temp = new_head;

            // traverse the list to get the node before the pivot
            while (temp->next != pivot && temp->next != nullptr)
                temp = temp->next;

            // if temp->next is not null, disconnect left part from pivot
            if (temp->next != nullptr) {
                temp->next = nullptr;

                // recursively sort left part
                new_head = recursive(new_head, temp, getAttribute);

                // connect last node of left part to pivot
                temp = getTail(new_head);
                temp->next = pivot;
            }
        }

        // recursively sort the right part
        pivot->next = recursive(pivot->next, new_end, getAttribute);
        recursion_depth--;

        return new_head; // return the new head of the sorted list
    }
};

// recursive approach
class Merge {
public:
    // start the merge sort on the given list
    static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
        recursion_depth = 0;
        max_recursion_depth = 0;
        list.head = recursive(list.head, getAttribute);
        std::cout << "Maximum Mergesort Recursion Depth: " << max_recursion_depth << std::endl;
    }

private:
    static inline int recursion_depth = 0;
    static inline int max_recursion_depth = 0;

    static Node<Property>* recursive(Node<Property>* head, int (Property::*getAttribute)() const) {
        // base condition: if the list is empty or has one element, return head
        if (!head || !head->next)
            return head;

        // increment recursion depth, update max recursion depth
        recursion_depth++;
        max_recursion_depth = std::max(max_recursion_depth, recursion_depth);

        Node<Property>* first = nullptr; // first half of the list
        Node<Property>* second = nullptr; // second half of the list

        // split the list into two halves
        splitList(head, &first, &second);

        // recursively sort both parts
        first = recursive(first, getAttribute);
        second = recursive(second, getAttribute);

        // merge both parts
        Node<Property>* result = sortedMerge(first, second, getAttribute);

        recursion_depth--;

        return result; // return sorted list
    }

    // merges two sorted lists
    // connecting lists is as simple as updating pointers, no stack manipulation needed
    static Node<Property>* sortedMerge(Node<Property>* first, Node<Property>* second, int (Property::*getAttribute)() const) {
        // if one list is empty, return the other
        if (!first)
            return second;
        if (!second)
            return first;

        Node<Property>* result = nullptr;

        // compare attributes and merge
        if ((first->data.*getAttribute)() <= (second->data.*getAttribute)()) {
            // if the current node in the first list is smaller or equal, it becomes the next node in the result list
            // then recursively merge the rest of the first list (starting from the next node) with the second list
            result = first;
            result->next = sortedMerge(first->next, second, getAttribute);
        } else {
            // if the current node in the second list is smaller, it becomes the next node in the result list
            // then recursively merge the first list with the rest of the second list (starting from the next node)
            result = second;
            result->next = sortedMerge(first, second->next, getAttribute);
        }

        // return merged list
        return result;
    }

    // split list into two halves
    static void splitList(Node<Property>* source, Node<Property>** first_ref, Node<Property>** second_ref) {
        Node<Property>* slow = source;  // slow pointer
        Node<Property>* fast = source->next; // fast pointer

        // use a fast/slow strategy to get middle of list
        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        // split list into two halves
        *first_ref = source;
        *second_ref = slow->next;
        slow->next = nullptr; // terminate first half
    }
};