#include "entity/EnemyModel.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

EnemyModel::EnemyModel(int type){
	if (type == 0){
		enemyParams.lifePoint = 8;
		enemyParams.tag = 200;
		enemyParams.createLocation[0] = -100;
		enemyParams.createLocation[1] = 1060;
		enemyParams.frameActionNum = 4;
		enemyParams.textureName = 0;
		enemyParams.stayTime = 0;
		enemyParams.bezierPointA[0] = 400;
		enemyParams.bezierPointA[1] = 1060;
		enemyParams.bezierPointA[2] = 820;
		enemyParams.bezierPointA[3] = 640;
		enemyParams.bezierPointA[4] = 820;
		enemyParams.bezierPointA[5] = 640;
		enemyParams.bezierATime = 4;
		enemyParams.enemyScore = 120;
	}
	else if (type == 1){
		enemyParams.lifePoint = 6;
		enemyParams.tag = 201;
		enemyParams.createLocation[0] = 820;
		enemyParams.createLocation[1] = 1060;
		enemyParams.frameActionNum = 4;
		enemyParams.textureName = 1;
		enemyParams.stayTime = 0;
		enemyParams.bezierPointA[0] = 320;
		enemyParams.bezierPointA[1] = 1060;
		enemyParams.bezierPointA[2] = -100;
		enemyParams.bezierPointA[3] = 640;
		enemyParams.bezierPointA[4] = -100;
		enemyParams.bezierPointA[5] = 640;
		enemyParams.bezierATime = 4;
		enemyParams.enemyScore = 86;
	}

	//�����л�  
	EnemyModel::enemy = Sprite::createWithSpriteFrameName(String::createWithFormat("enemy%i_0.png", enemyParams.textureName)->_string);
	enemy->setPosition(Point(enemyParams.createLocation[0], enemyParams.createLocation[1]));
	enemy->setTag(enemyParams.tag);

	//����֡����
	Vector<SpriteFrame*> spriteFrames;
	char fileName[100] = { 0 };
	for (int i = 0; i < enemyParams.frameActionNum; i++)
	{
		sprintf(fileName, "enemy%i_%i.png", enemyParams.textureName, i);
		SpriteFrame *frames = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
		spriteFrames.pushBack(frames);
	}
	frameAction = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(spriteFrames, 0.08)));

	//��������
	ccBezierConfig enemyMovePath;
	enemyMovePath.controlPoint_1 = Point(enemyParams.bezierPointA[0], enemyParams.bezierPointA[1]);
	enemyMovePath.controlPoint_2 = Point(enemyParams.bezierPointA[2], enemyParams.bezierPointA[3]);
	enemyMovePath.endPosition = Point(enemyParams.bezierPointA[4], enemyParams.bezierPointA[5]);
	pathAction = BezierTo::create(enemyParams.bezierATime, enemyMovePath);

}
EnemyModel::~EnemyModel(){
}
bool EnemyModel::init(){
	//��ӵл�
    this->addChild(enemy,4);
    //ִ�ж���
	enemy->runAction(Sequence::create(pathAction,
		CCCallFunc::create(this, callfunc_selector(EnemyModel::overScreen)),
		NULL));
    enemy->runAction(frameAction);

    return true;
}

EnemyModel* EnemyModel::createEnemy(int type){

    EnemyModel* model = new EnemyModel(type);
    
    if(model && model->init()){
        model->autorelease();
        return  model;
    }
    
    CC_SAFE_DELETE( model );
    return NULL;
}

//���˱�����
void EnemyModel::enemyHit(){
	enemyParams.lifePoint--;
	if (enemyParams.lifePoint != 0){
		return;
	}
	else{
		enemyDie();
	}
}

//���˽����ƶ�
void EnemyModel::overScreen(){
	enemy->setTag(299);
	deleteEnemyInArray();
}

//��������
void EnemyModel::enemyDie(){
	enemy->setTag(299);
	GameLayer* gameLayer = (GameLayer*)this->getParent();
	gameLayer->addScore(enemyParams.enemyScore);
	enemy->runAction(Sequence::create(FadeOut::create(0.01),
		CCCallFunc::create(this, callfunc_selector(EnemyModel::enemyExplode)),
		CCCallFunc::create(this,callfunc_selector(EnemyModel::deleteEnemyInArray)),
		NULL));
}

//���˱�ը��Ч
void EnemyModel::enemyExplode(){
	ParticleSystem * explodingRing=ParticleSystemQuad::create("texture/enemy/explodingring.plist");
	explodingRing->setTexture(TextureCache::sharedTextureCache()->addImage("texture/enemy/explodingring.plist.png"));
	explodingRing->setAutoRemoveOnFinish(true);
	explodingRing->setPosition(enemy->getPosition());
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_explode.wav");
	this->addChild(explodingRing, 7);
}

//���������Ƴ�����
void EnemyModel::deleteEnemyInArray(){
	GameLayer* gameLayer = (GameLayer*)this->getParent();
	gameLayer->enemys.eraseObject(this);
}

//�ų�����
void EnemyModel::createPoints(int i){

}
