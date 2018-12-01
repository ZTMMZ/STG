#ifndef __EBULLET_EJECTOR_H__
#define __EBULLET_EJECTOR_H__

#include "cocos2d.h"
#include "entity/EnemyModel.h"
#include "entity/PlayerFactory.h"
USING_NS_CC;

class EBulletEjector:public cocos2d::Node{
public:
	EBulletEjector(EnemyModel* enemyModel, int type, PlayerFactory* playerFactory);
	~EBulletEjector();
	bool init();
	static EBulletEjector* createEBullet(EnemyModel* enemyModel, int type, PlayerFactory* playerFactory);
	CC_SYNTHESIZE_READONLY(SpriteBatchNode*, eBulletsBatchNode, EBBatchNode );

	
	void eBulletDie(Sprite *eBullet);
	void eBulletExplode(Object *data);	
	void deleteEBullet(Object *data);

	void isEnemyDie(float t);
	void moveBullet(float t);

	void addBullet(float t);
	void isEBulletsEmpty(float t);
	void deleteEjectorInArray();
public:
	Vector<Sprite *> eBullets; 
	EnemyModel* enemyModel;
	PlayerFactory *playerFactory;
	int type;
private:
	int leftBulletNum;
};
#endif // __EBULLET_EJECTOR_H__