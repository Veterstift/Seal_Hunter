Seal Hunter - Nintendo Switch Game Development
A C++ & SDL2 Homebrew project
by Kenneth van der Maazen (c) 2024 - 2025

------------------------------
Date created:       03-04-2025    
Last updated:       08-04-2025
Current version:    0.0.1
------------------------------

Seal Hunter is a free 2D shoot 'em up game, this version is written and programmed by me from scratch with the only goal for it to be playable on the Nintendo Switch.
This game might trigger some people due to the content of seal hunting, but I want to make it clear that this game is not meant to promote or glorify seal hunting in any way.
The game is purely fictional and for entertainment and educational purposes only, feel free to download, use, alter and/or modify my source code as you see fit.

The concept of this game is to prevent the seals and other creatures from overpopulating the ocean and eating all the fish from it!
Using a wide range of weapons, players must prevent harmful sea creatures, ranging from seals to polar bears, from reaching back to the ocean to ensure a good catch.
The base game is divided into 5 levels, each with its own unique challenges and obstacles. 
later on I will be adding more functionalities like splitscreen Co-op and/or online Multiplayer, game modes such as endless survival mode or levels with different stages.

====================================================================
08-04-2025 - Version 0.0.1
--------------------------------------------------------------------
Update Logs:
    - Initial commit of the game, it is still in the early stages of development.
    - Added basic game loop and game logic.
    - Added player spritesheet, player movement animation and idle.
    - 

--------------------------------------------------------------------
Links:
- GitHub:   https://github.com/Veterstift/SealHunter
- Assets:   https://shpro.de.tl/GuidesTipsTricks.htm

=====================================================================
📁 Seal Hunter/
│
├── main.cpp                 // Entry point: bevat alleen de game loop
├── player.cpp / .h          // Alles omtrent speler (init, render, beweging, animatie)
├── enemy.cpp / .h           // Voor vijandlogica, bv. brown_seal
├── weapon.cpp / .h          // Voor wapenlogica (init, render, currentWeapon, maxBullets, reloadTime)
├── bullets.cpp / .h         // Afvuren, bijhouden, renderen en herladen van kogels
├── physics.cpp / .h         // Shells, blood physics & rendering
├── game.cpp / .h            // HUD rendering (wapens bar, bullet count, score, crosshair)
├── assets.cpp / .h          // Laadt en beheert alle textures, fonts en geluiden
├── menus.cpp / .h           // Startmenu, pauzemenu, optiesmenu, menu-invoer
├── config.h                 // Globale constants en instellingen
└── utils.cpp / .h           // Handige functies zoals `renderText()`, random helpers

======================================================================
1. main.cpp
    * Main entry point of the game.
    * Initializes SDL2 and sets up the game window.
    * Handles game loop and event handling.

2. Player.h / Player.cpp
    * struct Player
    * initPlayer(SDL_Renderer*)
    * handlePlayerMovement(PadState*)
    * renderPlayer(SDL_Renderer*)

3. Enemy.h / Enemy.cpp
    * struct Enemy
    * initEnemy(SDL_Renderer*)
    * updateEnemy()
    * renderEnemy(SDL_Renderer*)

4. Bullets.h / Bullets.cpp
    * struct Bullet
    * vector<Bullet> bullets
    * shootBullet()
    * updateBullet()
    * renderBullet(SDL_Renderer*)
    * renderBulletCount(SDL_Renderer*)
    * startReloading()
    * updateReloading()

5. Shells.h / Shells.cpp
    * struct Shell
    * vector<Shell> shells
    * initShellTextures(SDL_Renderer*)
    * updateShells()
    * renderShells(SDL_Renderer*)

6. MuzzleFlash.h / MuzzleFlash.cpp
    * initMuzzleFlash(SDL_Renderer*)
    * renderMuzzleFlash(SDL_Renderer*)

7. UI.h / UI.cpp
    * renderText(...)
    * renderHUD(SDL_Renderer*)
    * initHUD(SDL_Renderer*)
    * initWeapons(SDL_Renderer*)

8. GameState.h / GameState.cpp
    * enum GameState, 
    * renderStartMenu(SDL_Renderer*)
    * handleStartMenuInput(PadState*)
    * renderPauseMenu(SDL_Renderer*)
    * handlePauseMenuInput(PadState*)
    * renderOptionsMenu(SDL_Renderer*)
    * handleOptionsMenuInput(PadState*)
    * renderGameOverMenu(SDL_Renderer*)
    * handleGameOverMenuInput(PadState*)
    * updateGameState()
    * renderGameState(SDL_Renderer*)

9. Environment.h / Environment.cpp
    * initBackdropAndIce(SDL_Renderer*)
    * renderBackdropAndIce(SDL_Renderer*)

10. InputHandler.h / InputHandler.cpp
    * handleEvents(PadState*)

11. Resources.h / Resources.cpp
    * loadResources()
    * unloadResources()

-------------------------------------------------------------------
Spritesheets:
- Player: 180x20 [9 frames] = 20x20
    [frame 1] - idle
    [frame 2] - walk
    [frame 3] - walk
    - Idle:
    [frame 4] - sit
    [frame 5] - sit idle
    [frame 6] - stand up
    [frame 7] - stand up
    [frame 8] - stand up
    [frame 9] - standing up


-------------------------------------------------------------------
Basic Seal Hunter Controls (default):
Description         Key         Function
Move up             UP          Moves character up.
Move left           LEFT        Moves character left.
Move down           DOWN        Moves character down.
Move right          RIGHT       Moves character right.
Jump                (A)         Character jumps. Can smash a crawling brown seal by falling on him.
Fire (shoot)        (B)         Gun fires.
Reload weapon       (Y)         Reloads the current weapon.
Quickbuy            (X)         Buys the next available weapon.
Pause Game          [+]         Pauses the game.
Open buymenu        [-]         Opens a menu where you can buy different weapons.
Switch weapons      [L]/[R]     Toggles between all weapons, press [L] to switch to the previous weapon, [R] to switch to the next weapon.
Show stats          [ZL]        Show various informations: team, money, loadout, kill count, level progress.
Kick player         [ZR]        Kick the player in front of you.