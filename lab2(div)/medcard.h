#ifndef MEDCARD_H
#define MEDCARD_H

#include <iostream>
#include <vector>
#include <string>
#include "medicalrecord.h"
using namespace std;

template <typename Key, typename Value>
class MedCard {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    static const int size = 1000000;
    vector<Node*> table;

    int hash(const Key& key);

public:
    MedCard();

    ~MedCard();

    void insert(const Key& key, const Value& value);

    bool find(const Key& key, Value& value);

    void update(const Key& key, const Value& value);

    void remove(const Key& key);

    void makeMedCard(MedicalRecord& patient);

    vector<Key> getAllKeys() const;

};

#endif /* MEDCARD_H */