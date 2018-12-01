#include "GameLayer.h"
#include "GameOverLayer.h"
#include "GameClearLayer.h"
#include "MenuLayer.h"
#include "PauseMenuLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
	layer->setTag(999);
    scene->addChild(layer);
    return scene;
}
/*
�㼶��
0	->	�󱳾�
1	->	��������Ч
2	->	�󾰹�������
3	->	��Ԫ��
4	->	�Ի�
4	->	�л�
5	->	�Ի�	�ӵ�
6	->	�л��ӵ�
7	->	��ը����Ч
8	->	ǰ��Ԫ��
9	->	����Ч������
10	->	ǰ����������
11	->	�ж���
12	->	����
12	->	�ؿ�����

Tag��
0		->	�󱳾�
1��2		->	�󾰹�������
3��4		->	����Ч������
5��6		->	ǰ����������
10-19	->	��������Ч
20-29	->	��ը����Ч
30-39	->	��Ԫ��
40-49	->	ǰ��Ԫ��
100		->	�Ի��ӵ�
101-199	->	�ӵ�
200-298	->	�л�
299		->	��ײ����δ�����ĵл�
300		->	�Ի�
400		->	�ж���
500		->	����
501		->	�Ի�����ֵ
600		->	�ؿ�����
*/

bool GameLayer:: init(){
	if(!Layer::init()){return false;}
	//���ó����ٶ�
	sceneSpeed=0.1;
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm/bgm_stage1_0.mp3",true);
	//���ô󱳾�
	setBackgroundSprite("texture/game/stage_1/bg_00.jpg",0,0);
	//�󾰹�������
	setBackgroundSprite("texture/game/stage_1/bg_01.png",2,1);
	setBackgroundSprite("texture/game/stage_1/bg_01.png",2,2,Point(0,getVisibleSize().height));
	//���÷���Ч������
	setBackgroundSprite("texture/game/stage_1/bg_02.png",9,3);
	setBackgroundSprite("texture/game/stage_1/bg_02.png",9,4,Point(0,getVisibleSize().height));
	//����ǰ����������
	setBackgroundSprite("texture/game/stage_1/bg_03.png",10,5);
	setBackgroundSprite("texture/game/stage_1/bg_03.png",10,6,Point(0,getVisibleSize().height));
	//���÷���
	score = 0;
	scoreLabel = Label::create("0","fonts/miniswb.ttf",48);
	scoreLabel->setString(String::createWithFormat("%d",score)->_string);
	scoreLabel->setPosition(Point(getVisibleSize().width-25,getVisibleSize().height-25));
	scoreLabel->setAnchorPoint(Point(1,1));
	addChild(scoreLabel,12);
	scoreLabel->setTag(500);
	
	//�����Ի�
	playerFactory = PlayerFactory::createPlayerFactory();
	this->addChild(playerFactory);
	//����������ʾ
	CCNode* playerLifes = CCNode::create();
	playerLifes->setTag(501);
	playerLifes->setPosition(Point::ZERO);
	this->addChild(playerLifes, 12);
	playerFactory->setPlayerLife(playerFactory->life);
	//���ùؿ�����
	Sprite* stageTitle=Sprite::create("texture/game/stage_1/stage_title.png");
	stageTitle->setPosition(Point(getVisibleSize().width/2 + getOrigin().x, getVisibleSize().height/2 + getOrigin().y));
	stageTitle->setOpacity(0);
	this->addChild(stageTitle,12);
	stageTitle->setTag(600);
	//���üƻ�����
	this->schedule(schedule_selector(GameLayer::collisionDetectPlayerEnemy));
	this->schedule(schedule_selector(GameLayer::collisionDetectPBulletEnemy));
	this->schedule(schedule_selector(GameLayer::collisionDetectEBulletPlayer));

	this->schedule(schedule_selector(GameLayer::taskTimeLine),sceneSpeed);

	//���ð�������
	setupButtonControl();

	return true;
}

