#include "core/General.h"

Texture2D PLAY;
Texture2D PAUSE;
Texture2D REPLAY;
Texture2D NEXT;
Texture2D DOUBLE_NEXT;
Texture2D BACK;
Texture2D DOUBLE_BACK;
Texture2D SPEED_UP;
Texture2D SPEED_DOWN;
Texture2D BACK_PAGE;

Texture2D DARK_MODE;
Texture2D LIGHT_MODE;

Texture2D AVLTREE;
Texture2D HASHTABLE;
Texture2D TREE234;
Texture2D MAXHEAP;
Texture2D TRIE;
Texture2D GRAPH;

theme THEME;
Font FONT;

void initResource() {
    PLAY = LoadTexture("./assets/images/Play.png");
    PAUSE = LoadTexture("assets/images/Pause.png");
    REPLAY = LoadTexture("./assets/images/Replay.png");
    BACK = LoadTexture("./assets/images/Chevron left.png");
    DOUBLE_BACK = LoadTexture("./assets/images/Chevrons left.png");
    NEXT = LoadTexture("./assets/images/Chevron right.png");
    DOUBLE_NEXT = LoadTexture("./assets/images/Chevrons right.png");
    SPEED_UP = LoadTexture("./assets/images/Chevron up.png");
    SPEED_DOWN = LoadTexture("./assets/images/Chevron down.png");
    BACK_PAGE = LoadTexture("./assets/images/BackPage.png");
    
    DARK_MODE = LoadTexture("./assets/images/Dark.png");
    LIGHT_MODE = LoadTexture("./assets/images/Light.png");

    // Menu Button
    AVLTREE = LoadTexture("./assets/images/AVL.png");
    HASHTABLE = LoadTexture("./assets/images/HashTable.png");
    TREE234 = LoadTexture("./assets/images/Tree234.png");
    MAXHEAP = LoadTexture("./assets/images/MaxHeap.png");
    TRIE = LoadTexture("./assets/images/Trie.png");
    GRAPH = LoadTexture("./assets/images/Graph.png");

    //Color
    THEME.BACKGROUND = {229,247,255, 255};
    THEME.MENU_BUTTON = {255,255,255,255};
    THEME.HOVER_MENU = {197,252,245,255};
    THEME.BUTTON = {229,247,255, 255};
    THEME.HOVER_BUTTON = {125,215,255, 255};
    THEME.SEPERATOR = {3, 178, 255, 255};
    THEME.INFOR = {6, 155, 91, 255};
    THEME.HIGHLIGHT_TEXT = {157, 238, 238, 255};
    THEME.HIGHLIGHT_NODE_1 = {55,221,149,255};
    THEME.HIGHLIGHT_NODE_2 = Fade(BLUE,60);
    THEME.NODE = {249,208,208,255};
    THEME.LINE = {182,157,157, 255};
    THEME.SIDEBAR = {250, 254, 255, 255};
    THEME.WEIGHT = {6, 155, 91, 255};

    //FONT = LoadFont("./Font/Roboto-Regular.ttf");
    FONT = LoadFontEx("./assets/fonts/SF-Pro-Display-Regular.otf", 40, 0, 255);
}

void unloadResource() {
    UnloadTexture(PLAY);
    UnloadTexture(PAUSE);
    UnloadTexture(REPLAY);
    UnloadTexture(BACK);
    UnloadTexture(DOUBLE_BACK);
    UnloadTexture(NEXT);
    UnloadTexture(DOUBLE_NEXT);
    UnloadTexture(SPEED_UP);
    UnloadTexture(SPEED_DOWN);
    UnloadTexture(BACK_PAGE);

    UnloadTexture(AVLTREE);
    UnloadTexture(HASHTABLE);
    UnloadTexture(TREE234);
    UnloadTexture(MAXHEAP);
    UnloadTexture(TRIE);
    UnloadTexture(GRAPH);

    UnloadFont(FONT);

    UnloadTexture(DARK_MODE);
    UnloadTexture(LIGHT_MODE);
}

