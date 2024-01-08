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
    bool  move_collectible();
    void setindex(int index);
    int getindex();
    virtual void stopAction() = 0;
};

enum CollectibleType {
    FIREBALL,
    INVERTED_PADDLE,
    WINDGLIDE,
    QUICKSAND,
    FREEZE,
    CLTB_CNT
};

class fireball : public collectible {
public:
    fireball(point r_uprleft, int r_radius, game* r_pGame,int r_duration);
    void collisionAction() override;
    void stopAction() override;
};

class invertedPaddle : public collectible {
public:
    invertedPaddle(point r_uprleft, int r_radius, game* r_pGame,int r_duration);
    void collisionAction() override;
    void stopAction() override;
};

class Windglide : public collectible {
public:
    Windglide(point r_uprleft, int r_radius, game* r_pGame, int r_duration);
    void collisionAction() override;
    void stopAction() override;
};

class Quicksand : public collectible {
public:
    Quicksand(point r_uprleft, int r_radius, game* r_pGame, int r_duration);
    void collisionAction() override;
    void stopAction() override;
};

class freeze : public collectible {
    float* direction;
public:
    freeze(point r_uprleft, int r_radius, game* r_pGame, int r_duration);
    void collisionAction() override;
};

