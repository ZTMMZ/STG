#include "AppDelegate.h"
#include "AppMacros.h"
#include "LoadLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
   
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("War");
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(designResolutionSize.width,designResolutionSize.height, kResolutionShowAll);
	//glview->setFrameSize(720,1280);
    //director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

	auto scene = LoadLayer::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
