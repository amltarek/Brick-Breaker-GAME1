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
    int getcurrentcollect();

    void update();
    void draw();
    void collisionAction() ;
    bool  move_collectible();
    /////void addcollectibles(collectible*a2);
    collectible** geta1();
};