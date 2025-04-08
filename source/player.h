#pragma once

#include <SDL2/SDL.h>
#include <switch.h>

class Player {
public:
    Player(SDL_Renderer* renderer ,int x, int y);
    ~Player(); // Destructor

    void handleInput(const u64 kHeld);
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect rect;      // Doelpositie op scherm
    SDL_Rect srcRect;   // Bronpositie uit de spitesheet
    int speed;

    SDL_Texture* texture;
    int frame;          // Huidige frame in de animatie
    int frameCounter;   // Voor de animatievetraging
    int frameCount;     // Aantal frames in de spritesheet

    bool isIdleAnimating;
    bool isGettingUp;
    int idleFrameStart;
    Uint32 lastInputTime;
};