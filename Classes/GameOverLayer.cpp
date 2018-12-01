#include "GameOverLayer.h"
#include "GameLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
#include "ScoreRecoderLayer.h"
USING_NS_CC;

Scene* GameOverLayer::createScene()
{
    auto scene = Scene::create();
	auto layer = GameOverLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverLayer::init(){
	if (!Layer::init()){
		return false;
	}
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm/prayers_score.mp3", true);

		Sprite* gameover_bg = Sprite::create("texture/gameover/bg_00.png");
		Sprite* gameover_title = Sprite::create("texture/gameover/title.png");

		gameover_bg->setPosition(Point::ZERO);
		gameover_bg->setAnchorPoint(Point::ZERO);
		gameover_bg->setOpacity(40);
		this->addChild(gameover_bg, 0, 0);

		gameover_title->setPosition(Point(360,670));
		gameover_title->setOpacity(0);
		this->addChild(gameover_title, 1, 1);

		gameover_bg->runAction(FadeIn::create(2.0f));
		gameover_title->runAction(FadeIn::create(0.7f));

//		GameOverLayer::onTouchBackBtn();
		GameOverLayer::setupTouchControl();

		return true;

}
void GameOverLayer::onTouchBackBtn(){
	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameOverLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}
void GameOverLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
		Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
}
//设置触摸控制
void GameOverLayer::setupTouchControl(){

	EventListenerTouchOneByOne * event = EventListenerTouchOneByOne::create();
	event->setSwallowTouches(true);
	event->onTouchBegan = CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);

	//注册
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
}

bool GameOverLayer::onTouchBegan(Touch *touch, Event *unused_event){
	Scene* gameScene = (Scene*)this->getParent();
	GameLayer* gameLayer = (GameLayer*)gameScene->getChildByTag(999);
	Label* scoreLabel = (Label*)gameLayer->getChildByTag(500);
	std::string score = scoreLabel->getString();

	Scene* scoreRecoderScene = ScoreRecoderLayer::createScene();
	ScoreRecoderLayer * scoreRecoderLayer = (ScoreRecoderLayer*)(scoreRecoderScene->getChildByTag(999));
	scoreRecoderLayer->score = score;
	Label* scoreLabel2 = (Label*)scoreRecoderLayer->getChildByTag(1);
	scoreLabel2->setString("Your score: "+score);

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, scoreRecoderScene));
	return true;
}
