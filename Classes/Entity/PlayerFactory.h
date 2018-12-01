#ifndef __PLAYER_FACTORY_H__
#define __PLAYER_FACTORY_H__

#include "cocos2d.h"
#include "BaseLayer.h"

USING_NS_CC;

class PlayerFactory:public BaseLayer{
public:
	//创建PlayerFactory
	PlayerFactory();
	~PlayerFactory();
	bool init();
	static PlayerFactory* createPlayerFactory();
	CC_SYNTHESIZE_READONLY(CCSprite*, player, PlayerSprite);
	CC_SYNTHESIZE_READONLY(CCSprite*, cPoint, CPointSprite);
	
	//新建自机
	void createPlayer();

	//自机就位
	void playerSetOn();
	//自机尚未就位
	void playerStandBy();

	//自机发射子弹
	void createMyBullet(float t);
	//自机子弹移动
	void moveMyBullet(float t);
	//移除自机子弹
	void deletePBullet(Object *data);

	//自机进入无敌状态
	void playerInvincible();
	//自机退出无敌状态
	void exitInvincible();

	//设置自机生命
	void setPlayerLife(int life);
	//自机死亡
	void playerDie();
	//判断自机生命是否为0
	void isGameOver(float t);

	//触摸控制
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	//设置触摸控制
	void setupTouchControl();
public:
	//自机生命
	int life;
	//自机位置
	Point pPosition;
	//自机是否就位
	bool isPlayerSetOn;
	//自机是否接受控制
	bool isOnCtrl;
	//手指是否在屏幕上
	bool isFingerOn;
	//触摸位置
	Point touchPosition;
	//自机是否进入无敌状态
	bool isPlayerInvincible;
	//自机子弹序列
	Vector<Sprite *> pBullets;
private:
	//自机帧动画序列
	Vector<SpriteFrame*> spriteFrames;

};
#endif // __PLAYER_FACTORY_H__