#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "cSprite.h"

class Projectile
{
private:
	cSprite sprite;
	float speed;
	FPoint pos;
	FPoint trajectory;

public:
	void initalize(SDL_Point p, FPoint traj, LPCSTR name);
	void update();
	void render(SDL_Renderer* theRenderer);
	SDL_Rect getPos();

};
#endif
