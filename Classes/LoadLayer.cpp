#include "LoadLayer.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
#include <thread>
#include <mutex>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "platform/android/jni/JniHelper.h"
#include <jni.h> 
#endif 

USING_NS_CC;

Scene* LoadLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = LoadLayer::create();
    scene->addChild(layer);
    return scene;
}

bool LoadLayer::init()
{
    if ( !Layer::init() ){return false;}

	progress = 0;

	ParticleSystem * loadingEffect=ParticleSystemQuad::create("texture/loading/loadingeffect.plist");
	loadingEffect->setTexture(TextureCache::sharedTextureCache()->addImage("texture/loading/loadingeffect.plist.png"));
	loadingEffect->setPosition(getVisibleSize().width-210,150);
	this->addChild(loadingEffect, 1);

	auto nowLoading=Sprite::create("texture/loading/nowloading.png");
	nowLoading->setAnchorPoint(Point(1,0));
	nowLoading->setPosition(getVisibleSize().width-60,60);
	this->addChild(nowLoading,2);

	loadDone = false; 
	std::thread lThread(&LoadLayer::loadingThread,this,this);
	lThread.join();
	this->scheduleUpdate(); 

	Director::getInstance()->getTextureCache()->addImageAsync("texture/menu/menuitem.png",CC_CALLBACK_1(LoadLayer::plistImageAsyncCallback, this,"texture/menu/menuitem.plist"));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/welcome/sp_00.png",CC_CALLBACK_0(LoadLayer::imageAsyncCallback, this));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/menu/bg_00.jpg",CC_CALLBACK_0(LoadLayer::imageAsyncCallback, this));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/help/bg_00.jpg",CC_CALLBACK_0(LoadLayer::imageAsyncCallback, this));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/score/bg_00.jpg",CC_CALLBACK_0(LoadLayer::imageAsyncCallback, this));
	
	return true;
}

void LoadLayer::loadingThread(LoadLayer* context)
{
	LoadLayer* scene = context; 

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	JavaVM *vm; 
    JNIEnv *env; 
    vm = JniHelper::getJavaVM(); 
    JavaVMAttachArgs thread_args; 
    thread_args.name = "Resource Load"; 
    thread_args.version = JNI_VERSION_1_4; 
    thread_args.group = NULL; 
    vm->AttachCurrentThread(&env, &thread_args); 
	#endif
    
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/se/se_select.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/se/se_cancel.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgm/bgm_menu.mp3");

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	vm->DetachCurrentThread(); 
	#endif

    scene->setLoadIndicator(true); 
}
void LoadLayer::update(float dt) 
{ 
	if (getLoadIndicator()&&progress==5) { 
       this->scheduleOnce(schedule_selector(LoadLayer::jumpCallback),0.5);
    } 

} 
bool LoadLayer::getLoadIndicator() 
{ 
    bool flag; 
    mutex.lock();
    flag = loadDone; 
	mutex.unlock();
    return flag; 
}   
void LoadLayer::setLoadIndicator(bool flag) 
{ 
	mutex.lock();
    loadDone = flag; 
    mutex.unlock();
    return; 
} 
void LoadLayer::imageAsyncCallback(){
	progress++;
}
void LoadLayer::plistImageAsyncCallback(Texture2D* texture,const std::string &plistPath){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath, texture);  
	progress++;
}
void LoadLayer::jumpCallback(float t){
	Director::getInstance()->replaceScene(WelcomeLayer::createScene());
}