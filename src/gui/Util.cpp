#include "gui/Util.h"

void DrawTextInRect(Font font, const char *text, Rectangle rect, int fontSize, Color textColor) {
    int maxWidth = (int)rect.width;
    int textHeight = fontSize;
    char lineBuffer[1024];
    const char *currentChar = text;
    int lineCount = 0;

    while (currentChar && *currentChar) {
        int lineWidth = 0;
        int charsToFit = 0;
        while (*currentChar && (lineWidth < maxWidth)) {
            lineBuffer[charsToFit++] = *currentChar;
            lineBuffer[charsToFit] = '\0'; 

            lineWidth = MeasureTextEx(font, lineBuffer, fontSize, 2).x;
            currentChar++;

            if (lineWidth > maxWidth) {
                currentChar--;
                lineBuffer[--charsToFit] = '\0';
                break;
            }
        }
        Vector2 textPosition;
        textPosition.x = rect.x;
        textPosition.y = rect.y + lineCount * textHeight;
        DrawTextEx(font, lineBuffer, textPosition, fontSize, 2, textColor);

        lineCount++;

        while (*currentChar && (*currentChar == ' ' || *currentChar == '\n')) {
            currentChar++;
        }
        if ((rect.y + lineCount * textHeight) >= (rect.y + rect.height)) break;
    }
}

void drawCode(std::string code, size_t n ,std::vector<int> highlight, Font font) {
    float lineHeight = (float)CODE_SIZE + 2;
    Vector2 CodeOffset = {20, 130};
    
    for (size_t i = 0; i<n; i++) {
        bool flag = false;
        for (auto line : highlight) {
            if (i == line) {
                flag = true;
                break;
            }
        }
        Color color = flag ? THEME.HIGHLIGHT_TEXT : Color {0,0,0,0};
        DrawRectangle(CodeOffset.x, CodeOffset.y + i * lineHeight, 260, lineHeight, color);
    }
    DrawTextEx(font, code.c_str(), {CodeOffset.x, CodeOffset.y + 1}, CODE_SIZE, 2, BLACK);
}

void drawInfor(const std::string infor, Font font) {
    DrawTextInRect(font, infor.c_str(), {20, 335, 260, 65}, CODE_SIZE, THEME.INFOR);
}

void drawSideBar(int type, std::string code, std::vector<int> lines, std::string infor, ProgressBar bar, Font font) {
    DrawRectangleRounded({0, 110, 297, 584}, 0.10f, 32, THEME.SIDEBAR);
    DrawLineEx({0, 326}, {297, 326}, 1.3, THEME.SEPERATOR);
    DrawLineEx({0, 408}, {297, 408}, 1.3, THEME.SEPERATOR);
    DrawLineEx({126, 408}, {126, 592}, 1.3, THEME.SEPERATOR);
    DrawLineEx({0, 592}, {297, 592}, 1.3, THEME.SEPERATOR);
    drawCode(code, 8, lines, font);
    drawInfor(infor, font);
    bar.draw(type);
}