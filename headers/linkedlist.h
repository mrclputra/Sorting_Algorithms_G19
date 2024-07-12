#pragma once

#include <iostream>
#include "property.h"

// node class template
template <typename T>
class Node {
public:
    T data;
    Node* next;

    // constructor
    Node(T data) : data(data), next(nullptr) {}
};

// linked list class template
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    // constructor
    LinkedList() : head(nullptr) {}
    
    // destructor
    ~LinkedList() {
        clear();
    }

    // add element to end of list
    void append(T data) {
        Node<T>* new_node = new Node<T>(data);
        if(head == nullptr) {
            head = new_node; // set as head if empty
        } else {
            Node<T>* temp = head;
            while(temp->next != nullptr) {
                temp = temp->next; // iterate to end
            }
            temp->next = new_node; // add to end
        }
    }

    // add element to beginning of list
    void prepend(T data) {
        Node<T>* new_node = new Node<T>(data);
        new_node->next = head;
        head = new_node;
    }

    // print list
    // for testing
    void print() {
        Node<T>* temp = head;
        while(temp != nullptr) {
            printData(temp->data);
            temp = temp->next;
        }
        std::cout << "null" << std::endl;
    }

    // clear the list
    void clear() {
        Node<T>* current = head;
        Node<T>* next_node;

        while(current != nullptr) {
            next_node = current->next;
            delete current;
            current = next_node;
        }

        head = nullptr;
    }

private:
    // print data based on type
    void printData(const T& data) {
        if constexpr (std::is_same<T, Property>::value) {
            // if datatype is property, print specific attribute
            std::cout << data.getID() << std::endl;
        } else {
            // else print normally
            std::cout << data << std::endl;
        }
    }
};