#ifndef CORE_DICTIONARY_H
#define CORE_DICTIONARY_H

#include "string.h"
#include "list.h"

template <typename T>
class Dictionary {
public:
    int Size() const { return keys.Size(); }
    void Set(const String& key, const T& value);
    T& Value(const String& key);
    const T& Value(const String& key) const;
    bool HasKey(const String& key) const;
    const String& Key(int index) const;
    void Remove(const String& key);
    void Clear();
private:
    List<String> keys;
    List<T> values;
};

template <typename T>
void Dictionary<T>::Set(const String& key, const T& value) {
    // If key is found, update
    const List<String>::Node* k = keys.First();
    typename List<T>::Node* v = values.First();
    while ( k ) {
        if ( k->Value() == key ) {
            v->Set(value);
            return;
        }
        k = k->Next();
        v = v->Next();
    }

    // If it was not found, create
    keys.Add(key);
    values.Add(value);
}

template <typename T>
T& Dictionary<T>::Value(const String& key) {
    static T dummy;
    const List<String>::Node* k = keys.First();
    typename List<T>::Node* v = values.First();
    while ( k ) {
        if ( k->Value() == key ) {
            return v->Value();
        }
        k = k->Next();
        v = v->Next();
    }
    return dummy;
}

template <typename T>
const T& Dictionary<T>::Value(const String& key) const {
    static T dummy;
    const List<String>::Node* k = keys.First();
    const typename List<T>::Node* v = values.First();
    while ( k ) {
        if ( k->Value() == key ) {
            return v->Value();
        }
        k = k->Next();
        v = v->Next();
    }

    return dummy;
}

template <typename T>
bool Dictionary<T>::HasKey(const String& key) const {
    const List<String>::Node* k = keys.First();
    while ( k ) {
        if ( k->Value() == key ) {
            return true;
        }
        k = k->Next();
    }
    return false;
}

template <typename T>
const String& Dictionary<T>::Key(int index) const {
    const List<String>::Node* k = keys.First();
    for ( int i = 0; i < index; i++ ) k = k->Next();
    return k->Value();
}

template <typename T>
void Dictionary<T>::Remove(const String& key) {
    List<String>::Node* k = keys.First();
    typename List<T>::Node* v = values.First();
    while ( k ) {
        if ( k->Value() == key ) {
            keys.Remove(k);
            values.Remove(v);
            break;
        }
        k = k->Next();
        v = v->Next();
    }
}

template <typename T>
void Dictionary<T>::Clear() {
    keys.Clear();
    values.Clear();
}

#endif // CORE_DICTIONARY_H
