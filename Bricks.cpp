 #include "Bricks.h"
#include "game.h"
#include"Collectible.h"


////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
brick::brick(point r_uprleft, int r_width, int r_height, game* r_pGame):
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
}

brick::~brick(){
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->DrawRectangle(uprLft.x, uprLft.y, uprLft.x + width, uprLft.y + height);
	pGame->getGrid()->sortDangling(uprLft); //sets to nullptr only as already deleted from heap when "delete this;" is called.
}


////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
normalBrick::normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame):
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
}

void normalBrick::collisionAction()
{
	pGame->updateScore(1);
	

	delete this;
}

////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
bombBrick::bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\BombBrick.jpg";
}

void bombBrick::collisionAction()
{
	//TODO: Add collision action logic
}

////////////////////////////////////////////////////  class rockBrick  /////////////////////////////////
rockBrick::rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\RockBrick.jpg";
}

void rockBrick::collisionAction()
{
	//TODO: Add collision action logic
}

////////////////////////////////////////////////////  class powerup_downBrick  /////////////////////////////////
powerup_downBrick::powerup_downBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\Powerup_downBrick.jpg";
	
}

void powerup_downBrick::collisionAction()
{
	
	
	
    collectible* c1;
	c1 = new powerup(uprLft, 7, pGame);
	
	
	pGame->addcollectibles(c1);
	delete this;
	
	//////////pGame->getWind()->SetBrush(RED);
	///////////pGame->getWind()->DrawCircle(uprLft.x, uprLft.y, 7);
	
	
	
}

/////////////////////////////////////////////////// class hardbrick /////////////////////////////////////////////////////////
hardBrick::hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\HardBrick.jpg";
	strength = 3;
}

void hardBrick::collisionAction()
{
	strength--;
	pGame->updateScore(1);
	// Check if the brick is destroyed
	if (strength <= 0)
	{
		delete this;
	}
	
}

