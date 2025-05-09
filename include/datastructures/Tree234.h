#ifndef TREE234_H
#define TREE234_H

#include "../core/General.h"

struct Key234 {
    int value;
    Vector2 start, end;
    bool highlight;

    Key234();
    Key234(int v, Vector2 st = {779.f-15, 124.f}, Vector2 des = {779.f-15, 124.f});
};

struct Node234 {
    std::vector<Key234> keys;
    std::vector<Node234*> children;
    Node234* parent;
    int width;
    Vector2 start;
    Vector2 end;
    
    Node234();
    Node234(int key, Vector2 start = {779.f, 124.f}, Vector2 end={779.f, 124.f}, Node234* parent = nullptr);

    bool isLeaf() const;
    bool isFull() const;
    int insert(int k);
    void remove(int key);
};

struct Step234 {
    Node234* root;
    std::vector<int> line;
    std::string infor;
    std::string code;
    int type;   // -1: node, 0: check, 1: insert, 2:
};

class Tree234 {
    private:
        Node234* root;
        void freeTree(Node234* &node);
        Node234* cloneTree(Node234* root, Node234* highlight=nullptr, int index=-1);
        
        std::vector<Step234> process;
        void clearProcess();
        
        void saveStep(Node234* highlight, int indexHighlight, int type, std::vector<int> lines, const std::string infor, const std::string code, bool forCreate = false);
        void freeStep(Step234 &st);
        
        Node234* split(Node234* &node);
        Node234* merge(Node234* &nodeToFix);
        int estimateWidth(Node234* root);
        void updatePos(Node234* root, bool updateStart = false, bool forCreate = false, Vector2 parentPos = {779.f, 124.f}, Vector2 delta = {0.f, 0.f});

    public:
        Tree234();
        virtual ~Tree234();

        std::vector<Step234> getProcess();
        
        void insert(int key);
        bool search(int key);
        bool remove(int key);
        void createFromFile(const char* filename);
        void createRandom(int n, int range);
        
        
        void inorderTraversal(Node234* node);
        void inorder();
        void BFT();
};

#endif  // TREE234_H
