#ifndef SCREEN_H
#define SCREEN_H
#include <SDL2/SDL.h>

class Screen
{
    public:
        Screen(SDL_Window *window, SDL_Renderer *renderer);
        virtual ~Screen();
        virtual void onRender() = 0;
        virtual bool onEvent(SDL_Event *event) = 0;
        virtual void onTick() {
            ticks++;
        }
        virtual bool continousRender() {return true;}
    protected:
        SDL_Window *window;
        SDL_Renderer *renderer;
        long ticks = 0;
    private:
};

#endif // SCREEN_H
