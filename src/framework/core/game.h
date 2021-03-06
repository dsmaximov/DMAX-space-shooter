/************************************************************************
** This code is part of DMAX_Shooter.
**
** DMAX_Shooter is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
** It is based on https://github.com/Shot511/GameBreakout.
** Implementation of https://learnopengl.com/In-Practice/2D-Game/Breakout
*************************************************************************/

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game/game_object.h"
#include "game/game_level.h"
#include "game/game_enemies.h"
#include "game/power_up.h"
#include "framework/rendering/particle_generator_expl.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_BOSS,
    GAME_MAIN_MENU,
    GAME_WIN,
    GAME_LOSE,
    GAME_HIGHSCORE_MENU,
    GAME_LEVEL_COMPLETE,
    GAME_ENTER_INITIALS,
    GAME_HELP,
    GAME_CREDITS
};

// Represents the menu buttons
enum ActiveMenuButton {
    BUTTON_CONTINUE,
    BUTTON_NEW,
    BUTTON_SAVE,
    BUTTON_LOAD,
    BUTTON_HIGH_SCORES,
    BUTTON_HELP,
    BUTTON_CREDITS
};

// Represents the four possible (collision) directions
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
// Defines a Collision typedef that represents collision data
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(75, 75);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(350.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(0.0f, -1350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 7.5f;
// Size of the powerup
const glm::vec2 POWER_UP_SIZE = glm::vec2(50.0f, 50.0f);

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // Game state
    GameState              State;
    GLboolean              Keys[1024];
    GLboolean              KeysProcessed[1024];
    GLboolean              LevelLoaded;
    GLint                  KeyCode;
    int                    KeyAction;
    GLuint                 Width , Height;
    std::vector<GameLevel> Levels;
    GLuint                 Level;
    GLuint                 Shields;
    GLuint                 Score;
    GLint                  ScrollSpeed;

    
    std::vector <ParticleGeneratorExplosion*>ExplosionParticleEngines;
    std::vector <ParticleGeneratorExplosion*>ShieldHitParticleEngines;
    // Constructor/Destructor
    Game(GLuint width, GLuint height, GLuint scroll_speed);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    //Reset initialization and prepare for new game
    void ReInit(); 
    // GameLoop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt, GLfloat scroll_speed, glm::vec2 screen_size);
    void Render();
    void DoCollisions();
    // Reset
    void ResetLevel();
    void ResetPlayer();

private:
    const int InitialPlayerShields = 10;
    // GAME_LEVEL_COMPLETE variables
    GLfloat PulseCoeff;  //speed of pulsations
    GLboolean PulseFlag; //change direction of pulsations
    // Ship.Invulnerability variables
    GLuint InvulCounter; //speed of pulsations 
    GLuint InvulFlag;    //change direction of pulsations
    GLuint InvulTimer;   //lenght of invulnerability
};

#endif