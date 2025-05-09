#include "gui/Button.h"

Button::Button() : Button({0,0,0,0}, "", 0.0f, BLUE, 0) {}

Button::Button(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font) 
            : outerRect(rect), content(text), font(font), fontSize(fontSize), contentColor(textColor) {
    Vector2 textSize = MeasureTextEx(this->font, text.c_str(), this->fontSize,2);
    this->contentPos = {this->outerRect.x + (this->outerRect.width-textSize.x)/2, (yText == -1) ? (rect.y + (rect.height - textSize.y)/2) : yText};
    this->isHovered = false;
}

Button::~Button() {
    // Placeholder for destructor 
}

bool Button::IsHovered() {
    return this->isHovered;
}

void Button::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? THEME.HOVER_BUTTON : THEME.BUTTON);
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, ORIGIN, 0, this->fontSize, 2, this->contentColor);
}

int Button::handle() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && this->isHovered) {
        this->isHovered = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 1;
    }
    return 0;
}