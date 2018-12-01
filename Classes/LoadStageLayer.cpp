#include "LoadStageLayer.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include <thread>
#include <mutex>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "platform/android/jni/JniHelper.h"
#include <jni.h> 
#endif 

USING_NS_CC;

Scene* LoadStageLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = LoadStageLayer::create();
    scene->addChild(layer);
    return scene;
}

bool LoadStageLayer::init()
{
    if ( !Layer::init() ){return false;}

	progress=0;
	ParticleSystem * loadingEffect=ParticleSystemQuad::create("texture/loading/loadingeffect.plist");
	loadingEffect->setTexture(TextureCache::sharedTextureCache()->addImage("texture/loading/loadingeffect.plist.png"));
	loadingEffect->setPosition(getVisibleSize().width-210,150);
	this->addChild(loadingEffect, 1);

	auto nowLoading=Sprite::create("texture/loading/nowloading.png");
	nowLoading->setAnchorPoint(Point(1,0));
	nowLoading->setPosition(getVisibleSize().width-60,60);
	this->addChild(nowLoading,2);

	loadDone = false; 
	std::thread sThread(&LoadStageLayer::loadingThread,this,this);
	sThread.join();
	this->scheduleUpdate(); 

	//�����Ի�
	Director::getInstance()->getTextureCache()->addImageAsync("texture/player/player0.png",CC_CALLBACK_1(LoadStageLayer::plistImageAsyncCallback, 
		this,"texture/player/player0.plist"));
	//���صл�
	Director::getInstance()->getTextureCache()->addImageAsync("texture/enemy/enemy0.png",CC_CALLBACK_1(LoadStageLayer::plistImageAsyncCallback, 
		this,"texture/enemy/enemy0.plist"));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/enemy/enemy1.png",CC_CALLBACK_1(LoadStageLayer::plistImageAsyncCallback, 
		this,"texture/enemy/enemy1.plist"));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/boss/boss0.png", CC_CALLBACK_1(LoadStageLayer::plistImageAsyncCallback,
		this, "texture/boss/boss0.plist"));
	//�����Ի��ӵ�
	Director::getInstance()->getTextureCache()->addImageAsync("texture/player/bullet.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//���صл��ӵ�0
	Director::getInstance()->getTextureCache()->addImageAsync("texture/bullet/eBullet0_0.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//���صл��ӵ�1
	Director::getInstance()->getTextureCache()->addImageAsync("texture/bullet/eBullet1_0.png", CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//�����ж���ͼ��
	Director::getInstance()->getTextureCache()->addImageAsync("texture/player/point.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//���ش󱳾�ͼƬ
	Director::getInstance()->getTextureCache()->addImageAsync("texture/game/stage_1/bg_00.jpg",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//���غ�ͼƬ
	Director::getInstance()->getTextureCache()->addImageAsync("texture/game/stage_1/bg_01.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//���ط���ͼƬ
	Director::getInstance()->getTextureCache()->addImageAsync("texture/game/stage_1/bg_02.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//����ǰ��ͼƬ
	Director::getInstance()->getTextureCache()->addImageAsync("texture/game/stage_1/bg_03.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//���عؿ�����
	Director::getInstance()->getTextureCache()->addImageAsync("texture/game/stage_1/stage_title.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//���ر�ը��Ч�ļ�
	Director::getInstance()->getTextureCache()->addImageAsync("texture/enemy/explodingring.plist.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//����Gameover����
	Director::getInstance()->getTextureCache()->addImageAsync("texture/gameover/bg_00.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	//����Gameover����
	Director::getInstance()->getTextureCache()->addImageAsync("texture/gameover/title.png",CC_CALLBACK_0(LoadStageLayer::imageAsyncCallback, this));
	return true;
}

void LoadStageLayer::loadingThread(LoadStageLayer* context)
{
	LoadStageLayer* scene = context; 

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	JavaVM *vm; 
    JNIEnv *env; 
    vm = JniHelper::getJavaVM(); 
    JavaVMAttachArgs thread_args; 
    thread_args.name = "Stage Load"; 
    thread_args.version = JNI_VERSION_1_4; 
    thread_args.group = NULL; 
    vm->AttachCurrentThread(&env, &thread_args); 
	#endif

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/se/se_explode.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/se/se_playershot.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/se/se_pause.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgm/bgm_stage1_0.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgm/bgm_stage1_1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgm/prayers_score.mp3");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	vm->DetachCurrentThread(); 
	#endif

    scene->setLoadIndicator(true); 
}
void LoadStageLayer::update(float dt) 
{ 
	if (getLoadIndicator()&&progress==16){
		this->scheduleOnce(schedule_selector(LoadStageLayer::jumpCallback),1.5f);
    } 

} 
bool LoadStageLayer::getLoadIndicator() 
{ 
    bool flag; 
    mutex.lock();
    flag = loadDone; 
	mutex.unlock();
    return flag; 
}   
void LoadStageLayer::setLoadIndicator(bool flag) 
{ 
	mutex.lock();
    loadDone = flag; 
    mutex.unlock();
    return; 
}
void LoadStageLayer::imageAsyncCallback(){
	progress++;
}
void LoadStageLayer::plistImageAsyncCallback(Texture2D* texture,const std::string &plistPath){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath, texture);  
	progress++;
}
void LoadStageLayer::jumpCallback(float t){
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f,GameLayer::createScene()));
}
