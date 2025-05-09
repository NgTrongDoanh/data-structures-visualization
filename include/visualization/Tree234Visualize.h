#ifndef TREE234VISUALIZE_H
#define TREE234VISUALIZE_H

#include "datastructures/Tree234.h" 
#include "gui/Util.h" 

class Tree234Visualize {
    private:
        Tree234 tree;
        Step234 step;
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
        Tree234Visualize(Font font);
        Tree234Visualize();
        virtual ~Tree234Visualize();
        
        void updateStep(int index);

        void createWithRandomizedData(int n = 15, int range = 100);
        void createFromFile();
        void insert();
        void deleteNode();
        void search();
        
        int handle();
        
        void drawButtons();
        void drawNode(Node234 *root, int frame, int num_frame, Font font, bool is_notification = false);
        void drawTree();
        void draw();
};

#endif // TREE234VISUALIZE_H