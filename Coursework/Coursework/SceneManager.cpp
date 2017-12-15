#include <iostream>
#include <string>
#include "SceneManager.h"
#include "cFontMgr.h"
#include "cSoundMgr.h"

SceneManager* SceneManager::pInstance = NULL;
static cTextureMgr* theTxtMgr = cTextureMgr::getInstance();
static cFontMgr* fontMgr = cFontMgr::getInstance();
static cSoundMgr* soundMgr = cSoundMgr::getInstance();
static Player* player = Player::getInstance();
static Boss* boss = Boss::getInstance();
static Control* control = Control::getInstance();

SceneManager * SceneManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new SceneManager();
	}
	return SceneManager::pInstance;
}

void SceneManager::load(string newScene)
{
	//Prevent multiple scene loads per frame.
	if (oneLoad) return;
	oneLoad = true;

	curScene = newScene;
	buttons.clear();
	static cTextureMgr* theTxtMgr = cTextureMgr::getInstance();

	//For each current scene, load any textures or buttons.
	if (curScene == "mainMenu") {
		scene.setTexture(theTxtMgr->getTexture("mainMenu"));
		scene.setSpritePos({ 0, 0 });
		scene.setSpriteDimensions(theTxtMgr->getTexture("mainMenu")->getTWidth(), theTxtMgr->getTexture("mainMenu")->getTHeight());
		
		if (continuing) {
			Button button1;
			button1.initalize("continueLoad", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 0 });
			buttons.push_back(button1);
			continuing = false;
		} else {
			Button button1;
			button1.initalize("start", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 0 });
			buttons.push_back(button1);
		}

		Button button2;
		button2.initalize("controls", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 50 });
		buttons.push_back(button2);

		Button button3;
		button3.initalize("credits", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 100 });
		buttons.push_back(button3);

		Button button4;
		button4.initalize("quit", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 150 });
		buttons.push_back(button4);
	}

	if (curScene == "controls") {
		scene.setTexture(theTxtMgr->getTexture("controls"));
		scene.setSpritePos({ 0, 0 });
		scene.setSpriteDimensions(theTxtMgr->getTexture("controls")->getTWidth(), theTxtMgr->getTexture("controls")->getTHeight());

		Button buttonControl;
		buttonControl.initalize("back", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 200 });
		buttons.push_back(buttonControl);
	}

	if (curScene == "credits") {
		scene.setTexture(theTxtMgr->getTexture("credits"));
		scene.setSpritePos({ 0, 0 });
		scene.setSpriteDimensions(theTxtMgr->getTexture("credits")->getTWidth(), theTxtMgr->getTexture("credits")->getTHeight());

		Button buttonCredits;
		buttonCredits.initalize("back", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 200 });
		buttons.push_back(buttonCredits);
	}

	if (curScene == "win") {
		soundMgr->getSnd("bossDeath")->play(0);

		scene.setTexture(theTxtMgr->getTexture("win"));
		scene.setSpritePos({ 0, 0 });
		scene.setSpriteDimensions(theTxtMgr->getTexture("win")->getTWidth(), theTxtMgr->getTexture("win")->getTHeight());

		Button buttonBack;
		buttonBack.initalize("backReset", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 200 });
		buttons.push_back(buttonBack);
	}

	if (curScene == "gameOver") {
		soundMgr->getSnd("playerDeath")->play(0);

		scene.setTexture(theTxtMgr->getTexture("gameOver"));
		scene.setSpritePos({ 0, 0 });
		scene.setSpriteDimensions(theTxtMgr->getTexture("gameOver")->getTWidth(), theTxtMgr->getTexture("gameOver")->getTHeight());

		Button buttonContinue;
		buttonContinue.initalize("continue", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 150 });
		buttons.push_back(buttonContinue);

		Button buttonBack;
		buttonBack.initalize("backReset", { WINDOW_WIDTH / 2 - theTxtMgr->getTexture("button01")->getTWidth() / 2, WINDOW_HEIGHT / 2 + 200 });
		buttons.push_back(buttonBack);
	}

}

void SceneManager::initalize(SDL_Renderer * theRenderer, vector<LPCSTR> theTxt)
{
	load("mainMenu");

	player->initalize();
	boss->initalize({ 875, 750 });
	level.initalize(theTxtMgr, theTxt);

	//Play theme music.
	soundMgr->getSnd("mainMenu")->play(-1);
}

void SceneManager::update()
{
	if (curScene == "mainMenu" || curScene == "controls" || curScene == "credits" || curScene == "win" || curScene == "gameOver") {
		for (unsigned int i = 0; i < buttons.size(); i++) {
			buttons[i].update();
		}
		if (control->down("escapeOnce")) control->setLooping(false);
	}
	if (curScene == "level") {
		player->update();
		level.update();
		boss->update();

		if (player->getHealth() <= 0) load("gameOver");
		if (boss->getHealth() <= 0) load("win");

		//Quit level
		if (control->down("escapeOnce")) {
			saveFile();
			continuing = true;
			load("mainMenu");
		}
	}
}

