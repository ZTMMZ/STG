#ifndef __SCORERECODER_LAYER_H__
#define __SCORERECODER_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "utils/DBUtil.h"

#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class ScoreRecoderLayer :public BaseLayer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(ScoreRecoderLayer);

	// TextField´¥Ãþ
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	//·µ»Ø°´¼ü¼àÌý
	void onTouchBackBtn();
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
	void ButtontouchEvent(Object *pSender, TouchEventType type);
	std::string score;
private:
	TextFieldTTF* textField;
	Label* scoreLabel;
	
};
#endif // __SCORERECODER_LAYER_H__
