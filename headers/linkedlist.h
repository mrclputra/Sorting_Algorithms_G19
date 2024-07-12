#pragma once

#include <iostream>
#include "property.h"

// node class template
class Node {
    public: 
    Property data;
    Node* next;

    // constructor
    Node(Property data) : data(data), next(nullptr) {}
};

// linked list class template
class LinkedList {
private:
    Node* head;

public:
    // constructor
    LinkedList() : head(nullptr) {}
    
    // destructor
    ~LinkedList() {
        clear();
    }

    // add element to end of list
    void append(Property data) {
        Node* new_node = new Node(data);
        if(head == nullptr) {
            head = new_node; // set as head if empty
        } else {
            Node* temp = head;
            while(temp->next != nullptr) {
                temp = temp->next; // iterate to end
            }
            temp->next = new_node; // add to end
        }
    }

    // add element to beginning of list
    void prepend(Property data) {
        Node* new_node = new Node(data);
        new_node->next = head;
        head = new_node;
    }

    // print list, ids only
    void printIds() {
        Node* temp = head;
        while(temp != nullptr) {
            std::cout << temp->data.getID() << std::endl;
            temp = temp->next;
        }
        std::cout << "null" << std::endl;
    }

    // print list, all elements
    void printAll() {
        Node* temp = head;
        while(temp != nullptr) {
            // call property print here
            temp->data.display();
            temp = temp->next;
            std::cout << std::endl;
        }
    }

    // clear the list
    void clear() {
        Node* current = head;
        Node* next_node;

        while(current != nullptr) {
            next_node = current->next;
            delete current;
            current = next_node;
        }

        head = nullptr;
    }
};