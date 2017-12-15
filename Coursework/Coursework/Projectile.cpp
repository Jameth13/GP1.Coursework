#include "Projectile.h"
#include "Control.h"
#include "Tools.h"

static cTextureMgr* theTxtMgr = cTextureMgr::getInstance();
static Control* control = Control::getInstance();
static Tools* tools = Tools::getInstance();

void Projectile::initalize(SDL_Point p, FPoint traj, LPCSTR name)
{
	speed = 0.25f * control->getDeltaTime();
	int txtWidth = theTxtMgr->getTexture(name)->getTWidth();
	int txtHeight = theTxtMgr->getTexture(name)->getTHeight();

	//Set position and trajectory
	pos = { 0.0f + p.x - control->getCameraPos().x - txtWidth / 2, 0.0f + p.y - control->getCameraPos().y - txtHeight / 2};
	trajectory = traj;
	
	//Set texture
	sprite.setTexture(theTxtMgr->getTexture(name));
	sprite.setSpritePos({ tools->round(pos.x), tools->round(pos.y) });
	sprite.setSpriteDimensions(txtWidth, txtHeight);

}

//Update position
void Projectile::update()
{
	pos = { pos.x + (speed * trajectory.x), pos.y - (speed * trajectory.y) };
	sprite.setSpritePos({control->getCameraPos().x + tools->round(pos.x), tools->round(pos.y) + control->getCameraPos().y});
}

//Render
void Projectile::render(SDL_Renderer* theRenderer)
{
	sprite.render(theRenderer, &sprite.getSpriteDimensions(), &sprite.getSpritePos(), sprite.getSpriteRotAngle(), &sprite.getSpriteCentre(), sprite.getSpriteScale());
}

SDL_Rect Projectile::getPos()
{
	return sprite.getSpritePos();
}
