#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "../core/General.h"

class ProgressBar {
    private:
        int curStep;
        int maxStep;
        float speed;
        
        int funcID;
        Font font;
    public:
        ProgressBar(Font font);
        ProgressBar();
        ~ProgressBar();

        int getCurrentStep();
        int getMaxStep();
        float getSpeed();
        
        void updateCurrentStep(int step);
        void updateMaxStep(int max);
        void updateSpeed(float speed);
        
        int handle();
        void draw(int type);
};

#endif // PROGRESSBAR_H