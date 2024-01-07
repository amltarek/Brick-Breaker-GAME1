#pragma once
#include "collidable.h"
#include "game.h"
#include "gameConfig.h"
#include "grid.h"
#include "CMUgraphicsLib/auxil.h"

class collectible : public collidable {
protected:
    int index;
    timer collectibleTimer;
    int duration;
   
public:
    collectible(point r_uprleft, int r_radius, game* r_pGame,int r_duration);
    ~collectible();
    
    virtual void draw()=0;
    void collisionAction()=0 ;
    bool  move_collectible();
    void setindex(int index);
    int getindex();
   
};

class powerup : public collectible {
public:
    powerup(point r_uprleft, int r_radius, game* r_pGame,int r_duration);
    void collisionAction() override;
    void draw();

};

class powerdown : public collectible {
public:
    powerdown(point r_uprleft, int r_radius, game* r_pGame,int r_duration);

    void collisionAction() override;
    void draw() override;
};