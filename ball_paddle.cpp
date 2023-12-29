#include "CMUgraphicsLib\CMUgraphics.h"
#include "ball_paddle.h"
#include"collidable.h"
#include "game.h"
#include "gameConfig.h"
#include "grid.h"
#include "CMUgraphicsLib/auxil.h"
/////////////////////////////////////////Paddle///////////////////////////////////////////////
paddle::paddle(point r_uprleft, int r_width, int r_height, game* r_pGame):
	collidable(r_uprleft, r_width, r_height, r_pGame){
	imageName = "images\\paddle.jpg";
}


//////////////////////////////////////////////////Pddle Collisions////////////////////////////////////////////////////
void paddle::collisionAction()
{
}


/////////////////////////////////////////////////////Paddle Movement//////////////////////////////////////////////////////////////////
void paddle::move_paddle_left()
{
	if (uprLft.x - 20 >= 0)
	{
		pGame->getWind()->SetPen(LAVENDER, 1);
		pGame->getWind()->SetBrush(LAVENDER);
		pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
		this->uprLft.x = uprLft.x - 20;
		this->draw();
	}
	pGame->getWind()->UpdateBuffer();
}

void paddle::move_paddle_right()
{
	if (uprLft.x + width + 20 <= pGame->getWind()->GetWidth()) {
		pGame->getWind()->SetPen(LAVENDER, 1);
		pGame->getWind()->SetBrush(LAVENDER);
		pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
		this->uprLft.x = uprLft.x + 20;
		this->draw();
	}
	pGame->getWind()->UpdateBuffer();
}

void paddle::reset_pos() {
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x+width, uprLft.y+height);
	uprLft.x = (config.windWidth / 2) - 50;
	uprLft.y = 500;
	this->draw();
}

//////////////////////////////////////////////////////////////////////Ball/////////////////////////////////////////////////////////////
ball::ball(point r_uprleft, int r_width, int r_height, game* r_pGame):
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\ball.jpg";
}

void ball::collisionAction()
{

}


bool ball::move_ball(float velocity[])
{

	point prevPosition = uprLft;

	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x+30,prevPosition.y+30);
	if (uprLft.y <= 40) {
		velocity[0] = velocity[0];
		velocity[1] = +1;
		uprLft.y = 40 + 1;
	}
	if (uprLft.x <=5) {
		velocity[0] = 1;
		velocity[1] = velocity[1];
		uprLft.x = 6;
	}
	if (uprLft.x >= 1150) {
		velocity[0] = -1;
		velocity[1] = velocity[1];
		uprLft.x = 1149;
	}
	if (uprLft.y >= 520) {
		velocity[0] = 0;
		velocity[1] = 0;
		return false;
	}
	uprLft.y += velocity[1] * 4;
	uprLft.x += velocity[0] * 4;

	pGame->getGrid()->draw();
	
	pGame->getpaddle()->draw();
	this->draw();
	pGame->getWind()->UpdateBuffer();
	Pause(5);
	return true;
}

void ball::get_velocity(float velocity[])
{
	paddle* thepaddle = pGame->getpaddle();
	point z = Collision_Check(this, thepaddle);
	float pos_onpaddle = (thepaddle->getWidth()) - z.x;
	float pos_from_center = pos_onpaddle - (thepaddle->getWidth() /float(2));
	float fraction = pos_onpaddle / (thepaddle->getWidth()/2);
	float angle = fraction * 45;
	float angle_rad = fraction * 3.14 / 180;
	if (z.x != 0 && z.y != 0) {
		velocity[0] = cos(angle);
		velocity[1] = sin(angle);
		this->uprLft.y = this->uprLft.y - 1;
	}

}

void ball::brickdeflection(float velocity[]) {
	grid* pGrid = pGame->getGrid();
	brick*** matrix = pGrid->get_matrix();
	for (int i = 0; i < pGrid->get_rows(); i++)
		for (int j = 0; j < pGrid->get_cols(); j++)
			if (matrix[i][j]) {
				brick* current_brick = matrix[i][j];
				point y = Collision_Check(this, current_brick);
				float pos_onpaddle = (current_brick->getWidth()) - y.x;
				float pos_from_center = pos_onpaddle - (current_brick->getWidth() / float(2));
				float fraction = pos_onpaddle / (current_brick->getWidth() / 2);
				float angle = fraction * 45;
				float angle_rad = fraction * 3.14 / 180;
				if (y.y != 0) {
					velocity[0] = cos(angle);
					velocity[1] = sin(angle);
					/*this->uprLft.y--;*/
				}
				else if (y.x != 0) {
					velocity[0] = -velocity[0];
					velocity[1] = velocity[1];
				}
			}

}

void ball::draw()
{
	pGame->getWind()->SetPen(BLUE);
	pGame->getWind()->SetBrush(BLUE);
	pGame->getWind()->DrawCircle(uprLft.x+15, uprLft.y+15, 15);
}

void ball::reset_position(float velocity[])
{
	pGame->getGameToolbar()->decrease_lives();
	pGame->getGameToolbar()->drawPlayMode();
	this->uprLft.x = (config.windWidth / 2) - 15;
	this->uprLft.y = 350;
	velocity[1] = 1;
	this->draw();
	pGame->getpaddle()->reset_pos();

}

