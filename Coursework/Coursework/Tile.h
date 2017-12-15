#ifndef _TILE_H
#define _TILE_H

#include "cSprite.h"

class Tile : public cSprite
{
private:
	//Animation
	float timing = 0;
	float interval = 120;

public:
	//ID
	int id;
	//Attributes
	bool collidable;
	bool solid;
	bool slow;
	bool animated;
	//Animate
	void animate();

};
#endif