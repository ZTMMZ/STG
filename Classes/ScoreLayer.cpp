#include "ScoreLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "utils/DBUtil.h"

#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* ScoreLayer::createScene()
{
    auto scene = Scene::create();
	auto layer = ScoreLayer::create();
    scene->addChild(layer);
    return scene;
}

bool ScoreLayer::init(){
	isAlertPop = false;

	if(!Layer::init()){return false;}
	ScoreLayer::onTouchBackBtn();
	setBackgroundSprite("texture/score/bg_00.jpg",0);

	Sprite* title = Sprite::create("texture/score/title.png");
	title->setPosition(Point(360, 1090));
	this->addChild(title,1);

	listview = ListView::create();
	listview->setTouchEnabled(true);
	listview->setSize(Size(630,450));
	listview->setPosition(Point(45, 390));
	listview->setDirection(SCROLLVIEW_DIR_BOTH);

	Layout *widget = Layout::create();
	widget->setSize(Size(630, 45));
	widget->setPosition(Point(45, 900));

	Label* noLabel = Label::create("0", "fonts/miniswb.ttf", 40);
	noLabel->setString("No.");
	noLabel->setPosition(Point(0, 0));
	noLabel->setAnchorPoint(Point::ZERO);
	widget->addChild(noLabel);

	Label* nameLabel = Label::create("0", "fonts/miniswb.ttf", 40);
	nameLabel->setString("Name");
	nameLabel->setPosition(Point(90, 0));
	nameLabel->setAnchorPoint(Point::ZERO);
	widget->addChild(nameLabel);

	Label* scoreLabel = Label::create("0", "fonts/miniswb.ttf", 40);
	scoreLabel->setString("Score");
	scoreLabel->setPosition(Point(250, 0));
	scoreLabel->setAnchorPoint(Point::ZERO);
	widget->addChild(scoreLabel);

	Label* timeLabel = Label::create("0", "fonts/miniswb.ttf", 40);
	timeLabel->setString("DateTime");
	timeLabel->setPosition(Point(440, 0));
	timeLabel->setAnchorPoint(Point::ZERO);
	widget->addChild(timeLabel);

	addChild(widget);

	if (DBUtil::sharedDB()->openDB("save.db"))  {
		DBUtil::sharedDB()->createTable("create table playerinfo( ID integer primary key autoincrement, playername nvarchar(32), playerscores int, time timestamp default(datetime('now','localtime')))");
		playerInfos = DBUtil::sharedDB()->getPlayerInfo();
		DBUtil::sharedDB()->closeDB();

		std::vector<std::string> playerInfo = playerInfos.at(0);
		int row = atoi(playerInfo.at(0).c_str());

		for (int i = 0; i<row; i++) {
			std::vector<std::string> playerInfo = playerInfos.at(i + 1);

			Layout *widget = Layout::create();
			widget->setSize(Size(getVisibleSize().width, getVisibleSize().height / 20));

			Label* noLabel = Label::create("0", "fonts/miniswb.ttf", 32);
			noLabel->setString(String::createWithFormat("%d", i + 1)->_string);
			noLabel->setPosition(Point(0, 20));
			noLabel->setAnchorPoint(Point::ZERO);
			widget->addChild(noLabel);

			Label* nameLabel = Label::create("0", "fonts/stzhongs.ttf", 30);
			nameLabel->setString(playerInfo.at(1));
			nameLabel->setPosition(Point(90, 20));
			nameLabel->setAnchorPoint(Point::ZERO);
			widget->addChild(nameLabel);

			Label* scoreLabel = Label::create("0", "fonts/miniswb.ttf", 32);
			scoreLabel->setString(playerInfo.at(2));
			scoreLabel->setPosition(Point(250, 20));
			scoreLabel->setAnchorPoint(Point::ZERO);
			widget->addChild(scoreLabel);

			Label* timeLabel = Label::create("0", "fonts/miniswb.ttf", 32);
			timeLabel->setString(playerInfo.at(3));
			timeLabel->setPosition(Point(440, 20));
			timeLabel->setAnchorPoint(Point::ZERO);
			widget->addChild(timeLabel);

			listview->pushBackCustomItem(widget);
		}
	}
	
	this->addChild(listview);

	buttonReset = Button::create();
	buttonReset->setTouchEnabled(true);
	buttonReset->loadTextures("texture/score/button/resetbtn0.png", "texture/score/button/resetbtn1.png", "");
	buttonReset->setPosition(Point(360, 220));
	buttonReset->addTouchEventListener(this, toucheventselector(ScoreLayer::ButtontouchEvent));
	this->addChild(buttonReset,1,0);

	DrawNode* line = DrawNode::create();
	Color4B lineColor = Color4B(136, 178, 195, 76);
	Point rect[4] = { Point(25, 880), Point(690, 880), Point(690, 878), Point(25, 878) };
	line->drawPolygon(rect, 4, Color4F(lineColor), 0, Color4F(lineColor));
	line->setPosition(Point::ZERO);
	this->addChild(line,2);

	return true;

}

