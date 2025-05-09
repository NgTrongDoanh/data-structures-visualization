#include "gui/CircleButton.h"

CircleButton::CircleButton() {}

CircleButton::CircleButton(Vector2 center, float radius, const char* file)
             : center(center), radius(radius), texture(LoadTexture(file)), isHovered(false) {}

CircleButton::~CircleButton() {
    UnloadTexture(this->texture);
}

bool CircleButton::IsHovered() {
    return this->isHovered;
}

void CircleButton::changeTexture(const char* file) {
    UnloadTexture(this->texture);
    this->texture = LoadTexture(file);
}

void CircleButton::handle() {
    this->isHovered = CheckCollisionPointCircle(GetMousePosition(), this->center, this->radius);
}

void CircleButton::draw() {
    DrawCircleV(this->center, this->radius, this->isHovered ? THEME.HOVER_BUTTON : THEME.BUTTON);
    drawPicture(this->texture, {center.x - radius + 2, center.y - radius +2, 2*radius -4, 2*radius -4});
}

