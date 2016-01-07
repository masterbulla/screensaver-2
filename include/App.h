#ifndef APP_H
#define APP_H
#include <SDL2/SDL.h>

#include "SierpinskiScreen.h"

class App
{
    public:
        App();
        virtual ~App();
    protected:
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool running = true;

        void fatal(const char *title, const char *msg);
        void init();
        void eventLoop();
        void onEvent(SDL_Event *event);

        Screen *screen;
    private:
};

#endif // APP_H
