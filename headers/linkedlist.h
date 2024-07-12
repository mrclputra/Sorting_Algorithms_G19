#pragma once

#include <iostream>
#include <exception>

// node class template
template <typename T>
class Node {
    public: 
    T data;
    Node<T>* next;

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
            // if no elements in list
            head == new_node;
        } else {
            // else add to end
            Node<T>* temp = head;
            while(temp->next != nullptr) {
                // iterate to end
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }

    // add element to beginning of list
    void prepend(T data) {
        Node<T>* new_node = new Node<T>(data);
        new_node->next = head;
        head = new_node;
    }

    // print list
    void print() {
        Node<T>* temp = head;
        while(temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
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
};