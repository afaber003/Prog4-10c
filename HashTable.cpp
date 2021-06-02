#include "HashTable.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

HashTable::HashTable(int s) {
    size = s;
    hashtable = new list<hashtoken*>[size];
}

int HashTable::computeHash(const string& s) const {
    int stringHash = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        stringHash = ((stringHash * 3) % size + s.at(i)) % size;
    }

    //int sizeOfString = s.size();
    //int hashIndex = sizeOfString % size;
    int hashIndex = stringHash % size;

    return hashIndex;
}

void HashTable::insert(string putWord, string putCode) {
    int putIndex = computeHash(putWord);
    for (auto i = hashtable[putIndex].begin(); i != hashtable[putIndex].end(); ++i) {
        if ((*i)->word == putWord) {
            return;
        }
    }
    hashtoken* newhashtoken = new hashtoken(putWord, putCode);
    hashtable[putIndex].push_back(newhashtoken);
}

string HashTable::getMappedValue(string s) const {
    int containIndex = computeHash(s);

    for (auto i = hashtable[containIndex].begin(); i != hashtable[containIndex].end(); ++i) {
        if ((*i)->word == s) {
            return (*i)->code;
        }
    }

    return "";
}
