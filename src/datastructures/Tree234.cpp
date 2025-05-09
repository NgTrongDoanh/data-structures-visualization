#include "datastructures/Tree234.h"

// Key234
Key234::Key234() {}
Key234::Key234(int v, Vector2 st, Vector2 des) : value(v), start(st), end(des), highlight(0) {}

// Node234
Node234::Node234() : parent(nullptr), keys({}), width(1), start({779.f, 124.f}), end(start) {}
Node234::Node234(int key, Vector2 start, Vector2 end, Node234* parent) : parent(parent), width(1), start(start), end(end) {
    this->keys.push_back({key});
}

bool Node234::isLeaf() const {
    return children.empty();
}

bool Node234::isFull() const {
    return keys.size() > 2;
}

int Node234::insert(int k) {
    int i = 0;
    for (; i < int(this->keys.size()); i++) {
        if (keys[i].value > k) break;
    }

    Key234 new_key;
    if (i == 0) new_key = Key234(k, keys[i].start, keys[i].end);
    else new_key = Key234(k, keys[i-1].start, keys[i-1].end);

    this->keys.insert(keys.begin() + i, new_key);

    return i;
}

void Node234::remove(int key) {
    int i = 0;
    for(; i < this->keys.size() && this->keys[i].value != key; i++);
    keys.erase(keys.begin() + i);
}

// Tree234
Tree234::Tree234() : root(nullptr) {}

Tree234::~Tree234() {
    freeTree(this->root);
    this->root = nullptr;
    clearProcess();
}

void Tree234::freeTree(Node234* &node) {
    if(!node) return;

    node->keys.clear();
    for (int i = 0; i < node->children.size(); i++) {
        freeTree(node->children[i]);
    }
    
    delete node;
    node = nullptr;
}

Node234* Tree234::cloneTree(Node234* root, Node234* highlight, int index) {
    if(!root) return nullptr;
    
    Node234* newNode = new Node234();
    for(auto key : root->keys) {
        newNode->keys.push_back(key);
        newNode->keys.back().highlight = (root == highlight && index == -1);
    }
    
    if(root == highlight && index > -1) {
        newNode->keys[index].highlight  = true;
    }
    
    newNode->parent = root->parent;
    newNode->width = root->width;
    newNode->start = root->start;
    newNode->end = root->end;
    
    for(auto child : root->children) {
        newNode->children.push_back(cloneTree(child, highlight, index));
    }

    return newNode;
}

std::vector<Step234> Tree234::getProcess() {
    return this->process;
}

void Tree234::clearProcess() {
    for (auto it = this->process.begin(); it != this->process.end(); ++it) {
        freeStep(*it);
    }
    this->process.clear();
}

void Tree234::saveStep(Node234* highlight, int indexHighlight, int type, std::vector<int> lines, const std::string infor, const std::string code, bool forCreate) {
    Node234* newRoot = cloneTree(this->root, highlight, indexHighlight);

    estimateWidth(newRoot);
    updatePos(newRoot, forCreate, forCreate, {779.f, 124.f}, {0.f, 0.f});
    this->process.push_back({newRoot, lines, infor, code, type});
    
    estimateWidth(this->root);
    updatePos(this->root, true, false);
}

void Tree234::freeStep(Step234 &st) {
    freeTree(st.root);
    st.line.clear();
}

int Tree234::estimateWidth(Node234* root) {
    if(!root) return 0;

    if(root->children.size() == 0) {
        root->width =(int) root->keys.size();
        return root->width;
    }
    
    int width = 0;
    for(int i = 0; i < root->children.size(); i++) {
        width += estimateWidth(root->children[i]);
    }
    
    root->width = width;
    return width;
}

void Tree234::updatePos(Node234* root, bool updateStart, bool forCreate, Vector2 parentPos, Vector2 delta) {
    if (!root) return;
    float width = root->keys.size() * 30;
    float pos = 0;

    if (updateStart) {
        if (forCreate) root->start = {779.f, 124.f};
        else root->start = Vector2Add(parentPos, delta);
        for(int i = 0; i < root->keys.size(); i++) {
            root->keys[i].start.x = pos + root->start.x - width/2;
            root->keys[i].start.y = root->start.y;
            pos += 30;
        }
    }
    
    pos = 0;
    root->end = Vector2Add(parentPos, delta);
    for(int i = 0; i < root->keys.size(); i++) {
        root->keys[i].end.x = pos + root->end.x - width/2;
        root->keys[i].end.y = root->end.y;
        pos += 30;
    }
    
    pos = 0;
    width = root->width*30.f + (root->children.size() - 1) * 10.f;
    for (int i = 0; i < root->children.size(); i++) {
        float childWidth = 30.f*root->children[i]->width + root->children[i]->children.size()*10.f;
        updatePos(root->children[i], updateStart, forCreate, root->end, {(pos + childWidth/2 - width/2), 100.f});
        pos += childWidth + 20;
    }
}

