#pragma once
#include "collidable.h"
#include "game.h"
#include "gameConfig.h"
#include "grid.h"
#include "CMUgraphicsLib/auxil.h"

class collectible : public collidable {
    game* pGame;
    point position;
    float velx;
    float vely;
    int radius;

public:
    collectible(point r_position, float r_velocityX, float r_velocityY, int r_radius, game* r_pGame);
    ~collectible();

    void update();
    void draw();
};