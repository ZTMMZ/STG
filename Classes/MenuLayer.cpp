#include "MenuLayer.h"
#include "GameLayer.h"
#include "ScoreLayer.h"
#include "HelpLayer.h"
#include "ConfigLayer.h"
#include "LoadStageLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MenuLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MenuLayer::init()
{
	
	//超类的init方法
    if ( !Layer::init() ){return false;}

	//CCSpriteFrameCache *frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
	//frameCache->addSpriteFramesWithFile("texture/menu/menuitem.plist");

	//新增菜单条目
	Sprite* startBtnNormal = Sprite::createWithSpriteFrameName("menuitem0_0.png");
    Sprite* startBtnPressed = Sprite::createWithSpriteFrameName("menuitem0_1.png");
    Sprite* startBtnDisabled = Sprite::createWithSpriteFrameName("menuitem0_1.png");
	MenuItemSprite* startBtn = MenuItemSprite::create(startBtnNormal, startBtnPressed, startBtnDisabled, this,menu_selector(MenuLayer::buttonsCallback));
	startBtn->setTag(0);
	startBtn->setOpacity(0);
	startBtn->setRotation3D(Vec3(90.0f, 0.0f, 0.0f));
	startBtn->runAction(Sequence::create(DelayTime::create(0), FadeIn::create(0.1f), RotateBy::create(0.4f, Vec3(-90.0f, 0.0f, 0.0f)), NULL));
	Sprite* helpBtnNormal = Sprite::createWithSpriteFrameName("menuitem1_0.png");
	Sprite* helpBtnPressed = Sprite::createWithSpriteFrameName("menuitem1_1.png");
	Sprite* helpBtnDisabled = Sprite::createWithSpriteFrameName("menuitem1_1.png");
	MenuItemSprite* helpBtn = MenuItemSprite::create(helpBtnNormal, helpBtnPressed, helpBtnDisabled, this, menu_selector(MenuLayer::buttonsCallback));
	helpBtn->setTag(1);
	helpBtn->setOpacity(0);
	helpBtn->setRotation3D(Vec3(90.0f, 0.0f, 0.0f));
	helpBtn->runAction(Sequence::create(DelayTime::create(0.1f), FadeIn::create(0.1f), RotateBy::create(0.4f, Vec3(-90.0f, 0.0f, 0.0f)), NULL));
	Sprite* scoreBtnNormal = Sprite::createWithSpriteFrameName("menuitem2_0.png");
	Sprite* scoreBtnPressed = Sprite::createWithSpriteFrameName("menuitem2_1.png");
	Sprite* scoreBtnDisabled = Sprite::createWithSpriteFrameName("menuitem2_1.png");
	MenuItemSprite* scoreBtn = MenuItemSprite::create(scoreBtnNormal, scoreBtnPressed, scoreBtnDisabled, this, menu_selector(MenuLayer::buttonsCallback));
	scoreBtn->setTag(2);
	scoreBtn->setOpacity(0);
	scoreBtn->setRotation3D(Vec3(90.0f, 0.0f, 0.0f));
	scoreBtn->runAction(Sequence::create(DelayTime::create(0.2f), FadeIn::create(0.1f), RotateBy::create(0.4f, Vec3(-90.0f, 0.0f, 0.0f)), NULL));
	Sprite* configBtnNormal = Sprite::createWithSpriteFrameName("menuitem3_0.png");
	Sprite* configBtnPressed = Sprite::createWithSpriteFrameName("menuitem3_1.png");
	Sprite* configBtnDisabled = Sprite::createWithSpriteFrameName("menuitem3_1.png");
	MenuItemSprite* configBtn = MenuItemSprite::create(configBtnNormal, configBtnPressed, configBtnDisabled, this, menu_selector(MenuLayer::buttonsCallback));
	configBtn->setTag(3);
	configBtn->setOpacity(0);
	configBtn->setRotation3D(Vec3(90.0f, 0.0f, 0.0f));
	configBtn->runAction(Sequence::create(DelayTime::create(0.3f), FadeIn::create(0.1f), RotateBy::create(0.4f, Vec3(-90.0f, 0.0f, 0.0f)), NULL));
	Sprite* exitBtnNormal = Sprite::createWithSpriteFrameName("menuitem4_0.png");
	Sprite* exitBtnPressed = Sprite::createWithSpriteFrameName("menuitem4_1.png");
	Sprite* exitBtnDisabled = Sprite::createWithSpriteFrameName("menuitem4_1.png");
	MenuItemSprite* exitBtn = MenuItemSprite::create(exitBtnNormal, exitBtnPressed, exitBtnDisabled, this, menu_selector(MenuLayer::buttonsCallback));
	exitBtn->setTag(4);
	exitBtn->setOpacity(0);
	exitBtn->setRotation3D(Vec3(90.0f, 0.0f, 0.0f));
	exitBtn->runAction(Sequence::create(DelayTime::create(0.4f), FadeIn::create(0.1f), RotateBy::create(0.4f, Vec3(-90.0f, 0.0f, 0.0f)), NULL));
	//创建菜单
	Menu* pMenu = Menu::create(startBtn, helpBtn, scoreBtn, configBtn, exitBtn, NULL);
	pMenu->setPosition(Point(getVisibleSize().width/2 ,getVisibleSize().height*0.35));
	pMenu->alignItemsVerticallyWithPadding(30);
	this->addChild(pMenu,2);

	ParticleSystem * menuEffect = ParticleSystemQuad::create("texture/menu/menueffect.plist");
	menuEffect->setTexture(TextureCache::sharedTextureCache()->addImage("texture/menu/menueffect.plist.png"));
	menuEffect->setPosition(getVisibleSize().width/2,-400);
	this->addChild(menuEffect, 1);

	//移除帧缓存
	//SpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("menuitem.plist");

	////设置滚动背景
	//setBackgroundSprite("texture/menu/bg_01.png",1,0);
	//setBackgroundSprite("texture/menu/bg_01.png",1,1,Point(0,getVisibleSize().height));
	//setBackgroundSprite("texture/menu/bg_01.png",1,2,Point(-getVisibleSize().width,getVisibleSize().height));
	//setBackgroundSprite("texture/menu/bg_01.png",1,3,Point(-getVisibleSize().width,0));
	//this->schedule(schedule_selector(MenuLayer::moveBackground));

	//新建背景
	setBackgroundSprite("texture/menu/bg_00.jpg",0);
    return true;
}


