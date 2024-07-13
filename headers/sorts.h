#pragma once

#include <iostream>
#include <functional>

#include "property.h"
#include "linkedlist.h"

// my modified linked list quicksort based on 
// https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
class Quick {
public:
    static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
        list.head = quicksort(list.head, getTail(list.head), getAttribute);
    }

private:
    static Node<Property>* getTail(Node<Property>* cur) {
        while (cur != nullptr && cur->next != nullptr) {
            cur = cur->next;
        }
        return cur;
    }

    static Node<Property>* partition(Node<Property>* head, Node<Property>* end, Node<Property>** newHead, Node<Property>** newEnd, int (Property::*getAttribute)() const) {
        Node<Property>* pivot = end;
        Node<Property>* prev = nullptr, *cur = head, *tail = pivot;

        while (cur != pivot) {
            if ((cur->data.*getAttribute)() < (pivot->data.*getAttribute)()) {
                if ((*newHead) == nullptr) {
                    (*newHead) = cur;
                }
                prev = cur;
                cur = cur->next;
            } else {
                if (prev) {
                    prev->next = cur->next;
                }
                Node<Property>* tmp = cur->next;
                cur->next = nullptr;
                tail->next = cur;
                tail = cur;
                cur = tmp;
            }
        }

        if (*newHead == nullptr) {
            *newHead = pivot;
        }

        *newEnd = tail;

        return pivot;
    }

    static Node<Property>* quicksort(Node<Property>* head, Node<Property>* end, int (Property::*getAttribute)() const) {
        if (!head || head == end) {
            return head;
        }

        Node<Property>* newHead = nullptr;
        Node<Property>* newEnd = nullptr;

        Node<Property>* pivot = partition(head, end, &newHead, &newEnd, getAttribute);

        if (newHead != pivot) {
            Node<Property>* tmp = newHead;
            while (tmp->next != pivot) {
                tmp = tmp->next;
            }
            tmp->next = nullptr;

            newHead = quicksort(newHead, tmp, getAttribute);

            tmp = getTail(newHead);
            tmp->next = pivot;
        }

        pivot->next = quicksort(pivot->next, newEnd, getAttribute);

        return newHead;
    }
};

class Merge {
public: 
    static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
        list.head = mergeSort(list.head, getAttribute);
    }

private:
    // merge two linkedlists
    static Node<Property>* merge(Node<Property>* left, Node<Property>* right, int (Property::*getAttribute)() const) {
        if (!left) return right;
        if (!right) return left;

        Node<Property>* result = nullptr;

        if ((left->data.*getAttribute)() <= (right->data.*getAttribute)()) {
            result = left;
            result->next = merge(left->next, right, getAttribute);
        } else {
            result = right;
            result->next = merge(left, right->next, getAttribute);
        }

        return result;
    }

    // get middle of list
    static Node<Property>* getMiddle(Node<Property>* head) {
        if (!head) return head;

        Node<Property>* slow = head;
        Node<Property>* fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    // sort
    static Node<Property>* mergeSort(Node<Property>* head, int (Property::*getAttribute)() const) {
        if (!head || !head->next) {
            return head;
        }

        Node<Property>* middle = getMiddle(head);
        Node<Property>* second_half_start = middle->next;
        middle->next = nullptr;

        Node<Property>* left = mergeSort(head, getAttribute);
        Node<Property>* right = mergeSort(second_half_start, getAttribute);

        return merge(left, right, getAttribute);
    }
};

/*
alternative merge sort implementation below
*/
// class Merge {
// public:
//     static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
//         list.head = mergeSort(list.head, getAttribute);
//     }

// private:
//     static Node<Property>* merge(Node<Property>* first, Node<Property>* second, int (Property::*getAttribute)() const) {
//         if (!first) return second;
//         if (!second) return first;

//         Node<Property>* result = nullptr;

//         if ((first->data.*getAttribute)() <= (second->data.*getAttribute)()) {
//             result = first;
//             result->next = merge(first->next, second, getAttribute);
//         } else {
//             result = second;
//             result->next = merge(first, second->next, getAttribute);
//         }

//         return result;
//     }

//     static Node<Property>* getMiddle(Node<Property>* head) {
//         if (!head) return head;

//         Node<Property>* slow = head;
//         Node<Property>* fast = head->next;

//         while (fast && fast->next) {
//             slow = slow->next;
//             fast = fast->next->next;
//         }

//         return slow;
//     }

//     static Node<Property>* mergeSort(Node<Property>* head, int (Property::*getAttribute)() const) {
//         if (!head || !head->next) {
//             return head;
//         }

//         Node<Property>* middle = getMiddle(head);
//         Node<Property>* nextOfMiddle = middle->next;
//         middle->next = nullptr;

//         Node<Property>* left = mergeSort(head, getAttribute);
//         Node<Property>* right = mergeSort(nextOfMiddle, getAttribute);

//         return merge(left, right, getAttribute);
//     }
// };