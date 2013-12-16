#ifndef CORE_LIST_H
#define CORE_LIST_H

#include "array.h"

template <typename T>
class List {
public:
    // Inner Node class
    class Node {
    public:
        friend class List<T>;
        Node(List<T>* list, Node* prevNode, const T& value);
        Node* Next() { return next; }
        const Node* Next() const { return next; }
        void Set(const T& val) { value = val; }
        T& Value() { return value; }
        const T& Value() const { return value; }
    private:
        T value;
        Node* next;
    };


    List() : first(0), last(0) {}
    ~List();

    int Size() const;
    bool IsEmpty() const;
    Node* Add(const T& val);
    Node* InsertBefore(const Node* node, const T& val);
    Node* InsertAfter(Node* node, const T& val);
    Node* First() { return first; }
    Node* Last() { return last; }
    const Node* First() const { return first; }
    const Node* Last() const { return last; }
    void Remove(Node* node);
    void Remove(const T& obj);
    void Clear();
    Array<T> ToArray();
    void Sort(bool (*compareFunc)(T&, T&));
private:
    Node* first;
    Node* last;
};

template <typename T>
List<T>::Node::Node(List<T>* list, Node* prevNode, const T& value) : value(value) {
    if ( prevNode ) {
        next = prevNode->next;
        prevNode->next = this;
    } else {
        next = list->First();
    }
}

template <typename T>
List<T>::~List() {
    Clear();
}

template <typename T>
int List<T>::Size() const {
    int count = 0;
    const Node* node = first;
    while ( node ) {
        count++;
        node = node->Next();
    }
    return count;
}

template <typename T>
bool List<T>::IsEmpty() const {
    return first == 0;
}

template <typename T>
typename List<T>::Node* List<T>::Add(const T& val) {
    return InsertAfter(last, val);
}

template <typename T>
typename List<T>::Node* List<T>::InsertBefore(const Node* node, const T& val) {
    if ( node == first ) {
        return InsertAfter(0, val);
    } else {
        const Node* current = first;
        while ( current->Next() ) {
            if ( current->Next() == node ) {
                return InsertAfter(current, val);
            }
            current = current->Next();
        }
    }
    return 0;
}

template <typename T>
typename List<T>::Node* List<T>::InsertAfter(Node* node, const T& val) {
    Node* newNode = new Node(this, node, val);
    if ( node == 0 ) first = newNode;
    if ( !newNode->Next() ) last = newNode;
    return newNode;
}

template <typename T>
void List<T>::Remove(Node* node) {
    // Fix previous node link
    if ( node == first ) {
        first = node->Next();
        if ( node == last ) last = 0;    // If it was the only node, last is NULL
    } else {
        Node* current = first;
        while ( current ) {
            if ( current->Next() == node ) {
                current->next = node->Next();
                if ( node == last ) last = current; // Fix last node
                break;
            }
            current = current->Next();
        }
    }

    delete node;
}

template <typename T>
void List<T>::Remove(const T& obj) {
    Node* current = first;
    while ( current ) {
        if ( current->Value() == obj ) {
            Remove(current->Value());
            break;
        }
        current = current->Next();
    }
}

template <typename T>
void List<T>::Clear() {
    while ( !IsEmpty() ) {
        Remove(first);
    }
}

template <typename T>
Array<T> List<T>::ToArray() {
    Array<T> arr(Size());
    Node* node = first;
    while ( node ) {
        arr.Add(node->Value());
        node = node->Next();
    }
    return arr;
}

template <typename T>
void List<T>::Sort(bool (*compareFunc)(T&, T&)) {
    // An array of zero or one elements is already sorted
    if ( Size() <= 1 ) return;

    // Select pivot
    Node* pivotNode = First();
    for ( int i = 0; i > Size()/2; i++ ) pivotNode = pivotNode->Next();

    // Create less and greater lists
    List<T> less, greater;
    Node* node = First();
    while ( node ) {
        if ( node != pivotNode ) {
            if ( compareFunc(node->Value(), pivotNode->Value()) ) {
                less.Add(node->Value());
            } else {
                greater.Add(node->Value());
            }
        }
        node = node->Next();
    }

    // Apply quicksort to both lists
    less.Sort(compareFunc);
    greater.Sort(compareFunc);

    // Clear list and add values in order
    T pivotValue = pivotNode->Value();
    Clear();
    node = less.First();
    while ( node ) {
        Add(node->Value());
        node = node->Next();
    }
    Add(pivotValue);
    node = greater.First();
    while ( node ) {
        Add(node->Value());
        node = node->Next();
    }
}

#endif // CORE_LIST_H
