#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "grid.h"
#include "ball_paddle.h"
#include "timer.h"
#include <chrono>

//Main class that coordinates the game operation
class game
{
	enum MODE	//Game mode
	{
		MODE_DSIGN,	//Design mode (startup mode)
		MODE_PLAY	//Playing mode
	};

	MODE gameMode;

	/// Add more members if needed


	
	window* pWind;	//Pointer to the CMU graphics window
	toolbar* gameToolbar;
	grid* bricksGrid;
	collidable** ball_paddle = new collidable * [2];
	paddle* temppaddle;
	ball* tempball;
	
	int lives = 3;
	int timer = 0;
	int score = 0;
	time_t startTime = 0;
public:
	game();
	~game();

	

	clicktype getMouseClick(int& x, int& y) const;
	clicktype getMouseClickc(int& x, int& y) const;
	//Get coordinate where user clicks and returns click type (left/right)
	string getString() const;	 //Returns a string entered by the user
	keytype wait_key(char& x) const;

	keytype get_key(char& x) const;

	window* CreateWind(int, int, int, int) const; //creates the game window


	void clearStatusBar() const;	//Clears the status bar


	void printMessage(string msg) const;	//Print a message on Status bar

	void go() const;

	window* getWind() const;		//returns a pointer to the graphics window

	void setGameMode(int gamemode);

	grid* getGrid() const;

	toolbar* getGameToolbar() const;

	collidable** getBallorPaddle() const;
	ball* getball() const;
	paddle* getpaddle() const;
	void updateScore(int scoreChange);
	int getScore();
	void decreaseLives();
};

