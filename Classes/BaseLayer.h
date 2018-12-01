#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class BaseLayer:public cocos2d::Layer{
public:
    virtual bool init();
	CREATE_FUNC(BaseLayer);
	Size getVisibleSize();
	Point getOrigin();
	void setBackgroundSprite(const char* textureName,int frame);
	void setBackgroundSprite(const char* textureName,int frame,int tag);
	void setBackgroundSprite(const char* textureName,int frame,int tag,Point move);
};
#endif // __BASE_LAYER_H__
