 #include "Bricks.h"
#include "game.h"
#include"Collectible.h"


////////////////////////////////////////////////////  class brick  ///////////////////////////////////////
brick::brick(point r_uprleft, int r_width, int r_height, game* r_pGame):
	collidable(r_uprleft, r_width, r_height, r_pGame)
{
}


BrickType brick::getType() const
{
	return type;
}


////////////////////////////////////////////////////  class normalBrick  /////////////////////////////////
normalBrick::normalBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\NormalBrick.jpg";
	type = BRK_NRM;
}

void normalBrick::collisionAction()
{
	pGame->updateScore(1);
	pGame->getGrid()->deleteBrick(uprLft);
}

////////////////////////////////////////////////////  class bombBrick  /////////////////////////////////
bombBrick::bombBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\BombBrick.jpg";
	type = BRK_BMB;
}

void bombBrick::collisionAction()
{

	grid* pGrid = pGame->getGrid();
	pGame->updateScore(5);


	point temp;
	temp.x = uprLft.x + width;
	temp.y = uprLft.y;
	
	
	temp.x = uprLft.x - width;
	temp.y = uprLft.y;
	pGrid->deleteBrick(temp);


	temp.x = uprLft.x;
	temp.y = uprLft.y+height;
	pGrid->deleteBrick(temp);

	temp.x = uprLft.x;
	temp.y = uprLft.y - config.brickHeight;
	pGrid->deleteBrick(temp);

	
	temp.x = uprLft.x + config.brickWidth;
	temp.y = uprLft.y + config.brickHeight;
	pGrid->deleteBrick(temp);


	temp.x = uprLft.x - config.brickWidth;
	temp.y = uprLft.y - config.brickHeight;
	pGrid->deleteBrick(temp);


	temp.x = uprLft.x + config.brickWidth;
	temp.y = uprLft.y - config.brickHeight;
	pGrid->deleteBrick(temp);


	temp.x = uprLft.x - config.brickWidth;
	temp.y = uprLft.y + config.brickHeight;
	pGrid->deleteBrick(temp);

	pGrid->deleteBrick(uprLft);
}

////////////////////////////////////////////////////  class rockBrick  /////////////////////////////////
rockBrick::rockBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\RockBrick.jpg";
	type = BRK_RCK;
}

void rockBrick::collisionAction()
{
	pGame->updateScore(1);
}

////////////////////////////////////////////////////  class powerup_downBrick  /////////////////////////////////
powerup_downBrick::powerup_downBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\Powerup_downBrick.jpg";
	type = BRK_PUD;
}

void powerup_downBrick::collisionAction()
{


	collectible* c1;
	c1 = new powerup(uprLft, 7, pGame);


	pGame->addcollectibles(c1);


	pGame->getGrid()->deleteBrick(uprLft);







}

/////////////////////////////////////////////////// class hardbrick /////////////////////////////////////////////////////////
hardBrick::hardBrick(point r_uprleft, int r_width, int r_height, game* r_pGame) :
	brick(r_uprleft, r_width, r_height, r_pGame)
{
	imageName = "images\\bricks\\HardBrick.jpg";
	type = BRK_HRD;
	strength = 3;
}

void hardBrick::collisionAction()
{
	strength--;
	pGame->updateScore(1);
	// Check if the brick is destroyed
	if (strength <= 0)
	{
		pGame->getGrid()->deleteBrick(uprLft);
	}

}

