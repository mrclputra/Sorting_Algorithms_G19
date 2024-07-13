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

    // print, for property functions only
    void print(void (T::*printFunc)() const) {
        Node<T>* temp = head;
        while(temp != nullptr) {
            (temp->data.*printFunc)();
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

private:
    // print data based on type
    void printData(const T& data) {
        if constexpr (std::is_same<T, Property>::value) {
            // if datatype is property, print specific attribute
            std::cout << data.getId() << std::endl;
        } else {
            // else print normally
            std::cout << data << std::endl;
        }
    }
};