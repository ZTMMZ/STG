#ifndef __CONFIG_LAYER_H__
#define __CONFIG_LAYER_H__

#include "BaseLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

const int UI_SLIDER_BGM = 1;
const int UI_SLIDER_SE = 2;
const int UI_BUTTON_APPLY = 3;
const int UI_BUTTON_DEFAULT = 4;
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class ConfigLayer :public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(ConfigLayer);

	void bgmSliderCallback(Ref* sender, SliderEventType type);
	void seSliderCallback(Ref* sender, SliderEventType type);
	void applyCallback(Ref* sender, TouchEventType type);
	void defaultCallback(Ref* sender, TouchEventType type);
	//·µ»Ø°´¼ü¼àÌý
	void onTouchBackBtn();
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
private:
	float bgm_v_last;
	float se_v_last;
	float bgm_v;
	float se_v;
	Slider* bgmSlider;
	Slider* seSlider;
	Button* applyBtn;
	Button* defaultBtn;
};
#endif // __CONFIG_LAYER_H__
