#ifndef _BOSS_H
#define _BOSS_H

//#include "GameConstants.h"
#include "cSprite.h"
#include "Projectile.h"

class Boss
{
private:
	static Boss* pInstance;
	//Health
	int health;
	//Movement
	void move();
	//Sprites
	cSprite spChar;
	cSprite spHealth;
	int txtWidth, txtHeight;
	//Position
	SDL_Point pos;
	SDL_Point posCentre;
	SDL_Point posProj;
	//Shooting
	std::vector<Projectile> projectiles;
	float timer;
	float fireRate;
	int fireMode;
	int fireTimes;
	bool direction;
	float angleSpacing;
	float angleOffset;

public:
	static Boss* getInstance();
	//Basic functions
	void initalize(SDL_Point p);
	void update();
	void render(SDL_Renderer* theRenderer);
	//Position
	SDL_Rect getPos();
	int getPosY();
	void setPosY(int y);
	//Shooting
	std::vector<Projectile> getProjectiles();
	void removeProjectile(int index);
	void removeAllProjectiles();
	//Health
	void hit(int amount);
	int getHealth();
	void setHealth(int h);
	//Reset everything
	void reset();

};
#endif
#pragma once
