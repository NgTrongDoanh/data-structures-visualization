#ifndef GRAPHVISUALIZE_H
#define GRAPHVISUALIZE_H

#include "datastructures/Graph.h" 
#include "gui/Util.h" 

class GraphVisualize {
    private:
        Graph graph;
        int numComponent;
        
        std::vector<Color> colorComponent;
        
        ProgressBar progressBar;
        std::string infor;
        
        Button createButton;
        InputStr inputNodes;
        InputStr inputEdges;
        
        Button randomButton;
        Button loadFileButton;
        bool isCreateChosen;
        
        Button connectedComponentButton;
        Button mstKruskalButton;
        
        Font font;
        
        std::vector<Color> generateRandomColors(int n);
        
    public:
        GraphVisualize(Font font = FONT);
        virtual ~GraphVisualize();

        void randomize();
        int loadFile();
        void connectedComponent();
        void mstKruskal();

        int handle();
        
        void drawGraph();
        void drawButton();
        void draw();
};

#endif // GRAPHVISUALIZE_H