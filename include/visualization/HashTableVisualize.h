#ifndef HASHTABLEVISUALIZE_H
#define HASHTABLEVISUALIZE_H

#include "datastructures/HashTable.h"
#include "gui/Util.h" 

class HashTableVisualize {
    private:
        HashTable table;

        HashStep step;
        int type = 0;
        
        ProgressBar progressBar;
        int stepIndex;
        int frame;
        int numFrameOfAnimation;
        
        Button createButton;
        bool isCreateChosen;
        
        Button resizeButton;
        Button randomButton;
        Button loadFileButton;
        
        InputStr inputSize;
        
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
        HashTableVisualize(Font font);
        HashTableVisualize();
        virtual ~HashTableVisualize();

        void updateStep(int step);
        void resize();
        
        void insert();
        void deleteNode();
        void search();
        void createWithRandomizedData(int n = 15, int range = 100);
        void createFromFile();
        
        int handle();
        
        void drawButtons();
        void drawTable();
        void draw();
};

#endif // HASHTABLEVISUALIZE_H