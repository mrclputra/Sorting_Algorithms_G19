#pragma once
#include <stack>

#include "linkedlist.h"
#include "property.h"

// my modified linked list quicksort based on 
// https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
class Quick {
public:
    static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
        recursion_depth = 0;
        max_recursion_depth = 0;
        list.head = recursive(list.head, getTail(list.head), getAttribute);
        std::cout << "Maximum Quicksort Recursion Depth: " << max_recursion_depth << std::endl;
    }

private:
    // track space complexity
    static inline int recursion_depth = 0;
    static inline int max_recursion_depth = 0;

    static Node<Property>* getTail(Node<Property>* curr) {
        while (curr != nullptr && curr->next != nullptr)
            curr = curr->next;
        return curr;
    }

    static Node<Property>* partition(Node<Property>* head, Node<Property>* end, Node<Property>** new_head, Node<Property>** new_end, int (Property::*getAttribute)() const) {
        if (!head || !end || !new_head || !new_end) return nullptr;

        Node<Property>* pivot = end;
        Node<Property>* prev = nullptr;
        Node<Property>* curr = head;
        Node<Property>* tail = pivot;

        // partition the list
        while (curr != pivot) {
            if ((curr->data.*getAttribute)() < (pivot->data.*getAttribute)()) {
                if ((*new_head) == nullptr)
                    (*new_head) = curr;

                prev = curr;
                curr = curr->next;
            } else {
                if (prev)
                    prev->next = curr->next;

                Node<Property>* temp = curr->next;
                curr->next = nullptr;
                tail->next = curr;
                tail = curr;
                curr = temp;
            }
        }

        if ((*new_head) == nullptr)
            (*new_head) = pivot;

        (*new_end) = tail;

        return pivot;
    }

    static Node<Property>* recursive(Node<Property>* head, Node<Property>* end, int (Property::*getAttribute)() const) {
        // base condition
        if (!head || head == end)
            return head;

        // increment recursion depth
        recursion_depth++;
        max_recursion_depth = std::max(max_recursion_depth, recursion_depth); // update max

        Node<Property>* new_head = nullptr;
        Node<Property>* new_end = nullptr;

        Node<Property>* pivot = partition(head, end, &new_head, &new_end, getAttribute);

        if (new_head != pivot) {
            Node<Property>* temp = new_head;
            while (temp->next != pivot && temp->next != nullptr)
                temp = temp->next;
            if (temp->next != nullptr) {
                temp->next = nullptr;

                new_head = recursive(new_head, temp, getAttribute);

                temp = getTail(new_head);
                temp->next = pivot;
            }
        }

        pivot->next = recursive(pivot->next, new_end, getAttribute);
        recursion_depth--;

        return new_head;
    }
};

// recursive approach
class Merge {
public:
    static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
        recursion_depth = 0;
        max_recursion_depth = 0;
        list.head = recursive(list.head, getAttribute);
        std::cout << "Maximum Mergesort Recursion Depth: " << max_recursion_depth << std::endl;
    }

private:
    static inline int recursion_depth = 0;
    static inline int max_recursion_depth = 0;

    static Node<Property>* recursive(Node<Property>* head, int (Property::*getAttribute)() const) {
        if (!head || !head->next)
            return head;

        recursion_depth++;
        max_recursion_depth = std::max(max_recursion_depth, recursion_depth);

        Node<Property>* first = nullptr;
        Node<Property>* second = nullptr;

        splitList(head, &first, &second);

        first = recursive(first, getAttribute);
        second = recursive(second, getAttribute);

        Node<Property>* result = sortedMerge(first, second, getAttribute);

        recursion_depth--;

        return result;
    }

    static Node<Property>* sortedMerge(Node<Property>* first, Node<Property>* second, int (Property::*getAttribute)() const) {
        if (!first)
            return second;
        if (!second)
            return first;

        Node<Property>* result = nullptr;

        if ((first->data.*getAttribute)() <= (second->data.*getAttribute)()) {
            result = first;
            result->next = sortedMerge(first->next, second, getAttribute);
        } else {
            result = second;
            result->next = sortedMerge(first, second->next, getAttribute);
        }

        return result;
    }

    static void splitList(Node<Property>* source, Node<Property>** first_ref, Node<Property>** second_ref) {
        Node<Property>* slow = source;
        Node<Property>* fast = source->next;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *first_ref = source;
        *second_ref = slow->next;
        slow->next = nullptr;
    }
};

/*
iterative approaches below
*/

// class Quick {
// public:
//     static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
//         if (!list.head || !list.head->next) return; // List is empty or has only one element

//         // Stack to store the sublists
//         std::stack<std::pair<Node<Property>*, Node<Property>*>> stack;
//         stack.push({list.head, getTail(list.head)});

