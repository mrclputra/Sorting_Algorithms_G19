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
        if (list.head != nullptr) {
            list.head = quicksort(list.head, getTail(list.head), getAttribute);
        }
    }

private:
    static Node<Property>* getTail(Node<Property>* curr) {
        while (curr != nullptr && curr->next != nullptr) {
            curr = curr->next;
        }
        return curr;
    }

    static Node<Property>* partition(Node<Property>* head, Node<Property>* end, Node<Property>** new_head, Node<Property>** new_end, int (Property::*getAttribute)() const) {
        if (!head || !end || !new_head || !new_end) {
            std::cerr << "Error: Null pointer encountered in partition function" << std::endl;
            return nullptr;
        }

        Node<Property>* pivot = end;
        Node<Property>* prev = nullptr, *curr = head, *tail = pivot;

        while (curr != pivot) {
            if ((curr->data.*getAttribute)() < (pivot->data.*getAttribute)()) {
                if ((*new_head) == nullptr) {
                    (*new_head) = curr;
                }
                prev = curr;
                curr = curr->next;
            } else {
                if (prev) {
                    prev->next = curr->next;
                }
                Node<Property>* tmp = curr->next;
                curr->next = nullptr;
                tail->next = curr;
                tail = curr;
                curr = tmp;
            }
        }

        if (*new_head == nullptr) {
            *new_head = pivot;
        }

        *new_end = tail;

        return pivot;
    }

    static Node<Property>* quicksort(Node<Property>* head, Node<Property>* end, int (Property::*getAttribute)() const) {
        if (!head || head == end) {
            return head;
        }

        Node<Property>* new_head = nullptr;
        Node<Property>* new_end = nullptr;

        Node<Property>* pivot = partition(head, end, &new_head, &new_end, getAttribute);

        if (new_head != pivot) {
            Node<Property>* tmp = new_head;
            while (tmp->next != pivot) {
                tmp = tmp->next;
            }
            tmp->next = nullptr;

            new_head = quicksort(new_head, tmp, getAttribute);

            tmp = getTail(new_head);
            tmp->next = pivot;
        }

        pivot->next = quicksort(pivot->next, new_end, getAttribute);

        return new_head;
    }
};

class Merge {
public:
    static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
        list.head = mergeSort(list.head, getAttribute);
    }

private:
    static Node<Property>* mergeSort(Node<Property>* head, int (Property::*getAttribute)() const) {
        if (!head || !head->next) return head;

        Node<Property>* middle = getMiddle(head);
        Node<Property>* nextOfMiddle = middle->next;

        middle->next = nullptr; // Split the list into two halves

        Node<Property>* left = mergeSort(head, getAttribute);
        Node<Property>* right = mergeSort(nextOfMiddle, getAttribute);

        return merge(left, right, getAttribute);
    }

    static Node<Property>* getMiddle(Node<Property>* head) {
        if (!head) return head;

        Node<Property>* slow = head;
        Node<Property>* fast = head->next;

        // Move fast by 2 and slow by 1
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

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
};