#ifndef __LOADSTAGE_LAYER_H__
#define __LOADSTAGE_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"
 
class LoadStageLayer:public BaseLayer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadStageLayer);
	void loadingThread(LoadStageLayer* context);
	void update(float dt);
	bool getLoadIndicator();
	void setLoadIndicator(bool flag);
	void imageAsyncCallback();
	void plistImageAsyncCallback(cocos2d::Texture2D* texture,const std::string &plistPath);
	void jumpCallback(float t);
private:
	bool loadDone;
	std::mutex mutex;
	int progress;
};

#endif // __LOADSTAGE_LAYER_H__
