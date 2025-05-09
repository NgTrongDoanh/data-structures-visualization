#include "gui/ProgressBar.h"

ProgressBar::ProgressBar(Font font) : curStep(0), maxStep(0), speed(1), funcID(0), font(font) {}

ProgressBar::ProgressBar() : ProgressBar(FONT) {}

ProgressBar::~ProgressBar() {
    // Placeholder for destructor
}

int ProgressBar::getCurrentStep() {
    return this->curStep;
}

int ProgressBar::getMaxStep() {
    return this->maxStep;
}

float ProgressBar::getSpeed() {
    return this->speed;
}

void ProgressBar::updateCurrentStep(int step) {
    if (step == -2) this->curStep = 0;
    else if (step == 2) this->curStep = maxStep;
    else this->curStep += step;
}

void ProgressBar::updateMaxStep(int max) {
    this->maxStep = max;
    this->curStep = 0;
}

void ProgressBar::updateSpeed(float speed) {
    this->speed = speed;
}

int ProgressBar::handle() {
    int flag = 10;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointCircle(GetMousePosition(), {33.5, 643.5}, 17.5)) {
            flag = -2;
        }
        if (CheckCollisionPointCircle(GetMousePosition(), {72.5, 643.5}, 17.5)) {
            flag = -1;
        }
        if (CheckCollisionPointCircle(GetMousePosition(), {121.77, 643.5}, 25.5)) {
            flag = 0;
        }
        if (CheckCollisionPointCircle(GetMousePosition(), {168.5, 643.5}, 17.5)) {
            flag = 1;
        }
        if (CheckCollisionPointCircle(GetMousePosition(), {207.5, 643.5}, 17.5)) {
            flag = 2;
        }
        if (CheckCollisionPointCircle(GetMousePosition(), {263.5, 610.5}, 12.5)) {
            this->speed += (this->speed < 2) ? 0.1 : 0;
            flag = 3;
        }
        if (CheckCollisionPointCircle(GetMousePosition(), {263.5, 670.5}, 12.5)) {
            this->speed -= (this->speed > 0.5) ? 0.1 : 0;
            flag = -3;
        }
    }
    if (flag != 10) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return flag;
}

void ProgressBar::draw(int type) {
    DrawCircle(33.5, 643.5, 17.5, CheckCollisionPointCircle(GetMousePosition(), {33.5, 643.5}, 17.5) ? THEME.HOVER_BUTTON : THEME.BUTTON);
    DrawCircle(72.5, 643.5, 17.5 , CheckCollisionPointCircle(GetMousePosition(), {72.5, 643.5}, 17.5) ? THEME.HOVER_BUTTON : THEME.BUTTON);
    DrawCircle(121.77, 643.5, 25.5 , CheckCollisionPointCircle(GetMousePosition(), {121.77, 643.5}, 25.5) ? THEME.HOVER_BUTTON : THEME.BUTTON);
    DrawCircle(168.5, 643.5, 17.5 , CheckCollisionPointCircle(GetMousePosition(), {168.5, 643.5}, 17.5) ? THEME.HOVER_BUTTON : THEME.BUTTON);
    DrawCircle(207.5, 643.5, 17.5 , CheckCollisionPointCircle(GetMousePosition(), {207.5, 643.5}, 17.5) ? THEME.HOVER_BUTTON : THEME.BUTTON);
    DrawCircle(263.5, 610.5, 12.5 , CheckCollisionPointCircle(GetMousePosition(), {263.5, 610.5}, 12.5) ? THEME.HOVER_BUTTON : THEME.BUTTON);
    DrawCircle(263.5, 670.5, 12.5 , CheckCollisionPointCircle(GetMousePosition(), {263.5, 670.5}, 12.5) ? THEME.HOVER_BUTTON : THEME.BUTTON);
    
    DrawTextPro(font, TextFormat("%.1fx", this->speed), {246, 631}, ORIGIN, 0.f, 20, 1, BLACK);
    
    drawPicture(DOUBLE_BACK, {19.5, 629, 28, 28});
    drawPicture(BACK, {56.75, 629, 28, 28});
    if (type == 0) drawPicture(PAUSE, {110, 629, 25, 25});
    else if (type == 1) drawPicture(PLAY, {110, 629, 25, 25});
    else drawPicture(REPLAY, {110, 629, 25, 25});
    drawPicture(NEXT, {155, 629, 28, 28});
    drawPicture(DOUBLE_NEXT, {194, 629, 28, 28});
    drawPicture(SPEED_UP, {250.5, 598, 25, 25});
    drawPicture(SPEED_DOWN, {250.5, 658, 25, 25});

    // DrawRectangleRec({4.02, 589, 297, 6}, NONHOVERED_BUTTON_LIGHT_THEME);
    DrawRectangleRec({0, 590, this->maxStep != 0 ? this->curStep*297.f/this->maxStep : 0, 4}, {249,208,208,255});
}