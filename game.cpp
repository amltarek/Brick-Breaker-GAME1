#include "game.h"
#include "gameConfig.h"
#include <chrono>
#include <thread>
#include "grid.h"
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
game::game()
{
	//Initialize playgrond parameters
	gameMode = MODE_DSIGN;


	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;

	gameToolbar = new toolbar(toolbarUpperleft,0,config.toolBarHeight, this);
	gameToolbar->drawDesignMode();

	//3 - create and draw the grid
	point gridUpperleft;
	gridUpperleft.x = 0;
	gridUpperleft.y = config.toolBarHeight;
	bricksGrid = new grid(gridUpperleft, config.windWidth, config.gridHeight, this);
	bricksGrid->draw();
	
	//4- Create the Paddle
	//TODO: Add code to create and draw the paddle
	point uperleft;
	uperleft.x = 520;
	uperleft.y = 500;
	int paddle_width = 100;
	int paddle_height = 30;
	temppaddle= new paddle(uperleft, paddle_width, paddle_height, this);
	temppaddle->draw();
	//5- Create the ball
	//TODO: Add code to create and draw the ball
	point position;
	position.x = 555;
	position.y = 350;
	tempball = new ball(position, 30, 30, this);
	//ball_paddle[0]->draw();
	//6- Create and clear the status bar
	clearStatusBar();
}

game::~game()
{
	delete pWind;
	delete gameToolbar;
	delete bricksGrid;
}


clicktype game::getMouseClick(int& x, int& y) const
{
	return pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
clicktype game::getMouseClickc(int& x, int& y) const
{
	return pWind->GetMouseClick(x, y);	//Wait for mouse click
}
keytype game::wait_key(char& x) const
{
	return pWind->WaitKeyPress(x);
}
keytype game::get_key(char& x) const
{
	return pWind->GetKeyPress(x);
}
//////////////////////////////////////////////////////////////////////////////////////////
window* game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}



window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}

void game::setGameMode(int gamemode)
{
	this->gameMode = MODE(gamemode);
}



string game::getString() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}



grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return bricksGrid;
}

toolbar* game::getGameToolbar() const
{
	return gameToolbar;
}

collidable** game::getBallorPaddle() const
{
	return ball_paddle;
}

ball* game::getball() const
{
	return tempball;
}

paddle* game::getpaddle() const
{
	return temppaddle;
}


int game::getScore()
{
	return score;
}

void game::updateScore(int scoreChange)
{
	score += scoreChange;
}

void game::decreaseLives()
{
	lives = lives - 1;
	if (lives <= 0) {
		//end sequence
	}
}

////////////////////////////////////////////////////////////////////////
void game::go() const
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;
	char paddle_movement;
	char moveball;
	keytype ktype;
	keytype space;

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Brick Breaker (CIE202-project) - - - - - - - - - -");
	do
	{
		if (gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		{
			printMessage("Ready...");
			getMouseClick(x, y);	//Get the coordinates of the user click
			//[1] If user clicks on the Toolbar
			pWind->SetBrush(LAVENDER);
			if (y >= 0 && y < config.toolBarHeight)
			{
				isExit = gameToolbar->handleClickDesignMode(x, y);
			}
		}
		if (gameMode == MODE_PLAY) {
			space = get_key(moveball);
			float direction[2] = { 0,1 };
			temppaddle->draw();
			while (moveball == ' ') {
				do {
					gameToolbar->draw_time(pWind);
					tempball->move_ball(direction);
					tempball->get_velocity(direction);
					tempball->brickdeflection(direction);
					ktype = get_key(paddle_movement);
					if (ktype == ESCAPE) {
						printMessage("Toolbar accessed");
						getMouseClickc(x, y);
						if (y >= 0 && y < config.toolBarHeight)
						{
							isExit = gameToolbar->handleClickPlayMode(x, y);
						}
					}
				} while (ktype != ARROW);
				printMessage("Play                                                                                                                                              Press Esc to access toolbar");
				while (ktype == ARROW) {

					if (paddle_movement == 6) {
						temppaddle->move_paddle_right();
					}
					if (paddle_movement == 4) {
						temppaddle->move_paddle_left();
					}
					ktype = NO_KEYPRESS;

				} 

			}
		}
	} while (!isExit);
	pWind->SetBuffering(false);
}