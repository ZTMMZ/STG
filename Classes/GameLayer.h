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
	//Boss����
	Vector<BossModel *> bosss;
	////Boss�ӵ�����
	//Vector<BBulletEjector *> bBulletEjectors;
	//�л�����
	Vector<EnemyModel *> enemys;
	//�л��ӵ�����
	Vector<EBulletEjector *> eBulletEjectors;
	//�Ի�Model
	PlayerFactory* playerFactory;
	//�����ٶ�
	float sceneSpeed;
	//����
	long score;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(GameLayer);


	/**********�����¼�***********/
	//��ʾ�ؿ�����
	void showStageTitle();
	//����
	void killAllEnemys();
	//ֹͣ����
	void stopFlying();
	////�Ƴ��л��ӵ���
	//void deleteAllEjector();
	//�ӷ�
	void addScore(int num);
	//��ͣ
	void gamePause();
	void gameResume();
	//��Ϸ����
	void gameOver();
	void gameClear();
/*******�ƻ�����*******/
	//ʱ����
	void taskTimeLine(float t);
	//��������
	void taskMoveBackground(float t);
	//�����л�
	void taskCreateEnemy(float t);
	void taskCreateEnemy2(float t);
	void taskCreateBoss(float t);
	//��ײ���
	void collisionDetectPlayerEnemy(float t);
	void collisionDetectPBulletEnemy(float t);
	void collisionDetectEBulletPlayer(float t);

	void collisionDetectPlayerBoss(float t);
	void collisionDetectPBulletBoss(float t);
	void collisionDetectBBulletPlayer(float t);

/********����ϵͳ�ص�********/
	//��������
	void setupButtonControl();
	//�����ص�
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);

	Label* scoreLabel;
};
#endif // __GAME_LAYER_H__