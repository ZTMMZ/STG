#ifndef __GAMECLEAR_LAYER_H__
#define __GAMECLEAR_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class GameClearLayer :public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(GameClearLayer);
	//ÉèÖÃ´¥Ãþ¿ØÖÆ
	void setupTouchControl();
	//´¥Ãþ¿ØÖÆ
	bool onTouchBegan(Touch *touch, Event *unused_event);
	//·µ»Ø°´¼ü¼àÌý
	void onTouchBackBtn();
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
};
#endif // __GAMECLEAR_LAYER_H__
