#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include "../core/General.h"

class CircleButton {
    private:
        Vector2 center;
        float radius;
        Texture2D texture;
        bool isHovered;
    public:
        CircleButton();
        CircleButton(Vector2 center, float radius, const char* file);
        ~CircleButton();

        bool IsHovered();
        
        void changeTexture(const char* file);
        
        void handle();
        void draw();
};

#endif // CIRCLEBUTTON_H