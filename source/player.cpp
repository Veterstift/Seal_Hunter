#include "player.h"
#include <switch.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define FRAME_WIDTH 20
#define FRAME_HEIGHT 20
#define ANIMATION_DELAY 10

// CONSTRUCTOR //
Player::Player(SDL_Renderer* renderer ,int x, int y) {
    rect.x = x;
    rect.y = y;
    rect.w = FRAME_WIDTH;
    rect.h = FRAME_HEIGHT;

    speed = 1;
    frame = 0;
    frameCounter = 0;
    frameCount = 3;
    isIdleAnimating = false;
    isGettingUp = false;
    idleFrameStart = 0;
    lastInputTime = SDL_GetTicks();

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = FRAME_WIDTH;
    srcRect.h = FRAME_HEIGHT;

    SDL_Surface* surface = SDL_LoadBMP("romfs:/sprites/player/blue/blue_spritesheet.bmp");
    if (!surface) {
        printf("Kon test.bmp niet laden: %s\n", SDL_GetError());
        texture = nullptr;
        return;
    }

    this->renderer = renderer;

    weapons.push_back(new Weapon(WeaponType::Pistol, renderer)); // Start met pistool
    currentWeaponIndex = 0;

    

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

// DESTRUCTOR //
Player::~Player() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    for (auto w : weapons) delete w;
}

void Player::handleInput(const u64 kHeld, const u64 kDown) {
    bool moving = false;

    if (isGettingUp) return;

    if (kHeld & HidNpadButton_Up)    { rect.y -= speed; moving = true; }
    if (kHeld & HidNpadButton_Down)  { rect.y += speed; moving = true; }
    if (kHeld & HidNpadButton_Left)  { rect.x -= speed; moving = true; }
    if (kHeld & HidNpadButton_Right) { rect.x += speed; moving = true; }

    if (kDown & HidNpadButton_X) {
        switchWeapon(); // Wapen wisselen
    }

    if (moving) {
        lastInputTime = SDL_GetTicks();

        // Als player in de idle-zit animatie zit → start "opstaan"
        if (isIdleAnimating) {
            isGettingUp = true;
            isIdleAnimating = false;
            idleFrameStart = 6; // Start van de "opstaan" animatie
            frame = idleFrameStart;
            frameCounter = 0;
            return;
        }
    }

    // Update srcRect alleen als speler beweegt
    if (moving && !isIdleAnimating) {
        frameCounter++;
        if (frameCounter >= ANIMATION_DELAY) {
            frame = 1 + ((frame - 1 + 1) % 2); // Alterneren tussen frame 1 en 2
            frameCounter = 0;
        }
    }

    if (!moving && !isIdleAnimating) {
        frame = 0;
        frameCounter = 0;
    }

    // Zet srcRect bij elke frame wijziging
    srcRect.x = frame * FRAME_WIDTH;
}

void Player::update() {
    // Later kun je hier animaties of botsing toevoegen
    Uint32 currentTime = SDL_GetTicks();

    // Als speler idle is > 10 seconden (10.000 ms)
    if (!isIdleAnimating && !isGettingUp && currentTime - lastInputTime > 10000) {
        isIdleAnimating = true;
        frame = 4;
        idleFrameStart = 4;
        frameCounter = 0;
    }

    // Afspelen van idle-animatie zitten 
    if (isIdleAnimating) {
        frameCounter++;
        if (frameCounter >= ANIMATION_DELAY) {
            frame++;
            frameCounter = 0;

            if (frame > 5) {
                frame = 5; // Laatste idle-frame
            }
            srcRect.x = frame * FRAME_WIDTH;
        }
    }

    // Afspelen van "opstaan" animatie
    if (isGettingUp) {
        frameCounter++;
        if (frameCounter >= ANIMATION_DELAY) {
            frame++;
            frameCounter = 0;

            if (frame > 9) {
                frame = 0; // Terug naar idle
                isGettingUp = false;
            }

            srcRect.x = frame * FRAME_WIDTH;
        }
    }
}

void Player::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, &srcRect, &rect);
    } else {
        // Als de texture niet is geladen, teken een rechthoek
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // witte speler
        SDL_RenderFillRect(renderer, &rect);
    }
    
    // Render het wapen iets rechts van de speler
    Weapon* weapon = weapons[currentWeaponIndex];
    SDL_Texture* weaponTexture = weapon->getTexture();

    if (weaponTexture) {
        SDL_Rect weaponRect;
        weaponRect.w = 16;
        weaponRect.h = 8;
        weaponRect.x = rect.x; // rechts van speler
        weaponRect.y = rect.y + rect.h / 2 - weaponRect.h / 2;

        SDL_RenderCopy(renderer, nullptr, nullptr, &weaponRect);
        SDL_RenderCopy(renderer, weaponTexture, nullptr, &weaponRect);
    }
}

void Player::switchWeapon() {
    if (weapons.size() > 1) {
        currentWeaponIndex = (currentWeaponIndex + 1) % weapons.size();
    }
}

void Player::unlockWeapon(WeaponType type) {
    bool alreadyUnlocked = false;
    for (Weapon* w : weapons) {
        if (w->getType() == type) {
            alreadyUnlocked = true;
            break;
        }
    }
    if (!alreadyUnlocked) {
        weapons.push_back(new Weapon(type, renderer));
    }
}

Weapon* Player::getCurrentWeapon() const {
    return weapons[currentWeaponIndex];
}