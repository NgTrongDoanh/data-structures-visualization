#ifndef UTIL_H
#define UTIL_H

#include "../core/General.h"
#include "Button.h"
#include "CircleButton.h"
#include "ImageButton.h"
#include "TitleButton.h"
#include "InputStr.h"
#include "ProgressBar.h"


void DrawTextInRect(Font font, const char *text, Rectangle rect, int fontSize, Color textColor);
void drawCode(std::string code, size_t n ,std::vector<int> highlight, Font font);
void drawInfor(std::string infor, Font font = FONT);
void drawSideBar(int type, std::string code, std::vector<int> lines, std::string infor, ProgressBar bar, Font font = FONT);

#endif // UTIL_H