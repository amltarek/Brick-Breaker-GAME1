#pragma once
#include "collidable.h"
#include "game.h"
#include "gameConfig.h"
#include "grid.h"
#include "CMUgraphicsLib/auxil.h"

class collectible : public collidable {
    game* pGame;
 
    
    int radius;

public:
    collectible(point r_uprleft, int r_radius, game* r_pGame);
    ~collectible();

    void update();
    void draw();
    void collisionAction() override;
    bool  move_collectible();
};