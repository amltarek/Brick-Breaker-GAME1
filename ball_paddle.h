#pragma once
#include "collidable.h"
#include "Bricks.h"
class paddle :public collidable {
private:

public:
	paddle(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	void move_paddle_right();
	void move_paddle_left();
};

class ball :public collidable {
private:

public:
	ball(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	void move_ball(float []);
	void get_velocity(float velocity[]);
	void brickdeflection(float velocity[]);
};