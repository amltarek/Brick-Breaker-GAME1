#pragma once
#include "collidable.h"
#include "game.h"
#include "gameConfig.h"
#include "grid.h"
#include "CMUgraphicsLib/auxil.h"

class collectible : public collidable {
protected:
 
   
public:
    collectible(point r_uprleft, int r_radius, game* r_pGame);
    ~collectible();
    
    virtual void draw()=0;
    void collisionAction()=0 ;
    bool  move_collectible();
   
};

class powerup : public collectible {
public:
    powerup(point r_uprleft, int r_radius, game* r_pGame);
    void collisionAction() override;
    void draw();

};

class powerdown : public collectible {
public:
    powerdown(point r_uprleft, int r_radius, game* r_pGame);

    void collisionAction() override;
    void draw() override;
};