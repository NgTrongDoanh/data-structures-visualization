#include "core/Application.h"

Application::Application() : tab(0), theme(THEME.BACKGROUND) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Data Visualized");
    initResource();
    SetTextureFilter(FONT.texture, TEXTURE_FILTER_POINT);
    SetTargetFPS(FPS);
}

Application::~Application() {
    unloadResource();
    CloseWindow();
}

void Application::run() {
    while (!WindowShouldClose() && this->tab != -1) {
        switch (this->tab) {
            case 0:
                this->tab = menu();
                break;
            case 1:
                this->tab = avlTree();
                break;
            case 2:
                this->tab = hashTable();
                break;
            case 3:
                this->tab = Tree234();
                break;
            case 4:
                this->tab = maxHeap();
                break;
            case 5:
                this->tab = trie();
                break;
            case 6:
                this->tab = graph();
                break;
        
            default:
                this->tab = -1;
                break;
        }
        
    }
    CloseWindow();
}

int Application::menu() {
    Menu menu;
    int8_t flag = -1;
    do {
        menu.hanlde();
        BeginDrawing();
            ClearBackground(THEME.BACKGROUND);
            menu.draw();
            flag = menu.clicked();
        EndDrawing();
    } while (!WindowShouldClose() && !flag);
    return flag;
}

int Application::maxHeap() {
    MaxHeapVisualize maxHeap(FONT);
    int flag = 0;
    TitleButton tittle = TitleButton({465, 34, 350, 40}, "Max Heap", -1, BLACK, 20);
    while(!WindowShouldClose()) {
        if (tittle.handle() == 1) {
            return 0;
        }
        BeginDrawing();
        ClearBackground(THEME.BACKGROUND);
        maxHeap.draw();
        tittle.draw();
        EndDrawing();
        if (!flag) flag = maxHeap.handle();
        else flag /=2;
    }
    return -1;
}

int Application::avlTree() {
    
    AVLTreeVisualize avlTree(FONT);
    TitleButton tittle = TitleButton({465, 34, 350, 40}, "AVL Tree", -1, BLACK, 20);
    int flag = 0;
    while(!WindowShouldClose()) {
        if (tittle.handle() == 1) return 0;
        BeginDrawing();
        ClearBackground(THEME.BACKGROUND);
        avlTree.draw();
        tittle.draw();
        EndDrawing();
        if (!flag) flag = avlTree.handle();
        else flag /=2;
    }
    return -1;
}

int Application::Tree234() {
    
    Tree234Visualize Tree234(FONT);
    TitleButton tittle = TitleButton({465, 34, 350, 40}, "2-3-4 Tree", -1, BLACK, 20);
    int flag = 0;
    while(!WindowShouldClose()) {
        if (tittle.handle() == 1) return 0;
        BeginDrawing();
        ClearBackground(THEME.BACKGROUND);
        Tree234.draw();
        tittle.draw();
        EndDrawing();
        if (!flag) flag = Tree234.handle();
        else flag /=2;
    }
    return -1;
}

int Application::trie() {
    
    TrieVisualize trie(FONT);
    TitleButton tittle = TitleButton({465, 34, 350, 40}, "Trie", -1, BLACK, 20);
    int flag = 0;
    while(!WindowShouldClose()) {
        if (tittle.handle() == 1) return 0;
        BeginDrawing();
        ClearBackground(THEME.BACKGROUND);
        trie.draw();
        tittle.draw();
        EndDrawing();
        if (!flag) flag = trie.handle();
        else flag /=2;
    }
    return -1;
}

int Application::graph() {
    
    GraphVisualize graph(FONT);
    TitleButton tittle = TitleButton({465, 34, 350, 40}, "Graph", -1, BLACK, 20);
    int flag = 0;
    while(!WindowShouldClose()) {
        if (tittle.handle() == 1) return 0;
        BeginDrawing();
        ClearBackground(THEME.BACKGROUND);
        graph.draw();
        tittle.draw();
        EndDrawing();
        if (!flag) flag = graph.handle();
        else flag /=2;
    }
    return -1;
}

int Application::hashTable() {
    
    HashTableVisualize hashTable(FONT);
    TitleButton tittle = TitleButton({465, 34, 350, 40}, "HashTable - Linear Probing", -1, BLACK, 20);
    int flag = 0;
    while(!WindowShouldClose()) {
        if (tittle.handle() == 1) return 0;
        BeginDrawing();
        ClearBackground(THEME.BACKGROUND);
        hashTable.draw();
        tittle.draw();
        EndDrawing();
        if (!flag) flag = hashTable.handle();
        else flag /=2;
    }
    return -1;
}
