#include "ball_paddle.h"
#include"collidable.h"
#include "game.h"
#include "gameConfig.h"

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


void ball::move_ball(ball* aball, float velocity[])
{
	pGame->getWind()->SetPen(LAVENDER, 1);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
	point prevPosition = uprLft;


	uprLft.y += velocity[1] * 3;
	uprLft.x += velocity[0] * 3;

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
	if (uprLft.x >= 1195) {
		velocity[0] = -1;
		velocity[1] = velocity[1];
		uprLft.x = 1194;
	}
	aball->draw();

}

void ball::get_velocity(paddle* apaddle, float velocity[])
{
	point z = Collision_Check(this, apaddle);
	float pos_onpaddle = (apaddle->getWidth()) - z.x;
	float pos_from_center = pos_onpaddle - (apaddle->getWidth() /float(2));
	float fraction = pos_onpaddle / (apaddle->getWidth()/2);
	float angle = fraction * 45;
	float angle_rad = fraction * 3.14 / 180;
	if (z.x != 0 && z.y != 0) {
		velocity[0] = cos(angle);
		velocity[1] = sin(angle);
	}
}