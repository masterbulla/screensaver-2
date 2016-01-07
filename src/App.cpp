#include "App.h"

App::App()
{
    init();

    screen = new SierpinskiScreen(window, renderer);

    eventLoop();

}

App::~App()
{
    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    if (window != nullptr) SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::fatal(const char *title, const char *message) {
    fprintf(stderr, "%s error: %s\n", title, message);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
    exit(1);
}

void App::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) fatal("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow("Screensaver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) fatal("Window", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) fatal("Renderer", SDL_GetError());
}

void App::eventLoop() {
    SDL_Event event;
    screen->onRender();
    while (running) {

        //Wait for Events before render?
        if (!screen->continousRender()) {
            SDL_WaitEvent(&event);
            onEvent(&event);
        }

        while (SDL_PollEvent(&event)) onEvent(&event);

        screen->onTick();
        screen->onRender();

    }
}

void App::onEvent(SDL_Event *event) {
    switch (event->type) {
    case SDL_QUIT:
        running = false;
        break;
    case SDL_KEYDOWN:
        if (event->key.keysym.sym == SDLK_r) {
            delete screen;
            screen = new SierpinskiScreen(window, renderer);
        }
        break;
    }
    screen->onEvent(event);
}
