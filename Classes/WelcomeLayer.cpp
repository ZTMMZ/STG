#include "WelcomeLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* WelcomeLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = WelcomeLayer::create();
    scene->addChild(layer);
    return scene;
}

bool WelcomeLayer:: init(){
	if(!Layer::init()){return false;}

	//²¥·Å±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm/bgm_menu.mp3",true);

    Sprite* sp0=Sprite::create("texture/welcome/sp_00.png");
	sp0->setPosition(Point(getVisibleSize().width/2 + getOrigin().x, getVisibleSize().height/2 + getOrigin().y));
	sp0->setOpacity(0);
	this->addChild(sp0,0);
	sp0->runAction(Sequence::create(FadeIn::create(2),DelayTime::create(2),FadeOut::create(2),CallFunc::create(this, callfunc_selector(WelcomeLayer::gotoMenu)),NULL));
	//223
	return true;

}
void WelcomeLayer::gotoMenu(){
	Director::sharedDirector()->replaceScene(TransitionFade::create(0.5f, MenuLayer::createScene()));
}