/**********�����¼�***********/
//��ʾ�ؿ�����
void GameLayer::showStageTitle(){
	getChildByTag(600)->runAction(CCSequence::create(CCFadeIn::create(1),DelayTime::create(2),CCFadeOut::create(1),NULL));
}
//ֹͣ����
void GameLayer::stopFlying(){
	auto spbkr0 = this->getChildByTag(1);
	auto spbkr1 = this->getChildByTag(2);
	auto spbkr2 = this->getChildByTag(3);
	auto spbkr3 = this->getChildByTag(4);
	auto spbkr4 = this->getChildByTag(5);
	auto spbkr5 = this->getChildByTag(6);
	spbkr0->runAction(CCFadeOut::create(6));
	spbkr1->runAction(CCFadeOut::create(6));
	spbkr2->runAction(CCFadeOut::create(4));
	spbkr3->runAction(CCFadeOut::create(4));
	spbkr4->runAction(CCFadeOut::create(10));
	spbkr5->runAction(CCFadeOut::create(10));

}
//������е���
void GameLayer::killAllEnemys(){
	for (int i = 0; i < enemys.size(); i++)
	{
		EnemyModel* enemy=enemys.at(i);
		enemy->enemyDie();
		enemys.eraseObject(enemy);
	}
}

////�Ƴ��л��ӵ�Ejector��
//void GameLayer::deleteAllEjector(){
//	eBulletEjectors.clear();
//}
//�ӷ�
void GameLayer::addScore(int num){
	score += num;
	scoreLabel->setString(String::createWithFormat("%d", score)->_string);
}

//��Ϸ����
void GameLayer::gameOver(){
	this->unscheduleAllSelectors();
	this->getScene()->addChild(GameOverLayer::create(),1000);
	this->onExit();
}
//��Ϸ����
void GameLayer::gameClear(){
	this->unscheduleAllSelectors();
	this->getScene()->addChild(GameClearLayer::create(), 1000);
	this->onExit();
}

