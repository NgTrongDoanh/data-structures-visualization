#include "datastructures/Trie.h"

// TrieNode
TrieNode::TrieNode(char ch, Vector2 st, Vector2 des) {
    isEndStr = false;
    numOfChild = 0;
    width = 1;
    character = ch;
    start = st;
    end = des;
    for (int i = 0; i < ALPHABET_SIZE; i++) children[i] = nullptr;
}

TrieNode::TrieNode(){
    isEndStr = false;
    numOfChild = 0;
    width = 1;
    character = '\0';
    start = end = {779.f, 124.f};
    for (int i = 0; i < ALPHABET_SIZE; i++) children[i] = nullptr;
}

// Trie
Trie::Trie() {
    this->root = new TrieNode();
}

Trie::~Trie() {
    clearProcess();
    freeTrie(this->root);
    this->root = nullptr;
}

std::pair<TrieNode*, TrieNode*> Trie::cloneTrie(TrieNode* root, TrieNode* highlight) {
    if (!root) return {nullptr, nullptr};

    TrieNode* newNode = new TrieNode(root->character, root->start, root->end);
    newNode->isEndStr = root->isEndStr;
    newNode->numOfChild = root->numOfChild;

    std::pair<TrieNode*, TrieNode*> newElement = {newNode, nullptr};

    for(int i = 0; i < ALPHABET_SIZE; i++) {
        std::pair<TrieNode*, TrieNode*> tmp = cloneTrie(root->children[i], highlight);
        newElement.first->children[i] = tmp.first;
        if (tmp.second) {
            newElement.second = tmp.second;
        }
    }

    if (root == highlight) {
        newElement.second = newNode;
    }

    return newElement;
}

// Trie.cpp - Thử lại cách sửa này
void Trie::freeTrie(TrieNode* &node) {
    if (!node) return;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            freeTrie(node->children[i]); // Đệ quy giải phóng con
        }
    }

    // Sau khi tất cả con đã được giải phóng, giải phóng node hiện tại
    delete node;
    node = nullptr; // Rất quan trọng: đặt con trỏ thành nullptr sau khi delete
                   // để tránh dangling pointer và double free nếu hàm này được gọi lại
                   // với cùng một con trỏ (mặc dù với tham chiếu &node, điều này ít xảy ra hơn
                   // nhưng vẫn là thực hành tốt).
}

void Trie::saveStep(TrieNode* highlight, int type, std::vector<int> lines, const std::string infor, const std::string code, bool forCreate) {
    std::pair<TrieNode*, TrieNode*> newTrie = cloneTrie(this->root, highlight);
    
    estimateWidth(newTrie.first);
    updatePos(newTrie.first, false, forCreate, {779.f, 124.f}, {0.f, 0.f});
    this->process.push_back({newTrie.first, lines, newTrie.second, infor, code, type});
    
    estimateWidth(this->root);
    updatePos(this->root, true, false);
}

void Trie::freeStep(TrieStep &st) {
    freeTrie(st.root);
    st.line.clear();
    st.highlight = nullptr;
}

int Trie::estimateWidth(TrieNode* root) {
    if (!root) return 0;
    if (root->numOfChild == 0) {
        root->width = 1;
        return 1;
    }

    int width = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            width += estimateWidth(root->children[i]);
        }
    }
    
    root->width = width;
    return width;
}

bool Trie::isEmptyTrieNode(TrieNode* node) {
    if (node == nullptr) return true;
    if (node->isEndStr) return false;

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (node->children[i] != nullptr && !isEmptyTrieNode(node->children[i])) {
            return false;
        }
    }
    
    return true;
}

void Trie::updatePos(TrieNode* root, bool updateStart, bool forCreate, Vector2 parentPos, Vector2 delta) {
    if (!root) return;
    if (forCreate) root->start = {779.f, 124.f};
    if (updateStart && !forCreate) {
        root->start = Vector2Add(parentPos, delta);
    }
    root->end = Vector2Add(parentPos, delta);
    
    float pos = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if(!root->children[i]) continue;
        int childWidth = root->children[i]->width;
        updatePos(root->children[i], updateStart, forCreate, root->end, {50.f * (pos + float(childWidth)/2 - float(root->width)/2), 60.f});
        pos += childWidth;
    }
}

