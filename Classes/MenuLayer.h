#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class MenuLayer:public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void buttonsCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(MenuLayer);
	/*void moveBackground(float t);*/
};

#endif // __MENU_LAYER_H__
