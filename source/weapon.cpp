#include "weapon.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Weapon::Weapon(WeaponType type, SDL_Renderer* renderer) : type(type) {
    switch (type) {
        case WeaponType::Pistol: 
            damage = 10; 
            texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("romfs:/sprites/weapons/pistol/pistol.bmp"));
            break;
        case WeaponType::Shotgun: 
            damage = 25; 
            texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("romfs:/sprites/weapons/shotgun/shotgun.bmp"));
            break;
        case WeaponType::Rifle: 
            damage = 15; 
            texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("romfs:/sprites/weapons/rifle/rifle.bmp"));
            break;
    }
}

Weapon::~Weapon() {
    if (texture) SDL_DestroyTexture(texture);
}

WeaponType Weapon::getType() const {
    return type;
}

std::string Weapon::getName() const {
    switch (type) {
        case WeaponType::Pistol: return "Pistol";
        case WeaponType::Shotgun: return "Shotgun";
        case WeaponType::Rifle: return "Rifle";
        default: return "Unknown";
    }
}

int Weapon::getDamage() const {
    return damage;
}

SDL_Texture* Weapon::getTexture() const { return texture; }