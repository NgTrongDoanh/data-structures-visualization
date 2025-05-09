#ifndef GRAPH_H
#define GRAPH_H

#include "../core/General.h"

struct GraphNode {
    struct Edge {
        GraphNode* neighborNode;
        int weight;
        bool highlight = 0;
    };

    std::vector<Edge> neighbors;
    Vector2 pos;
    int color = 0;
};

class Graph {
    private:
        std::vector<GraphNode*> nodes;
        int frameCounting = 0;
        
        int getNodeIndex(GraphNode* node);
        int findParent(std::vector<int>& parent, int node);
        
        void unionNodes(std::vector<int>& parent, std::vector<int>& rank, int u, int v);

    public:
        Graph();
        virtual ~Graph();
        void clearGraph();

        void addNode(GraphNode* node);
        void addNode();
        int addEdge(int from, int to, int weight);

        void updatePositions();
        void resetMark();
        
        void randomize(int nodeCount, int maxX, int maxY);
        void initFromFile(const char* filename);
        int connectedComponent();
        void mstKruskal();
        
        void drawGraph(Font font, std::vector<Color> color={});
};

#endif // GRAPH_H
