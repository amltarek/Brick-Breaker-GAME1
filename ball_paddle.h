#pragma once
#include "collidable.h"
class paddle :public collidable {
private:

public:
	paddle(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	void move_paddle_right(paddle*);
	void move_paddle_left(paddle*);
};

class ball :public collidable {
private:

public:
	ball(point r_uprleft, int r_width, int r_height, game* r_pGame);
	void collisionAction();
	void move_ball(ball*, float []);
	void get_velocity(ball*,paddle*, float[]);
};