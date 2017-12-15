#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include "Level.h"
#include "Player.h"
#include "Button.h"
#include "Boss.h"

class SceneManager
{
private:
	static SceneManager* pInstance;
	cSprite scene;
	string curScene;
	Level level;
	std::vector<Button> buttons;
	bool oneLoad = false;
	bool continuing = false;
	fstream saveGame;
	bool saveGameAvailable;
	int line;
	//Save savedata.
	void saveFile();
	//Load each line of savedata.
	void loadFileIter(string sLine);
	//Save and Load notifications
	int notiTimer;
	bool notiSave;
	bool notiLoad;

public:
	static SceneManager* getInstance();
	//Basic funstions
	void initalize(SDL_Renderer* theRenderer, vector<LPCSTR> theTxt);
	void update();
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, vector<LPCSTR> theTxt);
	//Load new scene.
	void load(string newScene);
	void resetOneLoad();
	//Load savedata.
	void loadFile();
};
#endif
