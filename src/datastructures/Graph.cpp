#include "datastructures/Graph.h"

Graph::Graph() : frameCounting(0) {}

Graph::~Graph() {
    clearGraph();
}

int Graph::getNodeIndex(GraphNode* node) {
    auto it = std::find(nodes.begin(), nodes.end(), node);
    if (it != nodes.end()) {
        return (int)std::distance(nodes.begin(), it);
    }
    return -1; // Return -1 if node is not found (should not happen)
}

int Graph::findParent(std::vector<int>& parent, int node) {
    if (parent[node] != node)
        parent[node] = findParent(parent, parent[node]);
    return parent[node];
}

void Graph::unionNodes(std::vector<int>& parent, std::vector<int>& rank, int u, int v) {
    int root_u = findParent(parent, u);
    int root_v = findParent(parent, v);
    if (rank[root_u] > rank[root_v]) {
        parent[root_v] = root_u;
    } else if (rank[root_u] < rank[root_v]) {
        parent[root_u] = root_v;
    } else {
        parent[root_v] = root_u;
        rank[root_u]++;
    }
}

void Graph::clearGraph() {
    for (int i = 0; i < int(nodes.size()); i++) {
        delete nodes[i];
    }
    this->nodes.clear();
    this->frameCounting = 0;
}

void Graph::addNode(GraphNode* node) {
    nodes.push_back(node);
}

void Graph::addNode() {
    auto* node = new GraphNode();
    node->pos = {500.f + rand() % 950, 100.f + rand() % 650};
    addNode(node);
}

int Graph::addEdge(int from, int to, int weight) {
    if (from < nodes.size() && to < nodes.size() && from != to && weight != 0) {
        bool edgeExists = false;

        for (auto& edge : nodes[from]->neighbors) {
            if (edge.neighborNode == nodes[to]) {
                edgeExists = true;
                edge.weight = weight;
                break;
            }
        }
        for (auto& edge : nodes[to]->neighbors) {
            if (edge.neighborNode == nodes[from]) {
                edgeExists = true;
                edge.weight = weight;
                break;
            }
        }

        if (!edgeExists) {
            nodes[from]->neighbors.push_back({nodes[to], weight, 0});
            nodes[to]->neighbors.push_back({nodes[from], weight, 0});
            return 1;
        }
    }
    return 0;
}

void Graph::updatePositions() {
    float repulsion_const = 500000.0f;
    float attraction_const = 0.1f;

    for (auto node : nodes) {
        Vector2 force = {0, 0};

        for (auto other : nodes) {
            if (node != other) {
                float dx = node->pos.x - other->pos.x;
                float dy = node->pos.y - other->pos.y;
                float dis = sqrt(dx * dx + dy * dy);

                if (dis > 0) {
                    float repulsion = repulsion_const / (dis * dis);
                    force.x += repulsion * dx / dis;
                    force.y += repulsion * dy / dis;
                }
            }
        }

        //Spring Force
        for (auto edge : node->neighbors) {
            float dx = node->pos.x - edge.neighborNode->pos.x;
            float dy = node->pos.y - edge.neighborNode->pos.y;
            float dis = sqrt(dx * dx + dy * dy);

            if (dis > 0) {
                float attraction = attraction_const * (dis - edge.weight);
                force.x -= attraction * dx / dis;
                force.y -= attraction * dy / dis;
            }
        }

        if(this->frameCounting > 2000) continue;
        
        node->pos.x += force.x;
        node->pos.y += force.y;

        node->pos.x = std::max(std::min(1200.f, node->pos.x), 380.f);
        node->pos.y = std::max(std::min(650.f, node->pos.y), 150.f);
        frameCounting++;
    }
}

void Graph::resetMark() {
    for(auto node : nodes) {
        for(auto &edge : node->neighbors) {
            edge.highlight = false;
        }
        node->color = false;
    }
}

void Graph::randomize(int nodeCount, int edgeCount, int maxWeight) {
    clearGraph();
    for (int i = 0; i < nodeCount; ++i) {
        addNode();
    }

    srand((int)time(nullptr));
    for (int i = 0; i < edgeCount;) {
        int from = rand() % nodeCount;
        int to = rand() % nodeCount;
        if (from != to) {
            int weight = rand() % maxWeight + 1;
            i += addEdge(from, to, weight);
        }
    }
}

