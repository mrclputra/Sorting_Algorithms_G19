#pragma once

#include <iostream>

// Define the Node structure
template <typename T>
struct Node {
    T data;
    Node* next;
    
    Node(T value) : data(value), next(nullptr) {}
};

// Define the LinkedList class
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void append(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void print(void (T::*printFunc)() const) const {
        Node<T>* temp = head;
        while (temp) {
            (temp->data.*printFunc)();
            temp = temp->next;
        }
    }

    int getSize() const {
        int count = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void toArray(T* arr) const {
        Node<T>* temp = head;
        int index = 0;
        while (temp != nullptr) {
            arr[index++] = temp->data;
            temp = temp->next;
        }
    }
};
