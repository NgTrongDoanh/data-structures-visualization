#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../core/General.h"

struct HashStep {
    std::vector<int> table;
    std::vector<int> line;
    int highlightIndex;
    std::string infor;
    std::string code;
    int type;
};

class HashTable {
private:
    std::vector<int> table;
    int capacity;
    int size;

    std::vector<HashStep> process;

    void saveStep(int hightlightindex, int type, std::vector<int> line, const std::string infor, const std::string code, bool forCreate = false);

    int hash(int key);
    int linearProbe(int key);
    void clear();

public:
    HashTable(int capacity);
    HashTable() {};
    virtual ~HashTable() = default;

    std::vector<HashStep> getProcess();
    int getSize();
    int getCapacity();

    void resize(int k);
    
    void insert(int key);
    void deleteKey(int key);
    int search(int key);
    void createFromFile(const std::string& filename);
    void createRandom(int numKeys, int maxValue);
    void display();
};

#endif // HASHTABLE_H