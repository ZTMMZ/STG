#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class GameOverLayer :public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(GameOverLayer);
	//ÉèÖÃ´¥Ãþ¿ØÖÆ
	void setupTouchControl();
	//´¥Ãþ¿ØÖÆ
	bool onTouchBegan(Touch *touch, Event *unused_event);
	//·µ»Ø°´¼ü¼àÌý
	void onTouchBackBtn();
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
};
#endif // __GAMEOVER_LAYER_H__
