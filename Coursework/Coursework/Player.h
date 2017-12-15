#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include "GameConstants.h"
#include "cTextureMgr.h"
#include "cSprite.h"
#include "Projectile.h"

class Player
{
private:
	static Player* pInstance;
	//Score
	int score;
	//Health
	int health;
	//Sprites
	cSprite spChar;
	cSprite spHealth;
	//Movement
	void movement();
	float speed;
	bool slow;
	SDL_Point posCentre;
	vector<string> directions;
	void addDir(std::string dir);
	void removeDir(std::string dir);
	//Shooting
	vector<Projectile> projectiles;
	float timer;
	float firerate;

public:
	static Player* getInstance();
	//Basic functions
	void initalize();
	void update();
	void render(SDL_Renderer* theRenderer);
	//Score
	void setScore(int s);
	void modScore(int i);
	int getScore();
	//Health
	void hit(int amount);
	int getHealth();
	void setHealth(int h);
	//Movement
	SDL_Rect getPos();
	void setSlow(bool slow);
	SDL_Point getPosCentre();
	//Shooting
	vector<Projectile> getProjectiles();
	void removeProjectile(int index);
	void removeAllProjectiles();
	//Revive
	void revive();
};
#endif
