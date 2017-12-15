#ifndef _LEVEL_H
#define _LEVEL_H

#include "Tile.h"
#include "Player.h"

class Level : public cSprite
{
private:
	//Number of columns and rows of tiles.
	int nRows;
	int nCols;
	//List of all tiles.
	Tile tiles[32][32];
	//Current tiles being created.
	Tile aTile;
	//Update positions of the tiles.
	void updatePos();
	//Collision detection.
	void ColDet();
	bool PlayerCol(SDL_Rect a, SDL_Rect b, bool solid, bool slow, int row, int col);
	bool SimpleCol(SDL_Rect a, SDL_Rect b, bool solid);
	//OPtimization: Limit the number of times we check for collisions.
	int limit;

public:
	//Basic functions.
	void initalize(cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt);
	void update();
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt);

	int temp;
};
#endif
