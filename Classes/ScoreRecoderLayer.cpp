#include "ScoreRecoderLayer.h"
#include "ScoreLayer.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "utils/DBUtil.h"

#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* ScoreRecoderLayer::createScene()
{
    auto scene = Scene::create();
	auto layer = ScoreRecoderLayer::create();
	layer->setTag(999);
    scene->addChild(layer);
    return scene;
}

bool ScoreRecoderLayer::init(){
	if(!Layer::init()){return false;}
	ScoreRecoderLayer::onTouchBackBtn();
	setBackgroundSprite("texture/score/bg_00.jpg",0);

	Label* scoreLabel = Label::create("0", "fonts/miniswb.ttf", 52);
	scoreLabel->setString("0");
	scoreLabel->setPosition(Point(360, 1040));
	scoreLabel->setTag(1);
	this->addChild(scoreLabel);

	textField = CCTextFieldTTF::textFieldWithPlaceHolder("Input Your Name...", "Helvetica", 48);
	textField->setPosition(Point(360, 900));
	this->addChild(textField);
	textField->attachWithIME();

	Button* buttonSubmit = Button::create();
	buttonSubmit->setTouchEnabled(true);
	buttonSubmit->loadTextures("texture/scorerecoder/button/submitbtn0.png", "texture/scorerecoder/button/submitbtn1.png", "");
	buttonSubmit->setPosition(Point(360, 220));
	buttonSubmit->addTouchEventListener(this, toucheventselector(ScoreRecoderLayer::ButtontouchEvent));
	this->addChild(buttonSubmit);

	DrawNode* line = DrawNode::create();
	Color4B lineColor = Color4B(136, 178, 195, 76);
	Point rect[4] = { Point(112, 864), Point(608, 864), Point(608, 860), Point(112, 860) };
	line->drawPolygon(rect, 4, Color4F(lineColor), 0, Color4F(lineColor));
	line->setPosition(Point::ZERO);
	this->addChild(line, 2);

	EventListenerTouchOneByOne * event = EventListenerTouchOneByOne::create();
	event->setSwallowTouches(true);
	event->onTouchBegan = CC_CALLBACK_2(ScoreRecoderLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);

	return true;

}
void ScoreRecoderLayer::onTouchBackBtn(){
	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(ScoreRecoderLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}
void ScoreRecoderLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
		//Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
}
void ScoreRecoderLayer::ButtontouchEvent(Object *pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_ENDED:
		if (DBUtil::sharedDB()->openDB("save.db"))  {
			DBUtil::sharedDB()->createTable("create table playerinfo( ID integer primary key autoincrement, playername nvarchar(32), playerscores int, time timestamp default(datetime('now','localtime')))");
			DBUtil::sharedDB()->insertTable("insert into playerinfo( playername,playerscores) values ( '" + textField->getString() + "', " + score + ") ");
			DBUtil::sharedDB()->closeDB();
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
		Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, ScoreLayer::createScene()));

	}
	
}

bool  ScoreRecoderLayer::onTouchBegan(CCTouch* touch, CCEvent* event){
	bool isClicked = textField->boundingBox().containsPoint(touch->getLocation());
	if (isClicked){
		textField->attachWithIME();
		return true;
	}
	return false;
}