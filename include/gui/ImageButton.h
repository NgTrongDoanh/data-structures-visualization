#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include "../core/General.h"
#include "Button.h"

class ImageButton : public Button {
    protected:
        Rectangle innerRect;
        Texture2D texture;
    public:
        ImageButton(Rectangle outerRect, Rectangle innerRect, Texture2D texture, const std::string text, float yText, Color textColor, float fontSize, Font font=FONT);
        ImageButton();
        ~ImageButton();

        void draw(float radius = 15);
};

#endif // IMAGEBUTTON_H