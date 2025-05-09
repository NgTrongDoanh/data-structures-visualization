#include "gui/ImageButton.h"

ImageButton::ImageButton(Rectangle outerRect, Rectangle innerRect, Texture2D texture, const std::string text, float yText, Color textColor, float fontSize, Font font) 
    : Button(outerRect, text, yText, textColor, fontSize, font), innerRect(innerRect) {
    this->texture = texture;
}

ImageButton::ImageButton() : Button() {}

ImageButton::~ImageButton() {
    // Texture has been deleted in the unloadResource function (Application.cpp)
}

void ImageButton::draw(float radius) {
    Button::draw(radius);
    drawPicture(this->texture, this->innerRect);
}
