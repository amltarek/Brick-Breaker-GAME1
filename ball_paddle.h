#pragma once
#include "collidable.h"
#include "Bricks.h"
class paddle :public collidable {

private:

public:
	paddle(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	void move_paddle_right();
	void reset_pos();
	void move_paddle_left();
};

class ball :public collidable {
private:

public:
	ball(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	bool move_ball();
	void get_velocity();
	void brickdeflection();
	void draw();
	void reset_position();
};