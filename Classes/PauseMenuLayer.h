#ifndef __PAUSE_MENU_LAYER_H__
#define __PAUSE_MENU_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"

#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class PauseMenuLayer:public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(PauseMenuLayer);
	
	void ButtontouchEvent(Object *pSender, TouchEventType type);
};
#endif // __PAUSE_MENU_LAYER_H__
