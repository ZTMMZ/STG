#include "BaseLayer.h"
#include "AppMacros.h"
USING_NS_CC;

bool BaseLayer:: init(){
	if(!Layer::init())
	{
		return false;
	}
	return true;
	
}
CCSize BaseLayer::getVisibleSize(){
	return Director::getInstance()->getVisibleSize();
}
CCPoint BaseLayer::getOrigin(){
	return Director::getInstance()->getVisibleOrigin();
}
void BaseLayer::setBackgroundSprite(const char* textureName,int frame){
	Sprite* spbk=Sprite::create(textureName);
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);
	this->addChild(spbk,frame);
}
void BaseLayer::setBackgroundSprite(const char* textureName,int frame,int tag){
	Sprite* spbk=Sprite::create(textureName);
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);
	spbk->setTag(tag);
	this->addChild(spbk,frame);

}
void BaseLayer::setBackgroundSprite(const char* textureName,int frame,int tag,CCPoint move){
	Sprite* spbk=Sprite::create(textureName);
	spbk->setPosition(Point(move.x,move.y));
	spbk->setAnchorPoint(Point::ZERO);
	spbk->setTag(tag);
	this->addChild(spbk,frame);
}
