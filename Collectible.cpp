#include "collectible.h"


collectible::collectible(point r_uprleft, int r_radius, game* r_pGame,int r_duration) :
    collidable(r_uprleft, r_radius * 2, r_radius * 2, r_pGame),duration(r_duration)
    
{
}

collectible::~collectible()
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
//////////////////////////////////////powerup
powerup::powerup(point r_uprleft, int r_radius, game* r_pGame,int r_duration):
	collectible(r_uprleft, r_radius, r_pGame, r_duration) {}

void powerup::collisionAction()
{
		
	pGame->removecollectibles(this->getindex());
	
	

}

void powerup::draw()
{
	pGame->getWind()->SetBrush(RED);
	pGame->getWind()->DrawCircle(uprLft.x, uprLft.y, 7);
}
///////////////////////////////////////////////////////////////powerdown////////////////////////////////////////////
powerdown::powerdown(point r_uprleft, int r_radius, game* r_pGame,int r_duration):
	collectible(r_uprleft, r_radius, r_pGame,r_duration) {
	
	collectibleTimer.set_time();
	
}

void powerdown::collisionAction()
{
	pGame->getpaddle()->inverted(true);
	pGame->removecollectibles(this->getindex());

if (collectibleTimer.get_time() >= 6)
	{
	pGame->getpaddle()->inverted(false);
	}
	
}

void powerdown::draw()
{
	pGame->getWind()->SetBrush(BLUE);
	pGame->getWind()->DrawCircle(uprLft.x, uprLft.y, 7);
}