void theme::change() {
    if (!isDarkMode) {
        THEME.BACKGROUND = {229,247,255, 255};
        THEME.MENU_BUTTON = {255,255,255,255};
        THEME.HOVER_BUTTON = {197,252,245,255};
        THEME.BUTTON = {229,247,255, 255};
        THEME.HOVER_BUTTON = {125,215,255, 255};
        THEME.SEPERATOR = {3, 178, 255, 255};
        THEME.INFOR = {6, 155, 91, 255};
        THEME.HIGHLIGHT_TEXT = {157, 238, 238, 255};
        THEME.HIGHLIGHT_NODE_1 = {55,221,149,255};
        THEME.HIGHLIGHT_NODE_2 = Fade(BLUE,60);
        THEME.NODE = {249,208,208,255};
        THEME.LINE = {182,157,157, 255};
        THEME.SIDEBAR = {250,254,255,255};
        THEME.WEIGHT = {6, 155, 91, 255};
    }
    else {
        THEME.BACKGROUND = {45,69,81, 255};
        THEME.MENU_BUTTON = {204, 204, 204,255};
        THEME.HOVER_BUTTON = {136,184,163 ,255};
        THEME.BUTTON = {229,247,255, 255};
        THEME.HOVER_BUTTON = {125,215,255, 255};
        THEME.SEPERATOR = {3, 178, 255, 255};
        THEME.INFOR = {255, 255, 114, 255};
        THEME.HIGHLIGHT_TEXT = {180,237,230, 255};
        THEME.HIGHLIGHT_NODE_1 = {255,245,131,255};
        THEME.HIGHLIGHT_NODE_2 = {55,221,149,255};
        THEME.NODE = {182 ,234 ,255 ,255};
        THEME.LINE = {147,177,169, 255};
        THEME.SIDEBAR = {96,124,135,255};
        THEME.WEIGHT = {255, 255, 114, 255};
    }
    isDarkMode = !isDarkMode;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}


float FloatLerp(float start, float end, float amount) {
    return start + amount * (end - start);
}

void drawPicture(const char* path, Rectangle desRec, float rotation, Vector2 origin, Color color) {
    
    Texture2D texture = LoadTexture(path);
    if (texture.id == 0) return;
    Rectangle srcRect = {0.0f, 0.0f, (float) texture.width, (float) texture.height};
    DrawTexturePro(texture, srcRect, desRec, origin, rotation, color);
    UnloadTexture(texture);
}

void drawPicture(Texture2D texture, Rectangle desRec, float rotation, Vector2 origin, Color color) {
    if (texture.id == 0) return;
    Rectangle srcRect = {0.0f, 0.0f, (float) texture.width, (float) texture.height};
    DrawTexturePro(texture, srcRect, desRec, origin, rotation, color);
}

void drawRectangleWithBorder(Rectangle rec, Color colorRec, float widthBorder, Color colorBorder, int radiusBorder) {
    DrawRectangleRounded(rec, 1.0*radiusBorder/100, 64, colorRec);

    DrawRectangleRoundedLinesEx(rec, 1.0*radiusBorder/100, 64, widthBorder, colorBorder);
    // For other raylib versions 
    //DrawRectangleRoundedLines(rec, 1.0*radiusBorder/100, 64, widthBorder, colorBorder);
}

Texture2D textureFromImageWithRoundedCorner(const char* path, int radius) {
    Image src = LoadImage(path);
    Color *pixels = LoadImageColors(src);
    
    for (int y = 0; y < src.height; y++) {
        for (int x = 0; x < src.width; x++) {
            bool drawPixel = true;
            if ((x < radius && y < radius && sqrt((x - radius)*(x - radius) + (y - radius)*(y - radius)) > radius) || // Top-left corner
                (x > src.width - radius && y < radius && sqrt((x - (src.width - radius))*(x - (src.width - radius)) + (y - radius)*(y - radius)) > radius) || // Top-right corner
                (x < radius && y > src.height - radius && sqrt((x - radius)*(x - radius) + (y - (src.height - radius))*(y - (src.height - radius))) > radius) || // Bottom-left corner
                (x > src.width - radius && y > src.height - radius && sqrt((x - (src.width - radius))*(x - (src.width - radius)) + (y - (src.height - radius))*(y - (src.height - radius))) > radius)) // Bottom-right corner
            {
                drawPixel = false;
            }

            if (drawPixel) {
                pixels[y * src.width + x] = pixels[y * src.width + x];
            }
            else {
                pixels[y * src.width + x] = BLANK;
            }
        }
    }
    
    free(src.data);
    src.data = pixels;
    Texture2D texture = LoadTextureFromImage(src);
    
    UnloadImage(src);
    
    return texture;
}

void drawShrinkingText(const char* text, Vector2 position, int fontSize, float* scale, float* alpha, float shrinkRate, float fadeRate) {
    *scale -= shrinkRate;
    *alpha -= fadeRate;
    
    if (*scale < 0) *scale = 0;
    if (*alpha < 0) *alpha = 0;
    
    Vector2 textSize = MeasureTextEx(FONT, text, fontSize*(*scale), 1);
    Vector2 textPosition = {position.x - textSize.x / 2, position.y - textSize.y / 2};
    
    DrawTextEx(FONT, text, textPosition, fontSize* (*scale), 1, Fade(BLACK, *alpha));
}

// For other raylib versions
// void DrawRectangleRoundedLinesEx(Rectangle rec, float roundness, int segments, float lineThick, Color color) {
//     DrawRectangleRoundedLines(rec, roundness, segments, color);
// }