//         while (!stack.empty()) {
//             auto [head, end] = stack.top();
//             stack.pop();

//             if (!head || head == end) continue; // No need to sort a single element or empty list

//             Node<Property>* new_head = nullptr;
//             Node<Property>* new_end = nullptr;

//             Node<Property>* pivot = partition(head, end, &new_head, &new_end, getAttribute);

//             if (new_head != pivot) {
//                 Node<Property>* temp = new_head;
//                 while (temp->next != pivot && temp->next != nullptr) {
//                     temp = temp->next;
//                 }
//                 if (temp->next != nullptr) {
//                     temp->next = nullptr;
//                     stack.push({new_head, temp});
//                 }
//             }

//             pivot->next = stack.empty() ? nullptr : stack.top().first;
//             stack.push({pivot->next, new_end});
//         }

//         // Update the list head to the sorted list
//         list.head = stack.top().first;
//     }

// private:
//     static Node<Property>* getTail(Node<Property>* curr) {
//         while (curr != nullptr && curr->next != nullptr)
//             curr = curr->next;
//         return curr;
//     }

//     static Node<Property>* partition(Node<Property>* head, Node<Property>* end, Node<Property>** new_head, Node<Property>** new_end, int (Property::*getAttribute)() const) {
//         if (!head || !end || !new_head || !new_end) return nullptr;

//         Node<Property>* pivot = end;
//         Node<Property>* prev = nullptr;
//         Node<Property>* curr = head;
//         Node<Property>* tail = pivot;

//         // Partition the list
//         while (curr != pivot) {
//             if ((curr->data.*getAttribute)() < (pivot->data.*getAttribute)()) {
//                 if ((*new_head) == nullptr)
//                     (*new_head) = curr;

//                 prev = curr;
//                 curr = curr->next;
//             } else {
//                 if (prev)
//                     prev->next = curr->next;

//                 Node<Property>* temp = curr->next;
//                 curr->next = nullptr;
//                 tail->next = curr;
//                 tail = curr;
//                 curr = temp;
//             }
//         }

//         if ((*new_head) == nullptr)
//             (*new_head) = pivot;

//         (*new_end) = tail;

//         return pivot;
//     }
// };

// class Merge {
// public:
//     static void sort(LinkedList<Property>& list, int (Property::*getAttribute)() const) {
//         if (list.head == nullptr || list.head->next == nullptr) {
//             // List is empty or has a single element; already sorted
//             return;
//         }

//         // Step 1: Get the length of the linked list
//         int length = getLength(list.head);

//         // Step 2: Iteratively merge sublists of increasing size
//         Node<Property>* head = list.head;
//         Node<Property>* new_head = nullptr;

//         for (int size = 1; size < length; size *= 2) {
//             Node<Property>* current = head;
//             Node<Property>* tail = nullptr;

//             // Merge sublists of size 'size'
//             while (current != nullptr) {
//                 Node<Property>* left = current;
//                 Node<Property>* right = splitList(left, size);
//                 current = splitList(right, size);

//                 // Merge the two sublists and update the tail
//                 Node<Property>* merged = sortedMerge(left, right, getAttribute);
//                 if (new_head == nullptr) {
//                     new_head = merged;
//                 }
//                 if (tail != nullptr) {
//                     tail->next = merged;
//                 }
//                 tail = getTail(merged);
//             }
//             list.head = new_head;
//         }
//     }

// private:
//     static int getLength(Node<Property>* head) {
//         int length = 0;
//         Node<Property>* current = head;
//         while (current != nullptr) {
//             length++;
//             current = current->next;
//         }
//         return length;
//     }

//     static Node<Property>* splitList(Node<Property>* head, int size) {
//         if (head == nullptr) return nullptr;

//         Node<Property>* current = head;
//         Node<Property>* prev = nullptr;

//         for (int i = 0; i < size && current != nullptr; i++) {
//             prev = current;
//             current = current->next;
//         }

//         if (prev != nullptr) {
//             prev->next = nullptr;
//         }

//         return current;
//     }

//     static Node<Property>* sortedMerge(Node<Property>* first, Node<Property>* second, int (Property::*getAttribute)() const) {
//         if (!first) return second;
//         if (!second) return first;

//         Node<Property>* result = nullptr;

//         if ((first->data.*getAttribute)() <= (second->data.*getAttribute)()) {
//             result = first;
//             result->next = sortedMerge(first->next, second, getAttribute);
//         } else {
//             result = second;
//             result->next = sortedMerge(first, second->next, getAttribute);
//         }

//         return result;
//     }

//     static Node<Property>* getTail(Node<Property>* head) {
//         Node<Property>* tail = head;
//         while (tail != nullptr && tail->next != nullptr) {
//             tail = tail->next;
//         }
//         return tail;
//     }
// };