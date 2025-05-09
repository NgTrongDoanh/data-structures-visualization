#ifndef MAXHEAPVISUALIZE_H
#define MAXHEAPVISUALIZE_H

#include "../datastructures/MaxHeap.h" 
#include "../gui/Util.h"

class MaxHeapVisualize {
    private:
        MaxHeap heap;
        
        MaxHeapNamespace::Step animation;
        int type = 0;
        
        ProgressBar progressBar;
        int stepIndex;
        int frame;
        int numFrameOfAnimation;
        
        Button  createButton;
        bool isCreateChosen;
        Button randomButton;
        Button loadFileButton;
        
        Button pushButton;
        bool isPushChosen;
        
        Button deleteButton;
        bool isDeleteChosen;
        
        InputStr inputNumber;
        Button playButton;
        
        Button topButton;
        
        Button sizeButton;
        
        Font font;

    public:
        MaxHeapVisualize(Font font);
        MaxHeapVisualize();
        virtual ~MaxHeapVisualize();

        MaxHeapNamespace::Step getAinimation() { return this->animation;}
        void getTop();
        void getSize();
        int updateAnimation();
        
        void updateStep();
        void updateStep(int index);
        
        void createWithRandomizedData(int n, int range);
        void createFromFile();
        void push();
        void deleteNode();
        
        void drawButtons();
        int handle();
        void draw();
        int buttonHandle();
};

#endif // MAXHEAPVISUALIZE_H