/*******�Զ���ļƻ�����*******/
//ʱ����
void GameLayer::taskTimeLine(float t){
	//�󱳾�����
	auto spbk = this->getChildByTag(0);
	//0s
	if(-spbk->getPositionY()*sceneSpeed==0){
		this->schedule(schedule_selector(GameLayer::taskMoveBackground));
	}
	//1s
	if(-spbk->getPositionY()*sceneSpeed==1){
		showStageTitle();		
	}
	//6s
	if(-spbk->getPositionY()*sceneSpeed==6){
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy),0.5);
	}
	//10s
	if(-spbk->getPositionY()*sceneSpeed==10){
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy));
	}
	//11s
	if(-spbk->getPositionY()*sceneSpeed==11){
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy),0.5);
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy2),0.5);
	}
	//15s
	if(-spbk->getPositionY()*sceneSpeed==15){
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy));
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy2));
	}
	//16s
	if(-spbk->getPositionY()*sceneSpeed==16){
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy),0.5);
	}
	//20s
	if(-spbk->getPositionY()*sceneSpeed==20){
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy));
	}
	//21s
	if(-spbk->getPositionY()*sceneSpeed==21){
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy2),0.5);
	}
	//25s
	if(-spbk->getPositionY()*sceneSpeed==25){
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy2));
	}
	//26s
	if(-spbk->getPositionY()*sceneSpeed==26){
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy),0.5);
	}
	//30s
	if(-spbk->getPositionY()*sceneSpeed==30){
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy));
	}
	//31s
	if(-spbk->getPositionY()*sceneSpeed==31){
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy2),0.5);
	}
	//35s
	if(-spbk->getPositionY()*sceneSpeed==35){
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy2));
	}
	//36s
	if(-spbk->getPositionY()*sceneSpeed==36){
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy),0.5);
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy2),0.5);
	}
	//40s
	if(-spbk->getPositionY()*sceneSpeed==40){
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy));
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy2));
	}
	//46s
	if (-spbk->getPositionY()*sceneSpeed == 46){
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy), 0.5);
		this->schedule(schedule_selector(GameLayer::taskCreateEnemy2), 0.5);
	
	}
	//50s
	if (-spbk->getPositionY()*sceneSpeed == 50){
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy));
		this->unschedule(schedule_selector(GameLayer::taskCreateEnemy2));
	}
	//54s
	if(-spbk->getPositionY()*sceneSpeed==54){
		stopFlying();
	}
	//62s
	if(-spbk->getPositionY()*sceneSpeed==62){
		killAllEnemys();
		//deleteAllEjector();
	}
	//>=64s
	if(-spbk->getPositionY()*sceneSpeed>=64){	
		this->unschedule(schedule_selector(GameLayer::taskMoveBackground));
		this->unschedule(schedule_selector(GameLayer::taskTimeLine));
		this->scheduleOnce(schedule_selector(GameLayer::taskCreateBoss), 3);
		this->schedule(schedule_selector(GameLayer::collisionDetectPlayerBoss));
		this->schedule(schedule_selector(GameLayer::collisionDetectPBulletBoss));
		this->schedule(schedule_selector(GameLayer::collisionDetectBBulletPlayer));

	}
	//<64s
	if(-spbk->getPositionY()*sceneSpeed<64)
	{
		spbk->setPositionY(spbk->getPositionY()-1);
	}
}
//��������
void GameLayer::taskMoveBackground(float t){
	//�󾰹�������
	//��ȡ��������
	auto spbkr0 = this->getChildByTag(1);
	auto spbkr1 = this->getChildByTag(2);
	//�����ƶ���������A
	spbkr0->setPositionY(spbkr0->getPositionY()-4);
	//����������A�Ƴ�����ʱ����λ
	if(spbkr0->getPositionY()<-spbkr0->getContentSize().height)
	{
		spbkr0->setPositionY(0);
	}
	//��������B��Զ������A���Ϸ�
	spbkr1->setPositionY(spbkr0->getPositionY()+spbkr0->getContentSize().height);

	//����Ч������
	//��ȡ��������
	auto spbkr2 = this->getChildByTag(3);
	auto spbkr3 = this->getChildByTag(4);
	//�����ƶ���������A
	spbkr2->setPositionY(spbkr2->getPositionY()-6);
	//����������A�Ƴ�����ʱ����λ
	if(spbkr2->getPositionY()<-spbkr2->getContentSize().height)
	{
		spbkr2->setPositionY(0);
	}
	//��������B��Զ������A���Ϸ�
	spbkr3->setPositionY(spbkr2->getPositionY()+spbkr2->getContentSize().height);

	//ǰ����������
	//��ȡ��������
	auto spbkr4 = this->getChildByTag(5);
	auto spbkr5 = this->getChildByTag(6);
	//�����ƶ���������A
	spbkr4->setPositionY(spbkr4->getPositionY()-8);
	//����������A�Ƴ�����ʱ����λ
	if(spbkr4->getPositionY()<-spbkr4->getContentSize().height)
	{
		spbkr4->setPositionY(0);
	}
	//��������B��Զ������A���Ϸ�
	spbkr5->setPositionY(spbkr4->getPositionY()+spbkr4->getContentSize().height);

}
//�л�����
void GameLayer::taskCreateEnemy(float t){
	EnemyModel* enemyModel = EnemyModel::createEnemy(1);
	CC_SAFE_RETAIN(enemyModel);
	enemys.pushBack(enemyModel);
    this->addChild(enemyModel,4);
	enemyModel->setPosition(Point::ZERO);

	EBulletEjector* eBulletModel = EBulletEjector::createEBullet(enemyModel,1,playerFactory);
	CC_SAFE_RETAIN(eBulletModel);
	eBulletEjectors.pushBack(eBulletModel);
	this->addChild(eBulletModel,6);

}
//�л�����
void GameLayer::taskCreateEnemy2(float t){
	EnemyModel* enemyModel = EnemyModel::createEnemy(0);
	CC_SAFE_RETAIN(enemyModel);
	enemys.pushBack(enemyModel);
    this->addChild(enemyModel,4);
	enemyModel->setPosition(Point::ZERO);

	EBulletEjector* eBulletModel = EBulletEjector::createEBullet(enemyModel, 0, playerFactory);
	CC_SAFE_RETAIN(eBulletModel);
	eBulletEjectors.pushBack(eBulletModel);
	this->addChild(eBulletModel,6);

}
//Boss����
void GameLayer::taskCreateBoss(float t){
	BossModel* bossModel = BossModel::createBoss(0);
	CC_SAFE_RETAIN(bossModel);
	bosss.pushBack(bossModel);
	this->addChild(bossModel, 4);
	bossModel->setPosition(Point::ZERO);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm/bgm_stage1_1.mp3",true);
}
/********��ײ���********/
//�Ի���л���ײ
void GameLayer::collisionDetectPlayerEnemy(float t){
	auto cPoint = playerFactory->getChildByTag(400);
	Point mPoint = cPoint->getPosition();
	float mRadius = cPoint->getContentSize().height / 2;

	for (int i = 0; i < enemys.size(); i++)
	{
		auto enemy = enemys.at(i);

		Point ePoint = enemy->getEnemySprite()->getPosition();
		float eRadius = enemy->getEnemySprite()->getContentSize().height / 2;

		if ((ccpDistance(mPoint, ePoint) <= mRadius + eRadius) && enemy->getEnemySprite()->getTag() != 299){
			playerFactory->playerDie();
			enemy->enemyHit();
			i--;
		}
	}
}
//�Ի���л��ӵ�����ײ
void GameLayer::collisionDetectEBulletPlayer(float t){
	auto cPoint = playerFactory->getChildByTag(400);
	Point mPoint = cPoint->getPosition();
	float mRadius = cPoint->getContentSize().height / 2;

	for (int i = 0; i < eBulletEjectors.size(); i++)
	{
		EBulletEjector* eBulletModel = eBulletEjectors.at(i);
		Vector<Node*> eBulletBatch = eBulletModel->getEBBatchNode()->getChildren();

		for (int j = 0; j < eBulletBatch.size(); j++){

			Sprite* eBullet = (Sprite*)eBulletBatch.at(j);
			Point eBPoint = eBullet->getPosition();

			if (ccpDistance(mPoint, eBPoint) <= mRadius&&eBullet->getTag() != 199){
				playerFactory->playerDie();
				eBulletModel->eBulletDie(eBullet);
				j--;
			}
		}

	}
}
//�Ի��ӵ���л���ײ
void GameLayer::collisionDetectPBulletEnemy(float t){
	for (int i = 0; i < enemys.size(); i++)
	{
		auto enemy = enemys.at(i);
		Point ePoint = enemy->getEnemySprite()->getPosition();
		float eRadius = enemy->getEnemySprite()->getContentSize().height / 2;
		for (int j = 0; j< playerFactory->pBullets.size(); j++)
		{
			auto pBullet = playerFactory->pBullets.at(j);
			Rect pBRect = Rect(pBullet->getPositionX() - pBullet->getContentSize().width / 2,
				pBullet->getPositionY() - pBullet->getContentSize().height / 2,
				pBullet->getContentSize().width,
				pBullet->getContentSize().height);

			float cx, cy;

			if (ePoint.x < pBRect.getMinX())
				cx = pBRect.getMinX();
			else if (ePoint.x > pBRect.getMaxX())
				cx = pBRect.getMaxX();
			else
				cx = ePoint.x;

			if (ePoint.y < pBRect.getMinY())
				cy = pBRect.getMinY();
			else if (ePoint.y > pBRect.getMaxY())
				cy = pBRect.getMaxY();
			else
				cy = ePoint.y;

			if (ccpDistance(ePoint, Point(cx, cy))<eRadius&&enemy->getEnemySprite()->getTag() != 299){
				playerFactory->deletePBullet(pBullet);
				enemy->enemyHit();
				j--;
			}
		}
	}
}
//�Ի���Boss��ײ
void GameLayer::collisionDetectPlayerBoss(float t){
	auto cPoint = playerFactory->getChildByTag(400);
	Point mPoint = cPoint->getPosition();
	float mRadius = cPoint->getContentSize().height / 2;

	for (int i = 0; i < bosss.size(); i++)
	{
		auto boss = bosss.at(i);

		Point bPoint = boss->getBossSprite()->getPosition();
		float bRadius = boss->getBossSprite()->getContentSize().width / 2;

		if ((ccpDistance(mPoint, bPoint) <= mRadius + bRadius) && boss->getBossSprite()->getTag() != 299){
			playerFactory->playerDie();
			break;
			//boss->bossHit();
			i--;
		}
	}
}
//�Ի��ӵ���Boss��ײ
void GameLayer::collisionDetectPBulletBoss(float t){
	for (int i = 0; i < bosss.size(); i++)
	{
		auto boss = bosss.at(i);
		Point bPoint = boss->getBossSprite()->getPosition();
		float bRadius = boss->getBossSprite()->getContentSize().width / 2;
		for (int j = 0; j< playerFactory->pBullets.size(); j++)
		{
			auto pBullet = playerFactory->pBullets.at(j);
			Rect pBRect = Rect(pBullet->getPositionX() - pBullet->getContentSize().width / 2,
				pBullet->getPositionY() - pBullet->getContentSize().height / 2,
				pBullet->getContentSize().width,
				pBullet->getContentSize().height);

			float cx, cy;

			if (bPoint.x < pBRect.getMinX())
				cx = pBRect.getMinX();
			else if (bPoint.x > pBRect.getMaxX())
				cx = pBRect.getMaxX();
			else
				cx = bPoint.x;

			if (bPoint.y < pBRect.getMinY())
				cy = pBRect.getMinY();
			else if (bPoint.y > pBRect.getMaxY())
				cy = pBRect.getMaxY();
			else
				cy = bPoint.y;

			if (ccpDistance(bPoint, Point(cx, cy))<bRadius&&boss->getBossSprite()->getTag() != 299){
				playerFactory->deletePBullet(pBullet);
				boss->bossHit();
				j--;
			}
		}
	}
}
//�Ի���Boss�ӵ�����ײ
void GameLayer::collisionDetectBBulletPlayer(float t){
	auto cPoint = playerFactory->getChildByTag(400);
	Point mPoint = cPoint->getPosition();
	float mRadius = cPoint->getContentSize().height / 2;

	for (int i = 0; i < bosss.size(); i++)
	{

		BossModel* bossModel = bosss.at(i);
		Vector<Sprite*> bBullets = bossModel->bBullets;

		for (int j = 0; j < bBullets.size(); j++){

			Sprite* bBullet = bBullets.at(j);
			Point bBPoint = bBullet->getPosition();

			if (ccpDistance(mPoint, bBPoint) <= mRadius&&bBullet->getTag() != 199){
				playerFactory->playerDie();
				bossModel->bBulletDie(bBullet);
				j--;
			}
		}

	}
}
/********����ϵͳ�ص�********/
//�����ص�
void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	gamePause();
}
//��������
void GameLayer::setupButtonControl(){
	//���ֻ����ؼ��ļ���
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}


void GameLayer::gamePause(){
	if (!Director::getInstance()->sharedDirector()->isPaused()){
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_pause.wav");
		this->getScene()->addChild(PauseMenuLayer::create(), 1000, "Pause");
		Director::getInstance()->sharedDirector()->pause();
	}
}
void GameLayer::gameResume(){
	if (Director::getInstance()->sharedDirector()->isPaused()){
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->sharedDirector()->resume();
	}
}