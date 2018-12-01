#ifndef __ENEMY_MODEL_H__
#define __ENEMY_MODEL_H__

#include "cocos2d.h"
#include "params\EnemyParams.h"
USING_NS_CC;

class EnemyModel:public cocos2d::Node{
public:
	EnemyModel(int type);
	~EnemyModel();
	bool init();
	static EnemyModel* createEnemy(int type);
	CC_SYNTHESIZE_READONLY(CCSprite*, enemy, EnemySprite );

	void enemyDie();
	void enemyExplode();
	void overScreen();
	void releaseEnemy(float t);
	void enemyHit();
	void createPoints(int i);
	void deleteEnemyInArray();
	
public:
	//SpriteBatchNode* eBulletsBatchNode;
    //Vector<Sprite *> eBullets; 
private:
	EnemyParams enemyParams;

	FiniteTimeAction *pathAction;//µ–»À“∆∂ØπÏº£
	RepeatForever *frameAction;//µ–»À÷°∂Øª≠
	
	
};
#endif // __ENEMY_MODEL_H__