#ifndef __BOSS_MODEL_H__
#define __BOSS_MODEL_H__

#include "cocos2d.h"
#include "params\BossParams.h"
USING_NS_CC;

class BossModel:public cocos2d::Node{
public:
	BossModel(int type);
	~BossModel();
	bool init();
	static BossModel* createBoss(int type);
	CC_SYNTHESIZE_READONLY(CCSprite*, boss, BossSprite );

	void bossDie();
	void bossExplode();
	void overScreen();
	void releaseBoss(float t);
	void bossHit();
	void deleteBossInArray();
	void addBullet(float t);
	void moveBullet(float t);
	void deleteBBullet(Object *data);
	void bBulletDie(Sprite *bBullet);
	void bBulletExplode(Object *data);
	void isBossDie(float t);
public:
	SpriteBatchNode* bBulletsBatchNode;
    Vector<Sprite *> bBullets;
private:
	BossParams bossParams;

	FiniteTimeAction *pathAction;//µ–»À“∆∂ØπÏº£
	RepeatForever *frameAction;//µ–»À÷°∂Øª≠
	FiniteTimeAction *comeInAction;
	
};
#endif // __BOSS_MODEL_H__