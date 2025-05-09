#ifndef AVLVISUALIZE_H
#define AVLVISUALIZE_H

#include "../datastructures/AVL.h"
#include "../gui/Util.h"

class AVLTreeVisualize {
    private:
        AVLTree tree;
        AVLStep step;

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
        AVLTreeVisualize(Font font);
        AVLTreeVisualize();
        virtual ~AVLTreeVisualize();

        void updateStep(int step);

        void insert();
        void deleteNode();
        void search();
        void createFromFile();
        void createWithRandomizedData(int n = 15, int range = 100);
        
        int handle();
        // int buttonHandle();
        
        void drawNode(AVLNode *root, int specialValue, int frame, int numFrame, Font font, bool isNotification = false);
        void drawTree();
        void drawButtons();
        void draw();
};
    

#endif // AVLVISUALIZE_HPP