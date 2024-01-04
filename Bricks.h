#pragma once

//This file contains all classes bricks classes 
#include "collidable.h"



enum BrickType	//add more brick types
{
	BRK_NRM,	//Normal Brick
	BRK_BMB,	//Bomb Brick
	BRK_RCK,
	BRK_PUD,
	BRK_HRD

	//TODO: Add more types
};

////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
//Base class for all bricks
class brick :public collidable
{
public:
	brick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	~brick();
};


////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
class normalBrick :public brick
{
public:
	normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};

////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
class bombBrick :public brick
{
public:
	bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};

////////////////////////////////////////////////////  class rockBrick  /////////////////////////////////
class rockBrick :public brick
{
public:
	rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};

////////////////////////////////////////////////////  class powerup_downBrick  /////////////////////////////////
class powerup_downBrick :public brick
{

public:
	powerup_downBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};
////////////////////////////////////////////////////  class harbrick  /////////////////////////////////

class hardBrick :public brick
{
private:
	int strength;
public:
	hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
};




