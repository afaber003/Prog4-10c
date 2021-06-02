#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>

using namespace std;

struct hashtoken
{
  hashtoken(string w, string c)
  {
    word = w;
    code = c;
  }
  
  string word;
  string code;
};



class HashTable {
 
 public:
    HashTable(int);
	int computeHash(const string &) const;
    void insert(string, string);
    string getMappedValue(string s) const;
  
  private:
    list<hashtoken *> *hashtable;
    int size;
};

#endif 