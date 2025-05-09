#ifndef TRIE_H
#define TRIE_H

#include "../core/General.h"

const std::string Trie_INSERT(
    "cur = root\n"
    "for (char c : str)\n"
    "   if cur.child[c] == null\n"
    "       cur.child[c] = new Node(c)\n"
    "       cur.numOfChild++\n"
    "   cur = cur.child[c]\n"
    "cur.isEndStr = true\n"
);

const std::string Trie_DELETE(
    "cur = search(str)\n"
    "if (cur = nullptr) return;\n"
    "cur.isEndStr = false\n"
    "for (char c : rev(str))\n"
    "   cur.numOfChild--\n"
    "   cur = cur.parent\n"
    "   if cur.child[c].numOfChild == 0\n"
    "       delete cur.child[c]"
);

const std::string Trie_SEARCH(
    "cur = root\n"
    "for (char c : str)\n"
    "   if cur.child[c] == null\n"
    "       return NOT_FOUND\n"
    "   cur = cur.child[c]\n"
    "if cur.isEndStr return FOUND\n"
    "else return NOT_FOUND\n"
);

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    char character;
    bool isEndStr;
    int numOfChild;
    Vector2 start;
    Vector2 end;
    int width;

    TrieNode(char ch, Vector2 st = {779.f, 124.f}, Vector2 des = {779.f, 124.f});
    TrieNode();
};

struct TrieStep {
    TrieNode* root;
    std::vector<int> line;
    TrieNode* highlight;
    std::string infor;
    std::string code;
    int type;   // -1: node, 0: check, 1: insert, 2:
};

class Trie {
    private:
        TrieNode* root;
        std::pair<TrieNode*, TrieNode*> cloneTrie(TrieNode* root, TrieNode* highlight = nullptr); //first: root, second: highlight
        void freeTrie(TrieNode* &node);

        std::vector<TrieStep> process;
        
        void saveStep(TrieNode* highlight, int type, std::vector<int> lines, const std::string infor, const std::string code, bool forCreate = false);
        void freeStep(TrieStep &step);
        
        int estimateWidth(TrieNode* root);
        bool isEmptyTrieNode(TrieNode* node);
        
        void updatePos(TrieNode* root, bool updateStart = true, bool forCreate = false, Vector2 parentPos = {779.f, 124.f}, Vector2 delta = {0.f, 0.f});
        bool deleteWord(TrieNode* parent, TrieNode* node, const std::string& key, int depth = 0);

    public:
        Trie();
        virtual ~Trie();

        bool empty();
        TrieNode* getRoot();
        std::vector<TrieStep> getProcess();
        int estimateWidth();
        void clearProcess();
        
        void insert(std::string key);
        void createFromFile(const char* filename);
        void createRandom(int numWords, int maxLength);
        void deleteStr(const std::string key) {clearProcess(); deleteWord(nullptr, this->root, key, 0);}
        bool search(std::string key);
};

#endif // TRIE_H
