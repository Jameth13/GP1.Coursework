#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>
#include "cFontMgr.h"
#include "cSoundMgr.h"


using namespace std;

class cGame
{
public:
	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void update();
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);

	static cGame* getInstance();

private:
	static cGame* pInstance;
	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;
	//Fonts
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	// Game objects
	// Define the elements and there position in/on the array/map
	int renderWidth, renderHeight;
};
#endif