void Graph::initFromFile(const char* filename) {
    clearGraph();
    std::ifstream file(filename);
    int n;
    file >> n;

    for (int i = 0; i < n; ++i) {
        addNode();
    }
    
    int weight;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> weight;
            addEdge(i, j, weight);
        }
    }

    file.close();
}

int Graph::connectedComponent() {
    resetMark();
    std::vector<bool> visited(nodes.size(), false);
    int currentColor = 0;
    for (int i = 0; i < nodes.size(); ++i) {
        if (!visited[i]) {
            std::queue<int> q;
            q.push(i);
            visited[i] = true;
            nodes[i]->color = currentColor;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (auto& edge : nodes[node]->neighbors) {
                    int neighborIndex = getNodeIndex(edge.neighborNode);
                    if (!visited[neighborIndex]) {
                        q.push(neighborIndex);
                        visited[neighborIndex] = true;
                        nodes[neighborIndex]->color = currentColor;
                    }
                }
            }
            currentColor++;
        }
    }
    return currentColor;
}

void Graph::mstKruskal() {
    resetMark();
    std::vector<std::tuple<int, int, int>> edges;
    
    for (int i = 0; i < nodes.size(); ++i) {
        for (auto& edge : nodes[i]->neighbors) {
            edges.push_back({ edge.weight, i, getNodeIndex(edge.neighborNode) });
        }
    }

    std::sort(edges.begin(), edges.end());

    std::vector<int> parent(nodes.size());
    std::vector<int> rank(nodes.size(), 0);

    for (int i = 0; i < nodes.size(); ++i) {
        parent[i] = i;
    }

    for (auto& [weight, u, v] : edges) {
        if (findParent(parent, u) != findParent(parent, v)) {
            unionNodes(parent, rank, u, v);
            
            nodes[u]->color = true;
            nodes[v]->color = true;

            for (auto& edge : nodes[u]->neighbors) {
                if (getNodeIndex(edge.neighborNode) == v) {
                    edge.highlight = true;
                    break;
                }
            }
            for (auto& edge : nodes[v]->neighbors) {
                if (getNodeIndex(edge.neighborNode) == u) {
                    edge.highlight = true;
                    break;
                }
            }
            nodes[u]->color = true;
        }
    }
}

void Graph::drawGraph(Font font, std::vector<Color> color) {
    if(!color.empty()) {
        for (auto node : nodes) {
            for (auto edge : node->neighbors) {
                DrawLineEx(node->pos, edge.neighborNode->pos, 2, color[node->color]);
                Vector2 mid = { (node->pos.x + edge.neighborNode->pos.x) / 2, (node->pos.y + edge.neighborNode->pos.y) / 2 };
                DrawTextEx(font, TextFormat("%d", edge.weight), {mid.x, mid.y}, 15, 2, THEME.WEIGHT);
            }
        }
        for(int i = 0; i < nodes.size(); i++) {
            Vector2 size = MeasureTextEx(font, TextFormat("%d", i), 15, 2);
            DrawCircleV(nodes[i]->pos, 15, color[nodes[i]->color]);

            // for debugging
            // printf("Color: (%d, %d, %d, %d)\n", color[nodes[i]->color].r, color[nodes[i]->color].g, color[nodes[i]->color].b, color[nodes[i]->color].a);
            
            DrawTextEx(font, TextFormat("%d", i), {nodes[i]->pos.x - size.x/2, nodes[i]->pos.y - size.y/2}, 15, 2, BLACK);
        }
    } else {
        for (auto node : nodes) {
            for (auto edge : node->neighbors) {
                DrawLineEx(node->pos, edge.neighborNode->pos, 2, edge.highlight ? RED : THEME.LINE);
                Vector2 mid = { (node->pos.x + edge.neighborNode->pos.x) / 2, (node->pos.y + edge.neighborNode->pos.y) / 2 };
                DrawTextEx(font, TextFormat("%d", edge.weight), {mid.x, mid.y}, 15, 2, THEME.WEIGHT);
            }
        }
        for(int i = 0; i < nodes.size(); i++) {
            Vector2 size = MeasureTextEx(font, TextFormat("%d", i), 15, 2);
            DrawCircleV(nodes[i]->pos, 15, nodes[i]->color ? RED : THEME.NODE);
            DrawTextEx(font, TextFormat("%d", i), {nodes[i]->pos.x - size.x/2, nodes[i]->pos.y - size.y/2}, 15, 2, BLACK);
        }
    }
}
