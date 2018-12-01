#include "PauseMenuLayer.h"
#include "GameLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"

#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* PauseMenuLayer::createScene()
{
    auto scene = Scene::create();
	auto layer = PauseMenuLayer::create();
    scene->addChild(layer);
    return scene;
}

bool PauseMenuLayer::init(){
	if(!Layer::init()){return false;}

	Sprite* pause_title = Sprite::create("texture/game/pause/title.png");
	pause_title->setPosition(Point(360, 830));
	this->addChild(pause_title);

	Button* buttonCon = Button::create();
	buttonCon->setTouchEnabled(true);
	buttonCon->loadTextures("texture/game/pause/button/conbtn0.png", "texture/game/pause/button/conbtn1.png", "");
	buttonCon->setPosition(Point(360, 650));
	buttonCon->addTouchEventListener(this, toucheventselector(PauseMenuLayer::ButtontouchEvent));
	this->addChild(buttonCon,1,0);

	Button* buttonQuit = Button::create();
	buttonQuit->setTouchEnabled(true);
	buttonQuit->loadTextures("texture/game/pause/button/quitbtn0.png", "texture/game/pause/button/quitbtn1.png", "");
	buttonQuit->setPosition(Point(360, 540));
	buttonQuit->addTouchEventListener(this, toucheventselector(PauseMenuLayer::ButtontouchEvent));
	this->addChild(buttonQuit, 1, 1);
	return true;
}

void PauseMenuLayer::ButtontouchEvent(Object *pSender, TouchEventType type){
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Button* button = (Button*)pSender;
		if (button->getTag() == 0){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
			GameLayer* gameLayer = (GameLayer*)this->getParent();
			gameLayer->gameResume();
			this->removeFromParent();
		}
		else if (button->getTag() == 1){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
			GameLayer* gameLayer = (GameLayer*)this->getParent();
			gameLayer->gameResume();
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm/bgm_menu.mp3", true);
			Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
		}
	}

	
}