#include "HelpLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"

#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

Scene* HelpLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = HelpLayer::create();
    scene->addChild(layer);
    return scene;
}

bool HelpLayer:: init(){
	if(!Layer::init()){return false;}
	HelpLayer::onTouchBackBtn();
	CCNode *help = CSLoader::createNode("uilayer/help/HelpLayer.csb");
	this->addChild(help);

	return true;

}
void HelpLayer::onTouchBackBtn(){
	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(HelpLayer::onKeyReleased,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}
void HelpLayer::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_cancel.wav");
		Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
}