void MenuLayer::buttonsCallback(Ref* pSender)
{
	MenuItem * thisItem=(MenuItem *)pSender;

	switch(thisItem->getTag()){
	case 0: 
		CCLOG( "start game ");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::sharedDirector()->pushScene(TransitionFade::create(0.5f, LoadStageLayer::createScene()));
		break;
	case 1:
		CCLOG( "help");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
		Director::sharedDirector()->pushScene(TransitionFade::create(0.5f, HelpLayer::createScene()));
		break;
	case 2:
		CCLOG( "score");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
		Director::sharedDirector()->pushScene(TransitionFade::create(0.5f, ScoreLayer::createScene()));
		break;
	case 3:
		CCLOG("config");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
		Director::sharedDirector()->pushScene(TransitionFade::create(0.5f, ConfigLayer::createScene()));
		break;
	case 4:
		CCLOG( "exit");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
#if	(CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
#endif
		Director::getInstance()->end();
#if	(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
}

//void MenuLayer::moveBackground(float t){
//	//背景滚动
//	//获取背景精灵
//	auto spbkr0 = this->getChildByTag(0);
//	auto spbkr1 = this->getChildByTag(1);
//	auto spbkr2 = this->getChildByTag(2);
//	auto spbkr3 = this->getChildByTag(3);
//	//向下移动背景精灵A
//	spbkr0->setPosition(Point(spbkr0->getPositionX()+1.8,spbkr0->getPositionY()-3.2));
//	//当背景精灵A移出场景时，复位
//	if(spbkr0->getPositionX()>spbkr0->getContentSize().width)
//	{
//		spbkr0->setPosition(Point::ZERO);
//	}
//
//	spbkr1->setPosition(Point(spbkr0->getPositionX(),spbkr0->getPositionY()+spbkr0->getContentSize().height));
//	spbkr2->setPosition(Point(spbkr0->getPositionX()-spbkr0->getContentSize().width,spbkr0->getPositionY()+spbkr0->getContentSize().height));
//	spbkr3->setPosition(Point(spbkr0->getPositionX()-spbkr0->getContentSize().width,spbkr0->getPositionY()));
//}
