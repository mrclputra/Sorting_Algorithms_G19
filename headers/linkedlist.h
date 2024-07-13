#pragma once

#include <iostream>

// node structure
template <typename T>
struct Node {
    T data;
    Node* next;
    
    Node(T value) : data(value), next(nullptr) {}
};

// linked list class template
template <typename T>
class LinkedList {
public:
    Node<T>* head = nullptr;

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

    // print linked list for int type
    void print() const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << std::endl; // Print integer directly
            temp = temp->next;
        }
        std::cout << "null" << std::endl;
    }

    // overloaded print function for property type
    void print(void (Property::*printFunc)() const) const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            (temp->data.*printFunc)(); // Call specific print function for Property
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

    // get size
    int getSize() const {
        int size = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            ++size;
            temp = temp->next;
        }
        return size;
    }
};