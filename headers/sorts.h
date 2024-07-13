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
        list.head = recursive(list.head, getTail(list.head), getAttribute);
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

        if ((*newHead) == nullptr) {
            (*newHead) = pivot;
        }

        (*newEnd) = tail;

        return pivot;
    }

    static Node<Property>* recursive(Node<Property>* head, Node<Property>* end, int (Property::*getAttribute)() const) {
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

            newHead = recursive(newHead, tmp, getAttribute);

            tmp = getTail(newHead);
            tmp->next = pivot;
        }

        pivot->next = recursive(pivot->next, newEnd, getAttribute);

        return newHead;
    }
};