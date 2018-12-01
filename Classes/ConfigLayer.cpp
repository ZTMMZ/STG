#include "ConfigLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"

#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* ConfigLayer::createScene()
{
    auto scene = Scene::create();
	auto layer = ConfigLayer::create();
    scene->addChild(layer);
    return scene;
}

bool ConfigLayer::init(){
	if(!Layer::init()){return false;}
	CCNode *config = CSLoader::createNode("uilayer/config/ConfigLayer.csb");
	this->addChild(config);
	bgm_v_last = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	bgm_v = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	se_v_last = CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
	se_v = CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();

	bgmSlider = dynamic_cast<Slider*>(config->getChildByTag(UI_SLIDER_BGM));
	bgmSlider->setPercent((int)(bgm_v * 100));
	bgmSlider->addEventListenerSlider(this, sliderpercentchangedselector(ConfigLayer::bgmSliderCallback));
	
	seSlider = dynamic_cast<Slider*>(config->getChildByTag(UI_SLIDER_SE));
	seSlider->setPercent((int)(se_v * 100));
	seSlider->addEventListenerSlider(this, sliderpercentchangedselector(ConfigLayer::seSliderCallback));
	
	applyBtn = dynamic_cast<Button*>(config->getChildByTag(UI_BUTTON_APPLY));
	applyBtn->addTouchEventListener(this, toucheventselector(ConfigLayer::applyCallback));

	defaultBtn = dynamic_cast<Button*>(config->getChildByTag(UI_BUTTON_DEFAULT));
	defaultBtn->addTouchEventListener(this, toucheventselector(ConfigLayer::defaultCallback));

	ConfigLayer::onTouchBackBtn();
	return true;
}

void ConfigLayer::bgmSliderCallback(Ref* sender, SliderEventType type)
{
	switch (type)
	{
		case SLIDER_PERCENTCHANGED:
			bgm_v = (float)(bgmSlider->getPercent())/100;
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(bgm_v);
		break;
	}
}
void ConfigLayer::seSliderCallback(Ref* sender, SliderEventType type)
{
	switch (type)
	{
		case SLIDER_PERCENTCHANGED:
			se_v = (float)(seSlider->getPercent()) / 100;
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(se_v);
		break;
	}
}

void ConfigLayer::applyCallback(Ref* sender, TouchEventType type){
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
		Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
		break;
	}
}

void ConfigLayer::defaultCallback(Ref* sender, TouchEventType type){
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_select.wav");
		bgm_v = 0.5f;
		bgmSlider->setPercent(50);
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(bgm_v);
		se_v = 0.5f;
		seSlider->setPercent(50);
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(se_v);
		break;
	}
}

void ConfigLayer::onTouchBackBtn(){
	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(ConfigLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}
void ConfigLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
	bgm_v = bgm_v_last;
	bgmSlider->setPercent((int)(bgm_v_last * 100));
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(bgm_v_last);
	se_v = se_v_last;
	seSlider->setPercent((int)(se_v_last * 100));
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(se_v_last);
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
}
