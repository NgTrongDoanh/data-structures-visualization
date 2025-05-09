#ifndef AVL_H
#define AVL_H

#include "../core/General.h"

const std::string AVL_INSERT(
    "Insert v\n"
    "Check balance factor (bf):\n"
    "   LL: rt_Right\n"
    "   LR: left.rt_Left, rt_Right\n"
    "   RR: rt_Lef\n"
    "   RL: right.rt_Right, rt_Left\n"
);

const std::string AVL_DELETE(
    "Delete v\n"
    "Check balance factor (bf):\n"
    "   LL: rt_Right\n"
    "   LR: left.rt_Left, rt_Right\n"
    "   RR: rt_Lef\n"
    "   RL: right.rt_Right, rt_Left\n"
);

const std::string AVL_SEARCH(
    "if this == null\n"
    "   return NOT_FOUND\n"
    "if this.data == value\n"
    "   return FOUND\n"
    "if value < this.data\n"
    "   searchLeft\n"
    "if value > this.data\n"
    "   searchRight\n"
);

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    Vector2 start;
    Vector2 end;
    
    AVLNode(int key, Vector2 begin, Vector2 dest, int height=1) : key(key), left(nullptr), right(nullptr), height(height), start(begin), end(dest) {}
};

struct AVLStep {
    AVLNode* root;
    std::vector<int> line;
    int highlight;
    std::string infor;
    std::string code;
    int type;
    
};

class AVLTree {
    private:
        AVLNode* root;
        
        std::vector<AVLStep> process;
        
        AVLNode* cloneTree(AVLNode* node);
        void freeTree(AVLNode* &root);
        
        void clearProcess();
        
        void saveStep(int speacialValue, int type, std::vector<int> line, const std::string infor, const std::string code, bool forCreate = false);
        void freeStep(AVLStep &step);
        void updateStandardPos(AVLNode* root, Vector2 parentPos = {779, 124}, Vector2 delta = {0.0f, 0.0f});
        void updateTargetPos(AVLNode* root, Vector2 parentPos = {779, 124}, Vector2 delta = {0.0f, 0.0f}, bool forCreate = false);
        
        int height (AVLNode* node);
        void updateHeight(AVLNode* node);
        int updateAllHeight(AVLNode* node);
        
        int getBalance(AVLNode* node) {
            return node ? height(node->left) - height(node->right) : 0;
        }
        AVLNode* rightRotate(AVLNode* y);
        AVLNode* leftRotate(AVLNode* x);
        std::pair<AVLNode*, int> balance(AVLNode* node, const std::string code);

    public:
        AVLTree();
        virtual ~AVLTree();

        std::vector<AVLStep> getProcess() {return this->process;}

        void insert(int key, Vector2 start = {779, 124}, Vector2 end = {779, 124});
        void deleteNode(int key);
        bool search(int key);
        void createFromFile (const char* filename);
        void createWithRandomizedData(int n, int range);
        void printInOrder();
};

#endif  // AVL_H
