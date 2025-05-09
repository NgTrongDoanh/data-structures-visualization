#ifndef TITLEBUTTON_H
#define TITLEBUTTON_H

#include "../core/General.h"
#include "Button.h"

class TitleButton : public Button {
    protected:
        Vector2 backPagePos;
        float backPageRadius;
        Texture2D backPage;
    public:
        TitleButton(Rectangle rect, const std::string text, float ytext, Color textColor, float fontSize, Font font = FONT);
        TitleButton();
        virtual ~TitleButton();

        void draw(float radius = 50);
};

#endif // TITLEBUTTON_H