void SceneManager::render(SDL_Window * theSDLWND, SDL_Renderer * theRenderer, vector<LPCSTR> theTxt)
{
	//Render current scene's elements.
	if (curScene == "mainMenu" || curScene == "controls" || curScene == "credits" || curScene == "win" || curScene == "gameOver") {
		scene.render(theRenderer, &scene.getSpriteDimensions(), &scene.getSpritePos(), scene.getSpriteRotAngle(), &scene.getSpriteCentre(), scene.getSpriteScale());
		for (unsigned int i = 0; i < buttons.size(); i++) {
			buttons[i].renderBoth(theSDLWND, theRenderer, theTxtMgr, theTxt);
		}
	}
	if (curScene == "level") {
		level.render(theSDLWND, theRenderer, theTxtMgr, theTxt);
		boss->render(theRenderer);
		player->render(theRenderer);
	}

	//Render score
	if (curScene == "level" || curScene == "win" || curScene == "gameOver") {
		string sScore = "Score: " + to_string(player->getScore());
		LPCSTR csScore = sScore.c_str();

		if (theTxtMgr->getTexture("Score") != NULL) theTxtMgr->deleteTexture("Score");

		theTxtMgr->addTexture("Score", fontMgr->getFont("gameOver")->createTextTexture(theRenderer, csScore, SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
		cTexture* txtScore = theTxtMgr->getTexture("Score");
		SDL_Rect txtScorePos = { 10, 10, txtScore->getTextureRect().w, txtScore->getTextureRect().h };
		txtScore->renderTexture(theRenderer, txtScore->getTexture(), &txtScore->getTextureRect(), &txtScorePos, { 1, 1 });
	}
	//Save / Load Notification
	if (notiSave && notiTimer > 0) {
		notiTimer--;
		string sNotiSave = "Game saved!";
		LPCSTR csNotiSave = sNotiSave.c_str();

		if (theTxtMgr->getTexture("notiSave") != NULL) theTxtMgr->deleteTexture("notiSave");

		theTxtMgr->addTexture("notiSave", fontMgr->getFont("gameOverLarge")->createTextTexture(theRenderer, csNotiSave, SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
		cTexture* txtNotiSave = theTxtMgr->getTexture("notiSave");
		SDL_Rect txtNotiSavePos = { WINDOW_WIDTH / 2 - txtNotiSave->getTextureRect().w / 2, WINDOW_HEIGHT - 120, txtNotiSave->getTextureRect().w, txtNotiSave->getTextureRect().h };
		txtNotiSave->renderTexture(theRenderer, txtNotiSave->getTexture(), &txtNotiSave->getTextureRect(), &txtNotiSavePos, { 1, 1 });
	}
	if (notiLoad && notiTimer > 0) {
		notiTimer--;
		string sNotiLoad = "Game loaded!";
		LPCSTR csNotiLoad = sNotiLoad.c_str();

		if (theTxtMgr->getTexture("notiLoad") != NULL) theTxtMgr->deleteTexture("notiLoad");

		theTxtMgr->addTexture("notiLoad", fontMgr->getFont("gameOverLarge")->createTextTexture(theRenderer, csNotiLoad, SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));
		cTexture* txtNotiLoad = theTxtMgr->getTexture("notiLoad");
		SDL_Rect txtNotiLoadPos = { WINDOW_WIDTH / 2 - txtNotiLoad->getTextureRect().w / 2, WINDOW_HEIGHT - 120, txtNotiLoad->getTextureRect().w, txtNotiLoad->getTextureRect().h };
		txtNotiLoad->renderTexture(theRenderer, txtNotiLoad->getTexture(), &txtNotiLoad->getTextureRect(), &txtNotiLoadPos, { 1, 1 });
	}
	
}

void SceneManager::resetOneLoad()
{
	oneLoad = false;
}

//Save savedata.
void SceneManager::saveFile()
{
	notiSave = true;
	notiLoad = false;
	notiTimer = 200;
	saveGame.open("Resources\\savegame.dat");
	if (saveGame.is_open())
	{
		//Camera X
		saveGame << control->getCameraPos().x << endl;
		//Camera Y
		saveGame << control->getCameraPos().y << endl;
		//Boss Y
		saveGame << boss->getPosY() << endl;
		//Player health
		saveGame << player->getHealth() << endl;
		//Boss health
		saveGame << boss->getHealth() << endl;
		//Score
		saveGame << player->getScore() << endl;
		saveGame.close();
	}
	else cout << "Unable to open savegame.dat\n";
}

//Load savedata.
void SceneManager::loadFile()
{
	notiLoad = true;
	notiSave = false;
	notiTimer = 200;
	line = 0;
	string sLine;
	saveGame.open("Resources\\savegame.dat");
	if (saveGame.is_open())
	{
		while (getline(saveGame, sLine))
		{
			loadFileIter(sLine);
		}
		saveGame.close();
	}
	else cout << "Unable to open savegame.dat\n";
}

//Load each line of savedata.
void SceneManager::loadFileIter(string sLine)
{
	switch(line) {
	//Camera X
	case 0:
		control->setCameraPos({ stof(sLine), 0.0f });
		break;
	//Camera Y
	case 1:
		control->setCameraPos({ (float)control->getCameraPos().x, stof(sLine) });
		break;
	//Boss Y
	case 2:
		boss->setPosY(stoi(sLine));
		break;
	//Player health
	case 3:
		player->setHealth(stoi(sLine));
		break;
	//Boss health
	case 4:
		boss->setHealth(stoi(sLine));
		break;
	//Score
	case 5:
		player->setScore(stoi(sLine));
		break;
	default:
		break;
	}
	line++;
}