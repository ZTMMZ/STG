#include "GameClearLayer.h"
#include "GameLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "ScoreRecoderLayer.h"
USING_NS_CC;

Scene* GameClearLayer::createScene()
{
    auto scene = Scene::create();
	auto layer = GameClearLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameClearLayer::init(){
	if (!Layer::init()){
		return false;
	}
		
	Sprite* gameclear_bg = Sprite::create("texture/win/bg_00.png");
	Sprite* gameclear_title = Sprite::create("texture/win/title.png");

	gameclear_bg->setPosition(Point::ZERO);
	gameclear_bg->setAnchorPoint(Point::ZERO);
	gameclear_bg->setOpacity(40);
	this->addChild(gameclear_bg, 0, 0);

	gameclear_title->setPosition(Point(360, 670));
	gameclear_title->setOpacity(0);
	this->addChild(gameclear_title, 1, 1);

	gameclear_bg->runAction(FadeIn::create(2.0f));
	gameclear_title->runAction(FadeIn::create(0.7f));

//	GameOverLayer::onTouchBackBtn();
	GameClearLayer::setupTouchControl();

	return true;

}
void GameClearLayer::onTouchBackBtn(){
	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameClearLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}
void GameClearLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
}
//设置触摸控制
void GameClearLayer::setupTouchControl(){

	EventListenerTouchOneByOne * event = EventListenerTouchOneByOne::create();
	event->setSwallowTouches(true);
	event->onTouchBegan = CC_CALLBACK_2(GameClearLayer::onTouchBegan, this);

	//注册
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
}

bool GameClearLayer::onTouchBegan(Touch *touch, Event *unused_event){
	Scene* gameScene = (Scene*)this->getParent();
	GameLayer* gameLayer = (GameLayer*)gameScene->getChildByTag(999);
	Label* scoreLabel = (Label*)gameLayer->getChildByTag(500);
	std::string score = scoreLabel->getString();

	Scene* scoreRecoderScene = ScoreRecoderLayer::createScene();
	ScoreRecoderLayer * scoreRecoderLayer = (ScoreRecoderLayer*)(scoreRecoderScene->getChildByTag(999));
	scoreRecoderLayer->score = score;
	Label* scoreLabel2 = (Label*)scoreRecoderLayer->getChildByTag(1);
	scoreLabel2->setString("Your score: "+score);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm/prayers_score.mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, scoreRecoderScene));
	return true;
}
