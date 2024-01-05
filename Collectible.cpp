#include "collectible.h"


collectible::collectible(point r_uprleft, int r_radius, game* r_pGame) :
    collidable(r_uprleft, r_radius * 2, r_radius * 2, r_pGame),
    radius(r_radius),pGame(r_pGame)
{
}

collectible::~collectible()
{

}



void collectible::update()
{
   
}

void collectible::draw()
{
   
    pGame->getWind()->SetBrush(RED);
    pGame->getWind()->DrawCircle(uprLft.x, uprLft.y, 7);
}

void collectible::collisionAction()
{ 
	pGame->removecollectibles(this);
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
	Pause(5);
	return true;

	
}

///void collectible::addcollectibles(collectible*a2)
//{
	///////a1 = new collectible * [maxcollect];
	////if (currentcollect < maxcollect)
	//////{
		////////for (int i = 0; i < maxcollect; i++)
		////////{
			////////a1[i] = a2;
			//////currentcollect++;
		/////}

	///////}
///////}





