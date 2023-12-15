#include "grid.h"
#include "game.h"
#include "gameConfig.h"

grid::grid(point r_uprleft, int wdth, int hght, game* pG):
	drawable(r_uprleft, wdth, hght, pG)
{

	rows = height / config.brickHeight;
	cols = width / config.brickWidth;

	brickMatrix = new brick ** [rows];
	for (int i = 0; i < rows; i++)
		brickMatrix[i] = new brick * [cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			brickMatrix[i][j] = nullptr;
}

grid::~grid()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				delete brickMatrix[i][j];	//delete all allocated bricks

	for (int i = 0; i < rows; i++)
		delete brickMatrix[i];

	delete brickMatrix;

}

void grid::draw() const
{
	window* pWind = pGame->getWind();
	//draw lines showing the grid
	pWind->SetPen(config.gridLinesColor,1);

	//draw horizontal lines
	for (int i = 0; i < rows; i++) {
		int y = uprLft.y + (i + 1) * config.brickHeight;
		pWind->DrawLine(0, y, width, y);
	}
	//draw vertical lines
	for (int i = 0; i < cols; i++) {
		int x = (i + 1) * config.brickWidth;
		pWind->DrawLine(x, uprLft.y, x, uprLft.y+ rows* config.brickHeight);
	}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (brickMatrix[i][j])
				brickMatrix[i][j]->draw();	//draw exisiting bricks


}

int grid::addBrick(BrickType brkType, point clickedPoint)
{
	//TODO:
	// 1- Check that the clickedPoint is within grid range (and return -1)
	// 2- Check that the clickedPoint doesnot overlap with an exisiting brick (return 0)

	//Here we assume that the above checks are passed
	
	//From the clicked point, find out the index (row,col) of the corrsponding cell in the grid
	int gridCellRowIndex = (clickedPoint.y-uprLft.y) / config.brickHeight;
	int gridCellColIndex = clickedPoint.x / config.brickWidth;

	//Now, align the upper left corner of the new brick with the corner of the clicked grid cell
	point newBrickUpleft;
	newBrickUpleft.x = uprLft.x + gridCellColIndex * config.brickWidth;
	newBrickUpleft.y = uprLft.y+ gridCellRowIndex * config.brickHeight;

	switch (brkType)
	{
	case BRK_NRM:	//The new brick to add is Normal Brick
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new normalBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_BMB:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new bombBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_RCK:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new rockBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_PUD:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new powerup_downBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;

	case BRK_HRD:
		brickMatrix[gridCellRowIndex][gridCellColIndex] = new hardBrick(newBrickUpleft, config.brickWidth, config.brickHeight, pGame);
		break;
		//TODO: 
		// handle more types
	}
	return 1;
}

void grid::sortDangling(point brickPosition)
{
	int col = (brickPosition.x) / config.brickWidth;
	int row = (brickPosition.y - config.toolBarHeight) / config.brickHeight;
	brickMatrix[row][col] = nullptr;
}

void grid::deleteBrick(point brickPosition)
{
	pGame->getWind()->SetBrush(LAVENDER);
	pGame->getWind()->SetPen(LAVENDER);
	pGame->getWind()->SetPen(config.gridLinesColor, 1);
	pGame->getWind()->DrawRectangle(brickPosition.x, brickPosition.y, brickPosition.x + 60, brickPosition.y + 30);
	pGame->getWind()->DrawLine(brickPosition.x, brickPosition.y,brickPosition.x + 60,brickPosition.y);
	pGame->getWind()->DrawLine(brickPosition.x, brickPosition.y, brickPosition.x, brickPosition.y+30);
	pGame->getWind()->DrawLine(brickPosition.x + 60, brickPosition.y, brickPosition.x + 60,  brickPosition.y + 30);
	pGame->getWind()->DrawLine(brickPosition.x, brickPosition.y + 30, brickPosition.x + 60,  brickPosition.y + 30);
	int col = (brickPosition.x)/config.brickWidth;
	int row = (brickPosition.y - config.toolBarHeight) / config.brickHeight;
	delete brickMatrix[row][col];
	brickMatrix[row][col] = nullptr;
}
