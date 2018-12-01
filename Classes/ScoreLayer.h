#ifndef __SCORE_LAYER_H__
#define __SCORE_LAYER_H__

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

class ScoreLayer :public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(ScoreLayer);

	//·µ»Ø°´¼ü¼àÌý
	void onTouchBackBtn();
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
	void ButtontouchEvent(Object *pSender, TouchEventType type);
	void createAlert();
	void cancelReset();
	void okReset();
	bool isAlertPop;
private:
	std::vector<std::vector<std::string>> playerInfos;
	Button* buttonReset;
	ListView *listview;
	Layout* alert;
};
#endif // __SCORE_LAYER_H__
