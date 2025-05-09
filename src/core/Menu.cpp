#include "core/Menu.h"

Menu::Menu() {
    this->avlTree = ImageButton({180, 260, 240, 160}, {190, 270, 220, 120}, AVLTREE, "AVL Tree", 390, {145, 95, 35, 255}, 20);
    this->hashTable = ImageButton({520, 260, 240, 160}, {530, 270, 220, 120}, HASHTABLE, "Hash Table", 390, {145, 95, 35, 255}, 20);
    this->Tree234 = ImageButton({860, 260, 240, 160}, {870, 270, 220, 120}, TREE234, "2-3-4 Tree", 390, {145, 95, 35, 255}, 20);
    this->maxHeap = ImageButton({180, 500, 240, 160}, {190, 510, 220, 120}, MAXHEAP, "Max Heap", 635, {145, 95, 35, 255}, 20);
    this->trie = ImageButton({520, 500, 240, 160}, {530, 510, 220, 120}, TRIE, "Trie", 635, {145, 95, 35, 255}, 20);
    this->graph = ImageButton({860, 500, 240, 160}, {870, 510, 220, 120}, GRAPH, "Graph", 635, {145, 95, 35, 255}, 20);
    this->mode = isDarkMode ? DARK_MODE : LIGHT_MODE;
}

Menu::~Menu() {
    // Placeholder for destructor
    // all buttons have their own destructor
    // mode has been deleted in the constructor
    // isDarkMode has been deleted in the constructor
}

int8_t Menu::clicked() {
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if(avlTree.IsHovered()) return 1;
        if(hashTable.IsHovered()) return 2;
        if(Tree234.IsHovered()) return 3;
        if(maxHeap.IsHovered()) return 4;
        if(trie.IsHovered()) return 5;
        if(graph.IsHovered()) return 6;
    }
    return 0;
}

bool Menu::getDarkMode() {
    return this->isDarkMode;
}

void Menu::hanlde() {
    avlTree.handle();
    hashTable.handle();
    Tree234.handle();
    maxHeap.handle();
    trie.handle();
    graph.handle();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), {1220,60}, 27.5)) {
        this->isDarkMode = !this->isDarkMode;
        THEME.change();
        this->mode = isDarkMode ? DARK_MODE : LIGHT_MODE;
    }
}

void Menu::draw() {
    DrawTextPro(FONT, "DATA STRUCTURE VISUALIZATION", {(SCREEN_WIDTH - MeasureTextEx(FONT, "DATA STRUCTURE VISUALIZATION", 45, 5).x)/2, 75.0f}, {0.0f, 0.0f}, 0, 45, 5, {255, 160, 0, 255});
    avlTree.draw();
    hashTable.draw();
    Tree234.draw();
    maxHeap.draw();
    trie.draw();
    graph.draw();
    DrawCircle(1220, 60, 27.5, CheckCollisionPointCircle(GetMousePosition(), {1220,60}, 27.5) ? THEME.HOVER_MENU : THEME.MENU_BUTTON);
    drawPicture(mode, {1200,40,40,40});
}
