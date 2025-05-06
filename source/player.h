#pragma once

#include "weapon.h"
#include <vector>

#include <SDL2/SDL.h>
#include <switch.h>

class Player {
public:
    Player(SDL_Renderer* renderer ,int x, int y);
    ~Player(); // Destructor

    void handleInput(const u64 kHeld, const u64 kDown);
    void update();
    void render(SDL_Renderer* renderer);

    void switchWeapon(); // Toevoegen aan interface
    void unlockWeapon(WeaponType type); // Wapens vrijspelen

    Weapon* getCurrentWeapon() const;

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

    SDL_Renderer* renderer;
    std::vector<Weapon*> weapons;
    int currentWeaponIndex;
};