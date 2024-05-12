#include "../include/game.hpp"
#include "../include/player.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool Game::RUNNING = true;


void renderCross1(SDL_Surface *screenSurface, int x, int y, int w, Uint32 color) {
    SDL_Rect rect = {x, y - w / 2, 1, w};
    SDL_FillRect(screenSurface, &rect, color);

    rect = {x - w / 2, y, w, 1};
    SDL_FillRect(screenSurface, &rect, color);
}

void renderCross(SDL_Surface *screenSurface , int x, int y, float x1, float x2) {
    renderCross1(screenSurface, x, y, 20, SDL_MapRGB(screenSurface->format, 0x99, 0x99, 0x99));
    renderCross1(screenSurface, x + x1 * SCREEN_WIDTH * 0.2f, y + x2 * SCREEN_HEIGHT * 0.2f,
            10, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xAA));
}

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("hello_sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }
    screenSurface = SDL_GetWindowSurface(window);
    
    for(int i=0; i<2;i++){
        players.push_back(new Player);
        players[i]->controller->registerWithEventHandler(eventHandler);
    }
    RUNNING = true;
}

void Game::run()
{

    // Player *player = new Player;
    // player->controller->registerWithEventHandler(eventHandler);
    // eventHandler.print_map("test 1 : ", eventHandler._registeredCallbacks);
    // Player *player2 = new Player;
    // player2->test = 6;
    // player2->controller->registerWithEventHandler(eventHandler);
    // eventHandler.print_map("test 2 : ", eventHandler._registeredCallbacks);
    // delete player;
    // eventHandler.print_map("test 2 : ", eventHandler._registeredCallbacks);
    // std::cerr << player->test << std::endl;
    while (RUNNING)
    {
        SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0x33, 0x33, 0x33));
        eventHandler.handleEvents();
        update();
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::update(){
    players[0]->controller->getMove();
    renderCross(screenSurface, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, players[0]->x, players[0]->y);
    players[1]->controller->getMove();
    renderCross(screenSurface, 3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, players[1]->x, players[1]->y);
}

void Game::render(){
    return;
}

