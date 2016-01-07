#ifndef SIERPINSKISCREEN_H
#define SIERPINSKISCREEN_H

#include "Screen.h"


class SierpinskiScreen : public Screen
{
    public:
        SierpinskiScreen(SDL_Window *window, SDL_Renderer *renderer);
        virtual ~SierpinskiScreen();

        virtual void onRender();
        virtual bool onEvent(SDL_Event *event);
        virtual void onTick();
    protected:
    private:
        bool iteration(float sx, float sy, float ex, float ey, int it);
        int triangleCount = 0;
        int maxTriangleCount = 0;
        bool speed = false;
};

#endif // SIERPINSKISCREEN_H
