#include "collectible.h"


collectible::collectible(point r_uprleft, int r_radius, game* r_pGame) :
    collidable(r_uprleft, r_radius * 2, r_radius * 2, r_pGame)
    
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
powerup::powerup(point r_uprleft, int r_radius, game* r_pGame):
	collectible(r_uprleft, r_radius, r_pGame) {}

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
powerdown::powerdown(point r_uprleft, int r_radius, game* r_pGame):
	collectible(r_uprleft, r_radius, r_pGame) {}

void powerdown::collisionAction()
{
	pGame->getpaddle()->inverted(true);
	
}

void powerdown::draw()
{
	pGame->getWind()->SetBrush(BLUE);
	pGame->getWind()->DrawCircle(uprLft.x, uprLft.y, 7);
}


