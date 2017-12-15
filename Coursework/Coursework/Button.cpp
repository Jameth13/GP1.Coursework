#include "Button.h"
#include "cTextureMgr.h"
#include "cSoundMgr.h"
#include "SceneManager.h"

static Control* control = Control::getInstance();
static SceneManager* sceneMgr = SceneManager::getInstance();
static cTextureMgr* theTxtMgr = cTextureMgr::getInstance();
static cSoundMgr* soundMgr = cSoundMgr::getInstance();
static Player* player = Player::getInstance();
static Boss* boss = Boss::getInstance();

//Animate button.
void Button::animate()
{
	timing += 1;

	if (timing < interval / 2) {
		backgroundSprite.setTexture(theTxtMgr->getTexture("button01"));
	}
	if (timing > interval / 2) {
		backgroundSprite.setTexture(theTxtMgr->getTexture("button02"));
	}

	if (timing >= interval) timing = 0;
}

//Give the button the correct texture.
void Button::initalize(string n, SDL_Point p)
{
	name = n;
	pos = p;

	backgroundSprite.setTexture(theTxtMgr->getTexture("button01"));
	backgroundSprite.setSpritePos({ pos.x, pos.y });
	backgroundSprite.setSpriteDimensions(theTxtMgr->getTexture("button01")->getTWidth(), theTxtMgr->getTexture("button01")->getTHeight());

	if (name == "start") {
		textSprite.setTexture(theTxtMgr->getTexture("buttonStart"));
		textSprite.setSpritePos({ pos.x, pos.y });
		textSprite.setSpriteDimensions(theTxtMgr->getTexture("buttonStart")->getTWidth(), theTxtMgr->getTexture("buttonStart")->getTHeight());
	}
	if (name == "back" || name == "backReset") {
		textSprite.setTexture(theTxtMgr->getTexture("buttonBack"));
		textSprite.setSpritePos({ pos.x, pos.y });
		textSprite.setSpriteDimensions(theTxtMgr->getTexture("buttonBack")->getTWidth(), theTxtMgr->getTexture("buttonBack")->getTHeight());
	}
	if (name == "controls") {
		textSprite.setTexture(theTxtMgr->getTexture("buttonControls"));
		textSprite.setSpritePos({ pos.x, pos.y });
		textSprite.setSpriteDimensions(theTxtMgr->getTexture("buttonControls")->getTWidth(), theTxtMgr->getTexture("buttonControls")->getTHeight());
	}
	if (name == "credits") {
		textSprite.setTexture(theTxtMgr->getTexture("buttonCredits"));
		textSprite.setSpritePos({ pos.x, pos.y });
		textSprite.setSpriteDimensions(theTxtMgr->getTexture("buttonCredits")->getTWidth(), theTxtMgr->getTexture("buttonCredits")->getTHeight());
	}
	if (name == "quit") {
		textSprite.setTexture(theTxtMgr->getTexture("buttonQuit"));
		textSprite.setSpritePos({ pos.x, pos.y });
		textSprite.setSpriteDimensions(theTxtMgr->getTexture("buttonQuit")->getTWidth(), theTxtMgr->getTexture("buttonQuit")->getTHeight());
	}
	if (name == "continue") {
		textSprite.setTexture(theTxtMgr->getTexture("buttonContinue"));
		textSprite.setSpritePos({ pos.x, pos.y });
		textSprite.setSpriteDimensions(theTxtMgr->getTexture("buttonContinue")->getTWidth(), theTxtMgr->getTexture("buttonContinue")->getTHeight());
	}
	if (name == "continueLoad") {
		textSprite.setTexture(theTxtMgr->getTexture("buttonContinue"));
		textSprite.setSpritePos({ pos.x, pos.y });
		textSprite.setSpriteDimensions(theTxtMgr->getTexture("buttonContinue")->getTWidth(), theTxtMgr->getTexture("buttonContinue")->getTHeight());
	}
}

//Check if button is clicked and then transition.
void Button::update()
{
	if (control->down("mLeftOnce") && SDL_PointInRect(&control->getMousePos(), &backgroundSprite.getSpritePos()))
	{
		//Play button SFX.
		soundMgr->getSnd("button")->play(0);

		if (name == "start") sceneMgr->load("level");
		if (name == "back") sceneMgr->load("mainMenu");
		if (name == "controls") sceneMgr->load("controls");
		if (name == "credits") sceneMgr->load("credits");
		if (name == "quit") control->setLooping(false);
		if (name == "backReset")
		{
			control->reset();
			player->revive();
			boss->reset();
			sceneMgr->load("mainMenu");
		}
		if (name == "continue")
		{
			player->revive();
			boss->removeAllProjectiles();
			sceneMgr->load("level");
		}
		if (name == "continueLoad")
		{
			//Reset everything and then load.
			control->reset();
			player->revive();
			boss->reset();
			sceneMgr->loadFile();
			sceneMgr->load("level");
		}
	}

	//If mouse is hovering over button, animate.
	if (SDL_PointInRect(&control->getMousePos(), &backgroundSprite.getSpritePos())) {
		animate();
	} else {
		timing = 0;
		animate();
	}
}

//Render both the background sprite and the text sprite.
void Button::renderBoth(SDL_Window * theSDLWND, SDL_Renderer * theRenderer, cTextureMgr * theTxtMgr, vector<LPCSTR> theTxt)
{
	backgroundSprite.render(theRenderer, &backgroundSprite.getSpriteDimensions(), &backgroundSprite.getSpritePos(), backgroundSprite.getSpriteRotAngle(), &backgroundSprite.getSpriteCentre(), backgroundSprite.getSpriteScale());
	textSprite.render(theRenderer, &textSprite.getSpriteDimensions(), &textSprite.getSpritePos(), textSprite.getSpriteRotAngle(), &textSprite.getSpriteCentre(), textSprite.getSpriteScale());
}
