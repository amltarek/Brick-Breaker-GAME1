#include "collectible.h"


collectible::collectible(point r_uprleft, int r_radius, game* r_pGame,int r_duration) :
    collidable(r_uprleft, r_radius * 2, r_radius * 2, r_pGame),duration(r_duration)
    
{
}



bool collectible::move_collectible()
{
	point prevPosition = uprLft;
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(prevPosition.x, prevPosition.y, prevPosition.x + 30, prevPosition.y + 30);
	uprLft.y++;
	pGame->getpaddle()->draw();
	this->draw();
	pGame->getWind()->UpdateBuffer();
	if (prevPosition.y >= 520) {
		pGame->removecollectibles(this->getindex());
		return false;
	}
	return true;
}
void collectible::setindex(int index)
{
	this->index = index;
}
int collectible::getindex()
{
	return index;
}

fireball::fireball(point r_uprleft, int r_radius, game* r_pGame,int r_duration):
	collectible(r_uprleft, r_radius, r_pGame, r_duration) {
	imageName = "images\\collectibles\\Fireball.jpg";
}

void fireball::collisionAction()
{
	pGame->getball()->setType(FIRE_BALL);

	pGame->removecollectibles(this->getindex());
}

void fireball::stopAction()
{
	pGame->getball()->setType(NRM_BALL);
}

invertedPaddle::invertedPaddle(point r_uprleft, int r_radius, game* r_pGame,int r_duration):
	collectible(r_uprleft, r_radius, r_pGame,r_duration) {
	imageName = "images\\collectibles\\inverted paddle.jpg";
}

void invertedPaddle::collisionAction()
{
	pGame->getpaddle()->inverted(true);
	pGame->removecollectibles(this->getindex());
}

void invertedPaddle::stopAction()
{
	pGame->getpaddle()->inverted(false);
}

Windglide::Windglide(point r_uprleft, int r_radius, game* r_pGame, int r_duration) :
	collectible(r_uprleft, r_radius, r_pGame, r_duration) {
	imageName = "images\\collectibles\\Windglide.jpg";
}

void Windglide::collisionAction()
{
	pGame->getpaddle()->setSpeed(40);
	pGame->removecollectibles(this->getindex());
}

void Windglide::stopAction()
{
	pGame->getpaddle()->setSpeed(30);
}

Quicksand::Quicksand(point r_uprleft, int r_radius, game* r_pGame, int r_duration) :
	collectible(r_uprleft, r_radius, r_pGame, r_duration) {
	imageName = "images\\collectibles\\Quicksand.jpg";
}

void Quicksand::collisionAction()
{
	pGame->getpaddle()->setSpeed(10);
	pGame->removecollectibles(this->getindex());
}

void Quicksand::stopAction()
{
	pGame->getpaddle()->setSpeed(30);
}
