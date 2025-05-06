#pragma once

#include <SDL2/SDL.h>
#include <string>

enum class WeaponType {
    Pistol,
    Shotgun,
    Rifle
};

class Weapon {
public:
    Weapon(WeaponType type, SDL_Renderer* renderer);
    ~Weapon();

    WeaponType getType() const;
    std::string getName() const;
    int getDamage() const;
    SDL_Texture* getTexture() const;

private:
    WeaponType type;
    int damage;
    SDL_Texture* texture;
};
