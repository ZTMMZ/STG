#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "entity/EnemyModel.h"
#include "entity/BossModel.h"
#include "entity/EBulletEjector.h"
#include "entity/PlayerFactory.h"
USING_NS_CC;

class GameLayer:public BaseLayer{
public:
	//Boss序列
	Vector<BossModel *> bosss;
	////Boss子弹序列
	//Vector<BBulletEjector *> bBulletEjectors;
	//敌机序列
	Vector<EnemyModel *> enemys;
	//敌机子弹序列
	Vector<EBulletEjector *> eBulletEjectors;
	//自机Model
	PlayerFactory* playerFactory;
	//场景速度
	float sceneSpeed;
	//分数
	long score;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(GameLayer);


	/**********独立事件***********/
	//显示关卡标题
	void showStageTitle();
	//清屏
	void killAllEnemys();
	//停止飞行
	void stopFlying();
	////移出敌机子弹组
	//void deleteAllEjector();
	//加分
	void addScore(int num);
	//暂停
	void gamePause();
	void gameResume();
	//游戏结束
	void gameOver();
	void gameClear();
/*******计划任务*******/
	//时间线
	void taskTimeLine(float t);
	//背景滚动
	void taskMoveBackground(float t);
	//创建敌机
	void taskCreateEnemy(float t);
	void taskCreateEnemy2(float t);
	void taskCreateBoss(float t);
	//碰撞检测
	void collisionDetectPlayerEnemy(float t);
	void collisionDetectPBulletEnemy(float t);
	void collisionDetectEBulletPlayer(float t);

	void collisionDetectPlayerBoss(float t);
	void collisionDetectPBulletBoss(float t);
	void collisionDetectBBulletPlayer(float t);

/********控制系统回调********/
	//按键控制
	void setupButtonControl();
	//按键回调
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);

	Label* scoreLabel;
};
#endif // __GAME_LAYER_H__