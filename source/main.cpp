// main.cpp
#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <switch.h>

#include <SDL2/SDL.h>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


/* GLOBALE VARIABELEN */
bool quit = false;


// Functie om evenementen te verwerken
void handleEvents(PadState* pad, Player& player) {
    u64 kHeld = padGetButtons(pad); // Knoppen die nu worden ingedrukt
    u64 kDown = padGetButtonsDown(pad); // Knoppen die nu worden ingedrukt en ook 
    player.handleInput(kHeld);

    if (kDown & HidNpadButton_Plus) {quit = true;}
}

/*//////////////////////////////////////////////////////////////////////
// Functie om de game loop te starten, main entrypoint!
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
int main(int argc, char* argv[]) {
    romfsInit();
    chdir("romfs:/");

    // Configureer de controller invoer
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    SDL_Init(SDL_INIT_EVERYTHING);

    // Maak een venster aan en een renderer om graphics op het scherm te kunnen renderen
    SDL_Window* window = SDL_CreateWindow("Seal Hunter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player player(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    /*///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Game loop
    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
    while (!quit)
    {
        // Verwerk de controller invoer
        padUpdate(&pad);
        handleEvents(&pad, player);
        
        // Wis het scherm
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Zwarte achtergrond
        SDL_RenderClear(renderer);

        // Render objecten
        player.update();
        player.render(renderer);

        // Update het scherm
        SDL_RenderPresent(renderer);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    romfsExit();
    return 0;
}