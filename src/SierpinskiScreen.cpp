#include "SierpinskiScreen.h"
#include <cstdio>
using namespace std;

SierpinskiScreen::SierpinskiScreen(SDL_Window *window, SDL_Renderer *renderer) : Screen(window, renderer)
{
    puts("Created SierpinskiScreen");
}

SierpinskiScreen::~SierpinskiScreen()
{
    //dtor
}

bool SierpinskiScreen::iteration(float sx, float sy, float ex, float ey, int it) {
    if (triangleCount > 0) {
        if (it > 0) {
            iteration((3*sx+ex)/4, sy, (sx+3*ex)/4, (sy+ey)/2, it-1);
            iteration(sx, (sy+ey)/2, (sx+ex)/2, ey, it-1);
            iteration((sx+ex)/2, (sy+ey)/2, ex, ey, it-1);
        }
    }

    if(it==0 && triangleCount > 0) {
        triangleCount--;

        SDL_Point points[4] = {
            {(sx+ex)/2 , sy},
            {sx, ey}, // +1 wegen komischen Rechenfehler
            {ex, ey}
        };
        points[3] = points[0];

        SDL_RenderDrawLines(renderer, points, 4);
        return false;
    } else {
        return false;
    }
}

void SierpinskiScreen::onRender() {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    /*SDL_Point outer[4] = {
        {width/2, 20},
        {20, height-20},
        {width-20, height-20}
    };
    outer[3] = outer[0];
    SDL_RenderDrawLines(renderer, outer, 4);*/

    triangleCount = maxTriangleCount;

    iteration(20, 20, width-20, height-20, 8);

    SDL_RenderPresent(renderer);
};

void SierpinskiScreen::onTick() {
    Screen::onTick();
    if (speed) {
        maxTriangleCount += 6;
    } else {
        maxTriangleCount ++;
    }
}

bool SierpinskiScreen::onEvent(SDL_Event *event) {
    switch(event->type) {
    case SDL_KEYDOWN:
        if(event->key.keysym.sym == SDLK_SPACE) {
            speed = true;
            return true;
        } else {
            return false;
        }
    case SDL_KEYUP:
        if(event->key.keysym.sym == SDLK_SPACE) {
            speed = false;
            return true;
        } else {
            return false;
        }
    default:
        return false;
    }
};
