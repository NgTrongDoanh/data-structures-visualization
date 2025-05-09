#ifndef MENU_H
#define MENU_H

#include "../core/General.h"
#include "../gui/Util.h"
#include "../visualization/HashTableVisualize.h"
#include "../visualization/MaxHeapVisualize.h"
#include "../visualization/AVLTreeVisualize.h"
#include "../visualization/Tree234Visualize.h"
#include "../visualization/TrieVisualize.h"
#include "../visualization/GraphVisualize.h"

class Menu {
    private:
        ImageButton avlTree;
        ImageButton hashTable;
        ImageButton Tree234;
        ImageButton trie;
        ImageButton maxHeap;
        ImageButton graph;

        Texture2D mode;
        bool isDarkMode = false;

    public:
        Menu();
        virtual ~Menu();

        int8_t clicked();
        bool getDarkMode();

        void hanlde();

        void draw();
};

#endif // MENU_H
