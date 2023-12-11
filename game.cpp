#include "game.h"
#include "gameConfig.h"
#include <chrono>
#include <thread>
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
	position.y = 470;
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

keytype game::getkey(char& x) const
{
	return pWind->WaitKeyPress(x);
}
keytype game::getkeyc(char& x) const
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

void game::setTimer(time_t time)
{
	this->timer = time;
}

void game::setStartTime(time_t startTime)
{
	this->startTime = startTime;
}

time_t game::getStartTime() const
{
	return startTime;
}

time_t game::getTime() const
{
	return timer;
}

int game::getScore()
{
	return score;
}

void game::updateTimer()
{
	this->timer = this->timer - this->startTime;
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
	char a;
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
			//pWind->SetBrush(PURPLE);
			//pWind->DrawRectangle(250, 0, 400, config.toolBarHeight);
			//gameToolbar->setTimer(time(0) - gameToolbar->getStartTime());
			// Draw timer
			//pWind->SetFont(20, BOLD, BY_NAME, "Arial");
			//pWind->SetPen(BLACK);
			//pWind->DrawString(250, 5, "Timer: " + to_string(timer));
			space = getkeyc(moveball);
			while (moveball == ' ') {
				do {
					float x[2] = { 0,-1 };
					tempball->move_ball(tempball, x);
					sleep_for(10000ns);
					ktype = getkeyc(a);
				} while (ktype != ARROW);
				printMessage("Play                                                                                                                                              Press Esc to access toolbar");
				while (ktype == ARROW) {

					if (a == 6) {
						temppaddle->move_paddle_right(temppaddle);

					}
					if (a == 4) {
						temppaddle->move_paddle_left(temppaddle);
					}
					ktype = NO_KEYPRESS;

				}
				if (ktype == ESCAPE) {
					printMessage("Toolbar accessed");
					getMouseClick(x, y);
					if (y >= 0 && y < config.toolBarHeight)
					{
						isExit = gameToolbar->handleClickPlayMode(x, y);
					}
				}
			}
		}
	} while (!isExit);
}