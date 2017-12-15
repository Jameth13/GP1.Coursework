#include "Level.h"
#include "Control.h"
#include "Boss.h"
#include "Tools.h"
#include <iostream>

static Control* control = Control::getInstance();
static Player* player = Player::getInstance();
static Boss* boss = Boss::getInstance();
static Tools* tools = Tools::getInstance();

void Level::initalize(cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt)
{
	//Level design
	int levelDesign[32][32] = {
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 } ,
		{ 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 2, 2, 2, 2 } ,
		{ 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 2, 2, 2 } ,
		{ 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 2, 2 } ,
		{ 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2 } ,
		{ 2, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 2, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 2, 2, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 2, 2, 2 } ,
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2 } ,
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
	};

	nRows = sizeof(levelDesign) / sizeof(levelDesign[0]);
	nCols = sizeof(levelDesign[0]) / sizeof(levelDesign[0][0]);

	for (int row = 0; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			tiles[row][col].id = levelDesign[row][col];

			//Tag collidable tiles.
			if (tiles[row][col].id == 2 || tiles[row][col].id == 3 || tiles[row][col].id == 4) tiles[row][col].collidable = true;
			if (tiles[row][col].id == 2 || tiles[row][col].id == 4) tiles[row][col].solid = true;
			if (tiles[row][col].id == 3) tiles[row][col].slow = true;
			if (tiles[row][col].id == 1 || tiles[row][col].id == 3)  tiles[row][col].animated = true;

			tiles[row][col].setTexture(theTxtMgr->getTexture(theTxt[tiles[row][col].id]));
			tiles[row][col].setSpriteDimensions(theTxtMgr->getTexture(theTxt[tiles[row][col].id])->getTWidth(), theTxtMgr->getTexture(theTxt[tiles[row][col].id])->getTHeight());
		}
	}
}

void Level::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt)
{
	for (int row = 0; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			//Render tile
			tiles[row][col].render(theRenderer, &tiles[row][col].getSpriteDimensions(), &tiles[row][col].getSpritePos(), tiles[row][col].getSpriteRotAngle(), &tiles[row][col].getSpriteCentre(), tiles[row][col].getSpriteScale());
		}
	}
}

void Level::update()
{
	//Must update tiles before collision detection.
	updatePos();
	ColDet();
}


void Level::updatePos()
{
	SDL_Rect tilePos = { control->getCameraPos().x, control->getCameraPos().y, 0 , 0 };

	for (int row = 0; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			tiles[row][col].setSpritePos({ tilePos.x, tilePos.y });
			tilePos.x += tiles[row][col].getSpritePos().w;
			if (tiles[row][col].animated) tiles[row][col].animate();
		}
		tilePos.x = control->getCameraPos().x;
		tilePos.y += 32;
	}
}

void Level::ColDet()
{
	temp++;
	for (int row = 0; row < nRows; row++)
	{
		for (int col = 0; col < nCols; col++)
		{
			//Collision between player and walls.
			if (PlayerCol(player->getPos(), tiles[row][col].getSpritePos(), tiles[row][col].solid, tiles[row][col].slow, row, col)) {
				updatePos();
			}
		}
	}


	for (unsigned int bul = 0; bul < player->getProjectiles().size(); bul++) {
		
		bool remove = false;
		//Collision between player bullets and walls.
		int x = tools->round((-control->getCameraPos().x + player->getProjectiles()[bul].getPos().x + 0.5f) / 32.0f);
		int y = tools->round((-control->getCameraPos().y + player->getProjectiles()[bul].getPos().y + 0.5f) / 32.0f);

		if (tiles[y][x].solid == true) {
			remove = true;
		}

		//Collision between player bullets and boss.
		if (SimpleCol(boss->getPos(), player->getProjectiles()[bul].getPos(), true)) {
			remove = true;
			player->modScore(1);
			boss->hit(5);
		}

		if(remove) player->removeProjectile(bul);
	}


	for (unsigned int bul = 0; bul < boss->getProjectiles().size(); bul++) {

		bool remove = false;
		//Collision between boss bullets and walls.
		int x = tools->round((-control->getCameraPos().x + boss->getProjectiles()[bul].getPos().x + 0.5f) / 32.0f);
		int y = tools->round((-control->getCameraPos().y + boss->getProjectiles()[bul].getPos().y + 0.5f) / 32.0f);

		if (tiles[y][x].solid == true) {
			remove = true;
		}

		//Collision between boss bullets and player.
		if (SimpleCol(player->getPos(), boss->getProjectiles()[bul].getPos(), true)) {
			remove = true;
			player->hit(1);
		}

		if (remove) boss->removeProjectile(bul);
	}

}

//Collision detection between the player and solid walls.
bool Level::PlayerCol(SDL_Rect a, SDL_Rect b, bool solid, bool slow, int row, int col) {

	//Quick detection
	if (a.x + a.w <= b.x) return false;
	if (b.x + b.w <= a.x) return false;
	if (a.y + a.h <= b.y) return false;
	if (b.y + b.h <= a.y) return false;

	//Detailed collision for solid objects
	if (solid)
	{
		float moveX = 0;
		float moveY = 0;

		//Right
		if (a.x > b.x + b.w / 2) moveX += -(b.x + b.w - a.x);
		//Left
		if (a.x < b.x - b.w / 2) moveX += (a.x + a.w - b.x);
		//Top
		if (a.y < b.y - b.h / 2) moveY += (a.y + a.h - b.y);
		//Bottom
		if (a.y > b.y + b.h / 2) moveY += -(b.y + b.h - a.y);

		if (std::abs(moveX) > std::abs(moveY) && moveY != 0) moveX = 0;
		if (std::abs(moveX) < std::abs(moveY) && moveX != 0) moveY = 0;

		if (std::abs(moveX) == std::abs(moveY)) {

			if (SimpleCol(a, tiles[row + 1][col].getSpritePos(), tiles[row + 1][col].solid) ||
				SimpleCol(a, tiles[row - 1][col].getSpritePos(), tiles[row - 1][col].solid) ||
				SimpleCol(a, tiles[row][col + 1].getSpritePos(), tiles[row][col + 1].solid) ||
				SimpleCol(a, tiles[row][col - 1].getSpritePos(), tiles[row][col - 1].solid))
				return false;
		}

		control->moveCameraPos({ moveX, moveY });

	}

	if (slow) player->setSlow(true);

	return true;
}

bool Level::SimpleCol(SDL_Rect a, SDL_Rect b, bool solid) {

	if (a.x + a.w <= b.x) return false;
	if (b.x + b.w <= a.x) return false;
	if (a.y + a.h <= b.y) return false;
	if (b.y + b.h <= a.y) return false;

	if (solid) return true;

	return false;
}
