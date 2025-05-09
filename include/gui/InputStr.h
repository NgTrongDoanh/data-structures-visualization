#ifndef INPUTSTR_H
#define INPUTSTR_H

#include "../core/General.h"

class InputStr {
    private:
        Rectangle textBox;
        std::string text;
        std::string placeHolder;
        bool mouseOnText;
        int framesCounter;
        float fontSize;
        Font font;
        
    public:
        InputStr();
        InputStr(float x, float y, float width, float height, std::string placeHolder, float fontSize, Font font);
        virtual ~InputStr();

        std::string getText();

        void resetText();
        void changePlaceHolder(const std::string& newPlaceHolder);

        void handle();
        void draw();
};

#endif // INPUTSTR_H