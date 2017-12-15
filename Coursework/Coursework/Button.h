#ifndef _BUTTON_H
#define _BUTTON_H

#include "cSprite.h"
#include "Control.h"

class Button
{
private:
	//Animation
	float timing = 0;
	float interval = 30;
	//Button info
	string name;
	SDL_Point pos;
	//Sprites
	cSprite backgroundSprite;
	cSprite textSprite;

public:
	//Basic functions
	void initalize(string name, SDL_Point pos);
	void update();
	void renderBoth(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt);
	//Animation
	void animate();

};
#endif
