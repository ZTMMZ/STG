#ifndef __GAMECLEAR_LAYER_H__
#define __GAMECLEAR_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class GameClearLayer :public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(GameClearLayer);
	//���ô�������
	void setupTouchControl();
	//��������
	bool onTouchBegan(Touch *touch, Event *unused_event);
	//���ذ�������
	void onTouchBackBtn();
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
};
#endif // __GAMECLEAR_LAYER_H__
