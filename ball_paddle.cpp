#include "ball_paddle.h"
#include"collidable.h"
#include "game.h"
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
void paddle::move_paddle_left(paddle* apaddle)
{
	pGame->getWind()->SetPen(LAVENDER, 1);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
	apaddle->uprLft.x = uprLft.x - 20;
	apaddle->draw();
}

void paddle::move_paddle_right(paddle* apaddle)
{
	pGame->getWind()->SetPen(LAVENDER, 1);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
	apaddle->uprLft.x = uprLft.x + 20;
	apaddle->draw();
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
	uprLft.y = uprLft.y + velocity[1]*2;
	uprLft.x = uprLft.x + velocity[0]*2;
	aball->draw();
}

void ball::get_velocity(ball* aball, paddle* apaddle,float velocity[])
{
	point z=Collision_Check(aball, apaddle);
	float pos_onpaddle= (apaddle->getWidth())-z.x;
	float pos_from_center = pos_onpaddle - apaddle->getWidth() / 2;
	float fraction = pos_onpaddle / (apaddle->getWidth() / 2);
	float angle = fraction * 45;
	float angle_rad = fraction * 3.14 / 180;
	if (z.x!=0&&z.y!=0) {
		velocity[0] = cos(angle);
		velocity[1] = sin(angle);
	}
}