bool Trie::deleteWord(TrieNode* parent, TrieNode* node, const std::string& key, int depth) {
    if (!node) {
        saveStep(nullptr, -1, {1}, "Not Found Str", Trie_DELETE);
        return false;
    }

    // For debugging
    // printf("%c - %d\n", node->character, isEmptyTrieNode(node));

    if (depth == key.size()) {
        if (node->isEndStr){
            saveStep(node, 0, {2}, "remove str...", Trie_DELETE);
            parent->numOfChild--;
            node->isEndStr = false;
        } else {
            saveStep(node, 0, {2}, "sdhafgbhsdjjf", Trie_DELETE);
        }
        return !node->isEndStr && isEmptyTrieNode(node);
    }

    int index = key[depth] - 'a'; 
    saveStep(node, 0, {0}, "Searching Str...", Trie_DELETE);
    
    if (deleteWord(node, node->children[index], key, depth + 1)) {
        printf("1/%c - %d\n", node->children[index]->character, isEmptyTrieNode(node->children[index]));
        delete node->children[index];

        node->numOfChild--;
        node->children[index] = nullptr;
        
        saveStep(node->children[index], 0, {3,4,5,6,7}, "remove non_exist node...", Trie_DELETE);
        return !node->isEndStr && isEmptyTrieNode(node);
    }
    saveStep(nullptr, -1, {0}, TextFormat("Finish"), Trie_DELETE); 
    return false;
}

bool Trie::empty() {
    return this->root->numOfChild == 0;
}

TrieNode* Trie::getRoot() {
    return this->root;
}

std::vector<TrieStep> Trie::getProcess() {
    return this->process;
}

int Trie::estimateWidth() {
    return estimateWidth(this->root);
}

void Trie::clearProcess() {
    for (auto it = this->process.begin(); it != this->process.end(); ++it) {
        freeStep(*it);
    }

    this->process.clear();
}

void Trie::insert(std::string key) {
    clearProcess();
    
    if (!this->root) {
        this->root = new TrieNode();
        saveStep(this->root, 0, {0}, "root created", Trie_INSERT);
    }

    TrieNode* node = this->root;
    saveStep(node, 0, {0}, "set node <- root", Trie_INSERT);
    
    for (int i = 0; i < key.length(); i++) {
        saveStep(nullptr, 0, {1}, "for ch in str", Trie_INSERT);
        int index = key[i] - 'a';
        if (!node->children[index]){
            node->children[index] = new TrieNode(key[i], node->end);
            saveStep(node->children[index], 1, {2,3}, TextFormat("insert node with char %c", key[i]), Trie_INSERT);
        }
        node->numOfChild++;
        node = node->children[index];
        saveStep(node, 0, {4,5}, TextFormat("update node"), Trie_INSERT);
    }
    node->isEndStr = true;
    
    saveStep(node, 0, {6}, TextFormat("node->isEnd = true"), Trie_INSERT);
    saveStep(nullptr, -1, {0}, TextFormat("Finish"), Trie_INSERT);
}

bool Trie::search(std::string key) {
    clearProcess();
    TrieNode* node = this->root;
    saveStep(node, 0, {0}, "Searching...", Trie_SEARCH);

    for (int i = 0; i < key.length(); i++) {
        saveStep(node, 0, {1}, TextFormat("Checking %c", key[i]), Trie_SEARCH);
        int index = key[i] - 'a';
        if (!node->children[index]){
            saveStep(nullptr, -1, {2,3}, "NOT_FOUND", Trie_SEARCH);
            
            return false;
        }
        node = node->children[index];
        saveStep(node, 0, {4}, "next char", Trie_SEARCH);
    }
    
    if (node->isEndStr) {
        saveStep(node, 0, {5}, "FOUND", Trie_SEARCH);
    } else {
        saveStep(nullptr, -1, {6}, "NOT_FOUND", Trie_SEARCH);
    }
    
    return (node != nullptr && node->isEndStr);
}

void Trie::createFromFile(const char* filename) {
    clearProcess();
    freeTrie(this->root);

    this->root = new TrieNode();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string word;
    while (std::getline(file, word)) {
        if (!word.empty()) {
            insert(word);
        }
    }
    
    file.close();
    printf("DONE");
    clearProcess();
    saveStep(nullptr, -1, {}, "Creating...", "", true);
}

void Trie::createRandom(int numWords, int maxLength) {
    clearProcess();
    freeTrie(this->root);

    this->root = new TrieNode();
    srand(static_cast<unsigned int>(time(nullptr)));
    
    for (int i=0; i<numWords; i++) {
        int length = rand() % maxLength + 1;
        std::string word;
        for (int i=0; i<length; i++) {
            word += 'a' + rand() % 26;
        }
        insert(word);
    }

    clearProcess();
    saveStep(nullptr, -1, {}, "Creating...", "", true);
}