Node234* Tree234::split(Node234* &node) {
    Key234 middle = node->keys[1];
    
    Node234* leftNode = new Node234();
    leftNode->keys.push_back(node->keys[0]);
    Node234* rightNode = new Node234();
    rightNode->keys.push_back(node->keys[2]);
    
    if (!node->isLeaf()) {
        leftNode->children.push_back(node->children[0]);
        leftNode->children.push_back(node->children[1]);

        rightNode->children.push_back(node->children[2]);
        rightNode->children.push_back(node->children[3]);

        leftNode->children[0]->parent = leftNode;
        leftNode->children[1]->parent = leftNode;

        rightNode->children[0]->parent = rightNode;
        rightNode->children[1]->parent = rightNode;
    }
    
    if (node->parent == nullptr) {
        Node234* newRoot = new Node234();
        newRoot->keys.push_back(middle);
        newRoot->children.push_back(leftNode);
        newRoot->children.push_back(rightNode);
        delete root;
        root = newRoot;
        leftNode->parent = root;
        rightNode->parent = root;
        return root;
    }

    if(node == root) {
        return root;
    }
    
    int index = node->parent->insert(middle.value);
    
    node->parent->children[index] = leftNode;
    node->parent->children.insert(node->parent->children.begin() + index + 1, rightNode);
    leftNode->parent = node->parent;
    rightNode->parent = node->parent;
    Node234* returnNode = node->parent;
    delete node;
    node = nullptr;
    
    if (returnNode != nullptr && returnNode->isFull()) {
        returnNode = split(returnNode);

    }
    
    return returnNode;
}

Node234* Tree234::merge(Node234* &predecessor) {
    if (!predecessor) return nullptr;
    if (!predecessor->parent) {
        this->root = nullptr;
        return nullptr;
    }
    
    Node234* parent = predecessor->parent;
    int pos = 0;
    for (pos = 0; pos < int(parent->children.size()); ++pos) {
        if (parent->children[pos] == predecessor) break;
    }

    Node234* leftSibling = (pos > 0) ? parent->children[pos - 1] : nullptr;
    Node234* rightSibling = (pos < int(parent->children.size()) - 1) ? parent->children[pos + 1] : nullptr;

    if (leftSibling && leftSibling->keys.size() > 1) {
        predecessor->keys.insert(predecessor->keys.begin(), parent->keys[pos - 1]);
        parent->keys[pos - 1] = leftSibling->keys.back();
        leftSibling->keys.pop_back();

        if (!leftSibling->isLeaf()) {
            predecessor->children.insert(predecessor->children.begin(), leftSibling->children.back());
            leftSibling->children.pop_back();
        }
    } else if (rightSibling && rightSibling->keys.size() > 1) {
        // borrow from right sibling
        predecessor->keys.push_back(parent->keys[pos]);
        parent->keys[pos] = rightSibling->keys.front();
        rightSibling->keys.erase(rightSibling->keys.begin());

        if (!rightSibling->isLeaf()) {
            predecessor->children.push_back(rightSibling->children.front());
            rightSibling->children.erase(rightSibling->children.begin());
        }
    } else {
        if (leftSibling) {
            leftSibling->keys.push_back(parent->keys[pos - 1]);
            leftSibling->keys.insert(leftSibling->keys.end(), predecessor->keys.begin(), predecessor->keys.end());

            if (!predecessor->isLeaf()) {
                leftSibling->children.insert(leftSibling->children.end(), predecessor->children.begin(), predecessor->children.end());
            }
            parent->keys.erase(parent->keys.begin() + (pos - 1));
            parent->children.erase(parent->children.begin() + pos);
            delete predecessor;
            predecessor = nullptr;
        } else if (rightSibling) {
            predecessor->keys.push_back(parent->keys[pos]);
            predecessor->keys.insert(predecessor->keys.end(), rightSibling->keys.begin(), rightSibling->keys.end());

            if (!rightSibling->isLeaf()) {
                predecessor->children.insert(predecessor->children.end(), rightSibling->children.begin(), rightSibling->children.end());
            }
            parent->keys.erase(parent->keys.begin() + pos);
            parent->children.erase(parent->children.begin() + (pos + 1));
            delete rightSibling;
            rightSibling = nullptr;
        }
    }

    if (parent == this->root) {
        root = parent->children[0];
        delete parent;
        parent = nullptr;
    }
    return parent;
}

void Tree234::insert(int key) {
    clearProcess();
    if (!root) {
        root = new Node234(key);
        saveStep(root, -1, 0, {}, "insert at root...", "", false);
        return;
    }
    Node234* current = root;
    while (current) {

        saveStep(current, -1, 0, {}, "checking is_leaf()", "", false);
        if (current->isFull()) {
            saveStep(current, -1, 0, {}, "checking...", "", false);
            current = split(current);
            saveStep(nullptr, -1, 1, {}, "split...", "", false);
        }
        if(current->isLeaf()) {
            saveStep(current, -1, 0, {}, "this node is leaf, insert key", "", false);
            break;
        }
        if (key < current->keys[0].value) {
            current = current->children[0];
        } else if (current->keys.size() == 1 || (current->keys.size() > 1 && key < current->keys[1].value)) {
            current = current->children[1];
        } else {
            current = current->children[2];
        }
        saveStep(current, -1, 0, {}, "go to child...", "", false);
    }
    Node234* tmp = current;

    current->insert(key);
    saveStep(current, -1, 0, {}, "inserting...", "", false);
    saveStep(nullptr, -1, -1, {}, "finish", "", false);
}

