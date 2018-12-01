#include "entity/EBulletEjector.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

EBulletEjector::EBulletEjector(EnemyModel* enemyModel, int type, PlayerFactory* playerFactory){
	this->enemyModel = enemyModel;
	this->playerFactory = playerFactory;
	leftBulletNum = 50;
	this->type = type;
	//��ȡ�л��ӵ�Ȼ����뵽CCSpriteBatchNode��
	char filePath[100] = { 0 };
	sprintf(filePath, "texture/bullet/eBullet%d_0.png", this->type);
	eBulletsBatchNode = CCSpriteBatchNode::create(filePath);
}
EBulletEjector::~EBulletEjector(){
}
bool EBulletEjector::init(){

    this->addChild(eBulletsBatchNode,6);

    //ִ�м����ӵ���schedule
    this->schedule(schedule_selector(EBulletEjector::addBullet),0.1);
	//ֹͣ������
	this->schedule(schedule_selector(EBulletEjector::isEnemyDie));
	//�ƶ��ӵ�
    this->schedule(schedule_selector(EBulletEjector::moveBullet));
	//�ͷż��
	this->schedule(schedule_selector(EBulletEjector::isEBulletsEmpty));
	return true;
}

EBulletEjector* EBulletEjector::createEBullet(EnemyModel* enemyModel, int type, PlayerFactory* playerFactory){
	EBulletEjector* model = new EBulletEjector(enemyModel, type, playerFactory);

    if(model && model->init()){
        model->autorelease();
        return model;
    }
    
    CC_SAFE_DELETE(model);

    return NULL;
}

void EBulletEjector::addBullet( float t ){
	leftBulletNum--;
	char filePath[100] = { 0 };
	sprintf(filePath, "texture/bullet/eBullet%d_0.png", this->type);
	CCSprite* eBullet = CCSprite::create(filePath);
	eBullet->setPosition(enemyModel->getEnemySprite()->getPosition());
	//eBullet->setRotation();
	//eBullet->runAction(CCMoveTo::create(1, Point(playerFactory->pPosition)));
    eBulletsBatchNode->addChild(eBullet); 
	eBullets.pushBack(eBullet);
	eBullet->setTag(101);
}
//ɾ���ӵ�
void EBulletEjector::deleteEBullet(Object *data){
	Sprite* eBullet = (Sprite *)data;
	eBullets.eraseObject(eBullet);
}
//�ӵ�����
void EBulletEjector::eBulletDie(Sprite *eBullet){
	eBullet->setTag(199);
	eBullet->runAction(Sequence::create(FadeOut::create(0.01),
		CCCallFuncO::create(this, callfuncO_selector(EBulletEjector::eBulletExplode),eBullet),
		CCCallFuncO::create(this,callfuncO_selector(EBulletEjector::deleteEBullet),eBullet),
		NULL));
}
//�ӵ���ը��Ч
void EBulletEjector::eBulletExplode(Object *data){
	Sprite* eBullet = (Sprite *)data;
	ParticleSystem * exploding=ParticleSystemQuad::create("texture/bullet/ebulletexplode.plist");
	exploding->setTexture(TextureCache::sharedTextureCache()->addImage("texture/bullet/ebulletexplode.plist.png"));
	exploding->setAutoRemoveOnFinish(true);
	exploding->setPosition(eBullet->getPosition());
	this->addChild(exploding, 7);
}

//ֹͣ����
void EBulletEjector::isEnemyDie(float t){
	if (enemyModel->getEnemySprite()->getTag() == 299){
		leftBulletNum = 0;
		this->unschedule(schedule_selector(EBulletEjector::addBullet));
	}else if(leftBulletNum < 0){
		this->unschedule(schedule_selector(EBulletEjector::addBullet));
	}
}
//�ƶ��ӵ�
void EBulletEjector::moveBullet(float t){
	for(int i=0;i<eBullets.size();i++){
		Sprite* eBullet = eBullets.at(i);
		if(eBullet->getTag()!=199){
			eBullet->setPosition(eBullet->getPositionX(),eBullet->getPositionY()-5-(eBullet->getPositionY()/1280)*(eBullet->getPositionY()/1280)*20);

			if(eBullet->getPositionX()<-100||eBullet->getPositionX()>820||eBullet->getPositionY()<-100||eBullet->getPositionY()>1380){
				eBullet->setTag(199);
				deleteEBullet(eBullet);
			}
		}
	}
}
//����ӵ����Ƿ�Ϊ��
void EBulletEjector::isEBulletsEmpty(float t){
	if (eBullets.size() == 0 && leftBulletNum == 0){
		deleteEjectorInArray();
	}
}
//���������Ƴ�����
void EBulletEjector::deleteEjectorInArray(){
	GameLayer* gameLayer = (GameLayer*)this->getParent();
	gameLayer->eBulletEjectors.eraseObject(this);
}