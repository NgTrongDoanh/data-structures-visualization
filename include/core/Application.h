#ifndef APPLICATION_H
#define APPLICATION_H

#include "../core/General.h"
#include "Menu.h"

class Application {
    private:
        int tab;
        Color theme;

    public:
        Application();
        virtual ~Application();

        int menu();
        void run();
        
        int hashTable();
        int maxHeap();
        int avlTree();
        int Tree234();
        int trie();
        int graph();
};

#endif // APPLICATION_H
