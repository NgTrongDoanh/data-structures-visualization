#include "gui/InputStr.h"

InputStr::InputStr(float x, float y, float width, float height, std::string placeHolder, float fontSize, Font font)
                : textBox{x,y,width,height}, text(""), placeHolder(placeHolder), mouseOnText(false), framesCounter(0), fontSize(fontSize), font(font) {}


InputStr::InputStr() {}

InputStr::~InputStr() {
    // Placeholder for destructor
}

std::string InputStr::getText() {
    return this->text;
}

void InputStr::resetText() {
    srand((int)time(0));
    this->changePlaceHolder(TextFormat("%d", rand() % 100));
}

void InputStr::changePlaceHolder(const std::string& newPlaceHolder) {
    this->placeHolder = newPlaceHolder;
}

void InputStr::handle() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        mouseOnText = CheckCollisionPointRec(GetMousePosition(), this->textBox);
    }

    if (this->mouseOnText) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125 && this->text.length() < 30) {
                this->text += (char)key;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!this->text.empty()) {
                this->text.pop_back();
            }
        }
    }

    this->framesCounter++;
}

void InputStr::draw() {
    DrawRectangleRounded(this->textBox, 0.2f, 64, {229,247,255,255});
    DrawRectangleRoundedLinesEx(this->textBox, 0.2f, 64, 3, mouseOnText ? BLACK : GRAY);

    Vector2 size = MeasureTextEx(this->font, this->text.c_str(), this->fontSize, 2);
    size.y = MeasureTextEx(this->font, "|", this->fontSize, 2).y;
    
    if (this->text.empty() && !this->mouseOnText) {
        DrawTextEx(this->font, this->placeHolder.c_str(), {this->textBox.x + 16 , this->textBox.y + float(this->textBox.height - size.y)/2}, this->fontSize, 2, BLACK);
    } else {
        DrawTextEx(this->font, this->text.c_str(), {this->textBox.x + 16 , this->textBox.y + float(this->textBox.height - size.y)/2}, this->fontSize, 2, BLACK);
    }
    
    if (this->mouseOnText) {
        if (this->text.length() < 30) {
            if (((this->framesCounter/20) % 2) == 0) {
                DrawTextEx(this->font, "|", {this->textBox.x + 16 + size.x, this->textBox.y + float(this->textBox.height - size.y)/2}, this->fontSize, 2, BLACK);
            }
        }
    }
}