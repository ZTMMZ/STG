#ifndef __PLAYER_FACTORY_H__
#define __PLAYER_FACTORY_H__

#include "cocos2d.h"
#include "BaseLayer.h"

USING_NS_CC;

class PlayerFactory:public BaseLayer{
public:
	//����PlayerFactory
	PlayerFactory();
	~PlayerFactory();
	bool init();
	static PlayerFactory* createPlayerFactory();
	CC_SYNTHESIZE_READONLY(CCSprite*, player, PlayerSprite);
	CC_SYNTHESIZE_READONLY(CCSprite*, cPoint, CPointSprite);
	
	//�½��Ի�
	void createPlayer();

	//�Ի���λ
	void playerSetOn();
	//�Ի���δ��λ
	void playerStandBy();

	//�Ի������ӵ�
	void createMyBullet(float t);
	//�Ի��ӵ��ƶ�
	void moveMyBullet(float t);
	//�Ƴ��Ի��ӵ�
	void deletePBullet(Object *data);

	//�Ի������޵�״̬
	void playerInvincible();
	//�Ի��˳��޵�״̬
	void exitInvincible();

	//�����Ի�����
	void setPlayerLife(int life);
	//�Ի�����
	void playerDie();
	//�ж��Ի������Ƿ�Ϊ0
	void isGameOver(float t);

	//��������
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	//���ô�������
	void setupTouchControl();
public:
	//�Ի�����
	int life;
	//�Ի�λ��
	Point pPosition;
	//�Ի��Ƿ��λ
	bool isPlayerSetOn;
	//�Ի��Ƿ���ܿ���
	bool isOnCtrl;
	//��ָ�Ƿ�����Ļ��
	bool isFingerOn;
	//����λ��
	Point touchPosition;
	//�Ի��Ƿ�����޵�״̬
	bool isPlayerInvincible;
	//�Ի��ӵ�����
	Vector<Sprite *> pBullets;
private:
	//�Ի�֡��������
	Vector<SpriteFrame*> spriteFrames;

};
#endif // __PLAYER_FACTORY_H__