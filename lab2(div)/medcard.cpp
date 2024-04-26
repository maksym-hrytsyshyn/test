#include "medcard.h"
#include <iostream>
#include <vector>
#include <string>
#include "medicalrecord.h"
#include "fill.h"
using namespace std;

template <typename Key, typename Value>
int MedCard<Key, Value>::hash(const Key& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 10 + c) % size;
    }
    return hash;
}

template <typename Key, typename Value>  
MedCard<Key, Value>::MedCard() : table(size, nullptr) {
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

template <typename Key, typename Value>
MedCard<Key, Value>::~MedCard() {
    for (int i = 0; i < size; i++) {
        Node* current = table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
} 

template <typename Key, typename Value>
void MedCard<Key, Value>::insert(const Key& key, const Value& value) {
    int index = hash(key);
    Node* newNode = new Node(key, value);
    if (!table[index]) {
        table[index] = newNode;
    } else {
        Node* current = table[index];
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

template <typename Key, typename Value>
bool MedCard<Key, Value>::find(const Key& key, Value& value) {
    int index = hash(key);
    Node* current = table[index];
    while (current) {
        if (current->key == key) {
            value = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename Key, typename Value>
void MedCard<Key, Value>::update(const Key& key, const Value& value) {
    int index = hash(key);
    Node* current = table[index];
    while (current) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    cout << "Key not found in hash table" << endl;
}

template <typename Key, typename Value>
void MedCard<Key, Value>::remove(const Key& key) {
    int index = hash(key);
    Node* current = table[index];
    Node* prev = nullptr;
    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

template <typename Key, typename Value>
void MedCard<Key, Value>::makeMedCard(MedicalRecord& patient) {
    cout << "Enter the patient's full name: ";
    getline(cin, patient.fullName);
    cout << "Enter the patient's date of birth (dd mm yyyy): ";
    cin >> patient.dateOfBirth.day >> patient.dateOfBirth.month >> patient.dateOfBirth.year;
    cin.ignore();
    cout << "Your patient's personal code: ";
    string patientID = generateRandomID();
    cout << patientID << endl;
    insert(patientID, patient);
    cout << "Patient card added successfully! Patient ID: " << patientID << endl;
}

template <typename Key, typename Value>
vector<Key> MedCard<Key, Value>::getAllKeys() const {
    vector<Key> keys;
    for (int i = 0; i < size; i++) {
        Node* current = table[i];
        while (current) {
            keys.push_back(current->key);
            current = current->next;
        }
    }
    return keys;
}   

template class MedCard<string, MedicalRecord>;