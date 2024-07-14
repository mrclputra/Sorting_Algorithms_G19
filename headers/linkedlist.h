#pragma once

#include <iostream>

// node structure
template <typename T>
struct Node {
public:
    T data;
    Node* next;
    
    Node(T value) : data(value), next(nullptr) {}
};

// linked list class template
template <typename T>
class LinkedList {
public:
    Node<T>* head;

    // default constructor
    LinkedList() { head = NULL; }

    // copy constructor
    LinkedList(const LinkedList& other) {
        copyFrom(other);
    }

    // copy assignment operator
    // used to handle the assignment of one linked list to another, i.e. in functions that return the linkedlist
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

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

    // print linked list for standard type
    void print() const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << std::endl;
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // overloaded print function for property type
    void print(void (T::*printFunc)() const ) const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            (temp->data.*printFunc)(); // Call specific print function for Property
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // clear the list
    void clear() {
        Node<T>* current = head;
        while(current != nullptr) {
            Node<T>* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = nullptr;
    }

    // get size
    int size() const {
        int size = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            ++size;
            temp = temp->next;
        }
        return size;
    }

private:
    // helper function to copy from another linkedlist
    void copyFrom(const LinkedList& other) {
        if (!other.head) {
            head = nullptr;
            return;
        }

        head = new Node<T>(other.head->data);
        Node<T>* current = head;
        Node<T>* otherCurrent = other.head->next;

        while (otherCurrent) {
            current->next = new Node<T>(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }
};