#include "gui/TitleButton.h"

TitleButton::TitleButton(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font) 
    : Button(rect, text, yText, textColor, fontSize, font) {
    this->backPage = BACK_PAGE;
    this->backPageRadius = 20;
    this->backPagePos = {432,54};
}

TitleButton::TitleButton() : TitleButton({465, 34, 350, 40}, "", 0.0f, {249,208,208,255},0) {}

TitleButton::~TitleButton() {
    // Placeholder for destructor
}

void TitleButton::draw(float radius) {
    this->isHovered = CheckCollisionPointRec(GetMousePosition(), this->outerRect);
    DrawRectangleRounded(this->outerRect, radius/55, 32, this->isHovered ? Color{234,119,119,255} : Color{249,208,208,255});
    DrawTextPro(this->font, this->content.c_str(), this->contentPos, ORIGIN, 0, this->fontSize, 2, this->contentColor);
    
    this->isHovered = CheckCollisionPointCircle(GetMousePosition(), this->backPagePos, this->backPageRadius);
    DrawCircleV(this->backPagePos, this->backPageRadius, this->isHovered ? Color{234,119,119,255} : Color{249,208,208,255});
    drawPicture(this->backPage, {421, 43,22,22});
}