void ScoreLayer::onTouchBackBtn(){
	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(ScoreLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	
}
void ScoreLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");

	if (!isAlertPop){
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm/bgm_menu.mp3", true);
		Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
	}
	else{
		cancelReset();
	}
}

void ScoreLayer::ButtontouchEvent(Object *pSender, TouchEventType type){
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Button* button = (Button*)pSender;
		if (button->getTag() == 0){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
			createAlert();
		}
		else if (button->getTag() == 1){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
			okReset();
		}
		else if (button->getTag() == 2){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
			cancelReset();
		}
	}
}
void ScoreLayer::cancelReset(){
	createAlert();
	CCLOG("Cancel");
}
void ScoreLayer::okReset(){
	if (DBUtil::sharedDB()->openDB("save.db"))  {
		DBUtil::sharedDB()->clearTable("playerinfo");
		listview->removeAllChildren();
	}
	createAlert();
	CCLOG("OK");
}
void ScoreLayer::createAlert(){
	if (!isAlertPop){
		isAlertPop = true;
		buttonReset->setTouchEnabled(false);
		listview->setTouchEnabled(false);
		alert = Layout::create();
		
		Sprite* alertBg = Sprite::create("texture/score/alert_bg.png");
		alertBg->setAnchorPoint(Point::ZERO);
		alertBg->setPosition(Point::ZERO);
		alertBg->setOpacity(0);
		alertBg->runAction(FadeIn::create(0.2f));
		alert->addChild(alertBg, 0);

		Sprite* alertText = Sprite::create("texture/score/alert_text.png");
		alertText->setPosition(Point(360,735));
		alertText->setOpacity(0);
		alertText->runAction(FadeIn::create(0.3f));
		alert->addChild(alertText, 0);

		Button* buttonOK = Button::create();
		buttonOK->setTouchEnabled(true);
		buttonOK->loadTextures("texture/score/button/okbtn0.png", "texture/score/button/okbtn1.png", "");
		buttonOK->setPosition(Point(160,540));
		buttonOK->addTouchEventListener(this, toucheventselector(ScoreLayer::ButtontouchEvent));
		buttonOK->setOpacity(0);
		buttonOK->runAction(FadeIn::create(0.2f));
		alert->addChild(buttonOK, 0, 1);

		Button* buttonCancel = Button::create();
		buttonCancel->setTouchEnabled(true);
		buttonCancel->loadTextures("texture/score/button/cancelbtn0.png", "texture/score/button/cancelbtn1.png", "");
		buttonCancel->setPosition(Point(560, 540));
		buttonCancel->addTouchEventListener(this, toucheventselector(ScoreLayer::ButtontouchEvent));
		buttonCancel->setOpacity(0);
		buttonCancel->runAction(FadeIn::create(0.2f));
		alert->addChild(buttonCancel, 0, 2);

		this->addChild(alert,999);
	}
	else{
		isAlertPop = false;
		buttonReset->setTouchEnabled(true);
		listview->setTouchEnabled(true);
		alert->removeFromParent();
	}
}