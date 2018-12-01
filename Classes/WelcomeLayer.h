#ifndef __WELCOME_LAYER_H__
#define __WELCOME_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class WelcomeLayer:public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	void gotoMenu();
};
#endif // __WELCOME_LAYER_H__
