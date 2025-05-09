#ifndef TRIEVISUALIZE_H
#define TRIEVISUALIZE_H

#include "datastructures/Trie.h"
#include "gui/Util.h" 

class TrieVisualize {
    private:
        Trie tree;

        TrieStep step;
        int type = 0;
        
        ProgressBar progressBar;
        int stepIndex;
        int frame;
        int numFrameOfAnimation;
        
        Button createButton;
        bool isCreateChosen;
        Button randomButton;
        Button loadFileButton;
        
        Button insertButton;
        bool isInsertChosen;
        
        Button deleteButton;
        bool isDeleteChosen;
        
        Button searchButton;
        bool isSearchChosen;
        
        InputStr inputNumber;
        Button playButton;
        
        Font font;

    public:
        TrieVisualize(Font font);
        TrieVisualize();
        virtual ~TrieVisualize();

        void updateStep(int index);
        // int update_animation();
        
        void insert();
        void deleteNode();
        void search();
        void createWithRandomizedData(int n = 5, int length = 5);
        void createFromFile();
        
        int handle();

        void drawButtons();
        void drawNode(TrieNode* root, TrieNode* highlight, int frame, int numFrame, Font font, bool isNotification = false);
        void drawTree();        
        void draw();
};

#endif // TRIEVISUALIZE_H
    