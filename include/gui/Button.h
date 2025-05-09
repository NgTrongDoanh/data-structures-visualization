#ifndef BUTTON_H
#define BUTTON_H

#include "../core/General.h"

class Button {
    protected:
        Rectangle outerRect;
        std::string content;
        Vector2 contentPos;
        Color contentColor;
        Font font;
        float fontSize;
        bool isHovered;

    public:
        Button(Rectangle rect, const std::string text, float yText, Color textColor, float fontSize, Font font = FONT);
        Button();
        virtual ~Button();

        bool IsHovered();

        void draw(float radius = 15);
        int handle();
};

#endif // BUTTON_H