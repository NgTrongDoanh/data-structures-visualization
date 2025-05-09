#include "datastructures/HashTable.h"

HashTable::HashTable(int capacity) : capacity(capacity), size(0) {
    table.resize(capacity, -1);  // -1 indicates empty slot, -2 indicates deleted slot
    saveStep(-1, 0, {}, "", "", 1);
}

void HashTable::saveStep(int hightlightindex, int type, std::vector<int> line, const std::string infor, const std::string code, bool forCreate) {
    this->process.push_back({table, line, hightlightindex, infor, code, type});
}

int HashTable::hash(int key)  {
    return key % capacity;
}

int HashTable::linearProbe(int key) {
    int index = hash(key);
    int originalIndex = index;

    while (table[index] != -1 && table[index] != -2 && table[index] != key) {
        saveStep(index, 0, {}, "Finding suitable position!", "", 1);
        index = (index + 1) % capacity;
        if (index == originalIndex) {
            return -1;
        }
    }

    return index;
}

void HashTable::clear() {
    std::fill(table.begin(), table.end(), -1);
    size = 0;
}

std::vector<HashStep> HashTable::getProcess() {
    return this->process;
}

int HashTable::getSize() {
    return this->size;
}

int HashTable::getCapacity() {
    return this->capacity;
}

void HashTable::resize(int k) {
    this->process.clear();
    this->capacity = k;
    this->size = 0;
    this->table.clear();
    this->table.resize(k, -1);
    saveStep(-1, 0, {}, "Reset table and resize!", "", 1);
}

void HashTable::insert(int key) {
    this->process.clear();

    int exist = search(key);
    if (exist != -1) {
        saveStep(exist, 0, {}, "Key already exist!", "", 1);
        std::cout << "Key already exists: " << key << std::endl;
        return;
    }
    
    this->process.clear();
    int index = linearProbe(key);
    if (index == -1) {
        saveStep(-1, 0, {}, "Memory Fault!", "", 1);
        std::cout << "Hash table is full. Cannot insert key: " << key << std::endl;
        return;
    }

    if (table[index] == -1 || table[index] == -2) {
        table[index] = key;
        saveStep(index, 0, {}, "Insert Key!", "", 1);
        size++;
    }
}

void HashTable::deleteKey(int key) {
    this->process.clear();

    int index = hash(key);
    int originalIndex = index;
    while (table[index] != -1) {
        saveStep(index, 0, {}, "Finding key!", "", 1);
        if (table[index] == key) {
            table[index] = -2;  // Mark as deleted
            saveStep(index, 0, {}, "Delete key!", "", 1);
            size--;
            saveStep(-1, -1, {}, "Finish!", "", 1);
            return;
        }
        
        index = (index + 1) % capacity;
        if (index == originalIndex) {
            break;
        }
    }

    saveStep(-1, -1, {}, "NOT FOUND!", "", 1);
    std::cout << "Key not found: " << key << std::endl;
}

int HashTable::search(int key) {
    this->process.clear();
    
    int index = hash(key);
    int originalIndex = index;
    while (table[index] != -1) {
        saveStep(index, 0, {}, "Finding key!", "", 1);
        if (table[index] == key) {
            saveStep(index, 0, {}, "FOUND!", "", 1);
            return index;
        }

        index = (index + 1) % capacity;
        if (index == originalIndex) {
            break;
        }
    }

    saveStep(-1, 0, {}, "NOT FOUND!", "", 1);

    return -1;
}

void HashTable::createFromFile(const std::string& filename) {
    clear();
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    int key;
    while (file >> key) {
        insert(key);
    }
    
    file.close();
    this->process.clear();

    saveStep(-1, 0, {}, "Creating...", "", true);
}

void HashTable::createRandom(int numKeys, int maxValue) {
    clear();
    srand((int)time(0));
    
    for (int i = 0; i < numKeys; ++i) {
        int key = rand() % maxValue;
        insert(key);
    }
    
    this->process.clear();
    saveStep(-1, 0, {}, "Creating...", "", true);
}