bool Tree234::search(int key) {
    clearProcess();
    Node234* current = root;
    while (current != nullptr) {
        saveStep(current, -1, 0, {}, "checking", "", false);
        int i = 0;
        for (; i < int(current->keys.size()); i++) {
            if (key == current->keys[i].value) {
                saveStep(current, i, 0, {}, "FOUND", "", false);

                return true;
            }
            if (key < current->keys[i].value) break;
        }
        if (current->isLeaf()) {
            saveStep(nullptr, -1, -1, {}, "not found", "", false);
            return false;
        }
        current = current->children[i];
        saveStep(current, -1, 0, {}, "go to child", "", false);
    }
    saveStep(nullptr, -1, -1, {}, "not found", "", false);
    return false;
}

// There is a bug in this function, it doesn't work correctly. But I don't have time to fix it now.
// Be careful when using this function. :))
// Gud luck! <(")
bool Tree234::remove(int key) {
    clearProcess();
    if (!root) {
        saveStep(nullptr, -2, -1, {}, "empty tree", "");
        return 0;
    }

    Node234* node = root;
    int i = 0;
    while(node) {
        saveStep(node, -1, 0, {}, "Finding key", "", false);
        for(i = 0; i < node->keys.size() && node->keys[i].value < key; i++);
        if (i < node->keys.size() && node->keys[i].value == key) break;
        if (i < node->children.size()) node = node->children[i];
        else node = nullptr;
    }
    if (!node) {
        saveStep(nullptr, -1, -1, {}, "NOT FOUND", "", false);

        return 0;
    }
    saveStep(node, i, 0, {}, "FOUND, start removing", "", false);

    if (node->isLeaf()) {
        saveStep(node, i, 0, {}, "key in leaf node", "", false);
        node->remove(key);
        if(node->keys.size() == 0) {
            do {
                node = merge(node);
                saveStep(node, -1, 0, {}, "merge", "", false);
            } while (node && node->keys.size() == 0);
        }

        // For debugging
        // log_tree(this->root);
        
        saveStep(nullptr, -1, -1, {}, "finish", "", false);       
        return 1;
    }
    
    Node234* predecessor = node->children[i];
    while(!predecessor->isLeaf()) {
        predecessor = predecessor->children.back();
    }

    node->keys[i].value = predecessor->keys.back().value;

    // For debugging
    // printf("Size: %d\n", predecessor->keys.size());
    // Bug here, it doesn't work correctly
    
    predecessor->keys.pop_back();
    saveStep(node, i, 0, {}, "replace by predecessor", "", false);

    if (predecessor->keys.empty()) {
        do {
            predecessor = merge(predecessor);
        } while (predecessor && predecessor->keys.empty());
        saveStep(predecessor, -1, 0, {}, "merge", "", false);

    }

    saveStep(nullptr, -1, -1, {}, "finish", "", false);
    return 1;
}

void Tree234::createFromFile(const char* filename) {
    freeTree(this->root);
    this->root = nullptr;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    int key;
    while (file >> key) {
        insert(key);
    }

    clearProcess();
    saveStep(nullptr ,-1, -1, {}, "Creating...", "", true);
    saveStep(nullptr, -1, -1, {}, "Create succesfully", "");
    file.close();
}

void Tree234::createRandom(int n, int range) {
    freeTree(this->root);
    srand((int)time(0));

    for(int i = 0; i < n; i++) {
        insert(rand() % range);
        
    }

    clearProcess();
    saveStep(nullptr, -1, -1, {}, "Creating...", "", true);
    saveStep(nullptr, -1, -1, {}, "Create succesfully", "");
}

// For debugging
void Tree234::inorderTraversal(Node234* node) {
    if (node == nullptr) return;
    if (!node->children.empty()) inorderTraversal(node->children[0]);
    for (int i = 0; i < node->keys.size(); ++i) {
        std::cout << node->keys[i].value << " ";
        if (!node->children.empty() && i + 1 < node->children.size()) {
            inorderTraversal(node->children[i + 1]);
        }
    }
}

void Tree234::inorder() {
    inorderTraversal(root);
    std::cout << std::endl;
}

void Tree234::BFT() {
    if (!root) return;
    estimateWidth(root);
    updatePos(this->root, true, false);
    Node234* newRoot = cloneTree(this->root);
    std::queue<Node234*> q;
    q.push(newRoot);

    while (!q.empty()) {
        Node234* current = q.front();
        q.pop();
        for (Node234* child : current->children) {
            if (child != nullptr) {
                q.push(child);
            }
        }
    }
}
