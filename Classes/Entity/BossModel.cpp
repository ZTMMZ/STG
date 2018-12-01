#include "entity/BossModel.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

BossModel::BossModel(int type){
	if (type == 0){
		bossParams.lifePoint = 50;
		bossParams.tag = 202;
		bossParams.createLocation[0] = 360;
		bossParams.createLocation[1] = 1380;
		bossParams.frameActionNum = 4;
		bossParams.textureName = 0;
		bossParams.bossScore = 120;
	}
	
	//创建Boss  
	BossModel::boss = Sprite::createWithSpriteFrameName(String::createWithFormat("boss%i_0.png", bossParams.textureName)->_string);
	boss->setPosition(Point(bossParams.createLocation[0], bossParams.createLocation[1]));
	boss->setTag(bossParams.tag);
	bBulletsBatchNode = CCSpriteBatchNode::create("texture/bullet/eBullet2_0.png");

	//建立帧动画
	Vector<SpriteFrame*> spriteFrames;
	char fileName[100] = { 0 };
	for (int i = 0; i < bossParams.frameActionNum; i++)
	{
		sprintf(fileName, "boss%i_%i.png", bossParams.textureName, i);
		SpriteFrame *frames = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
		spriteFrames.pushBack(frames);
	}
	frameAction = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(spriteFrames, 0.08)));
	ActionInterval * move0 = CCDelayTime::create(1);
	ActionInterval * move1 = CCMoveBy::create(1, ccp(-200,-50));
	ActionInterval * move2 = CCDelayTime::create(1.5f);
	ActionInterval * move3 = CCMoveBy::create(1, ccp(400, 100));
	ActionInterval * move4 = CCDelayTime::create(1.5f);
	ActionInterval * move5 = CCMoveBy::create(1, ccp(-200, -50));
	FiniteTimeAction* seq = Sequence::create(move0, move1, move2, move3, move4, move5, NULL);
	pathAction = RepeatForever::create((CCActionInterval*)seq);
	comeInAction = CCMoveTo::create(0.8f, ccp(360, 960));
}
BossModel::~BossModel(){
}
bool BossModel::init(){
	//添加敌机
    this->addChild(boss,4);
    //执行动画
	boss->runAction(pathAction);
	boss->runAction(comeInAction);
    boss->runAction(frameAction);

	this->addChild(bBulletsBatchNode, 6);

	//执行加入子弹的schedule
	this->schedule(schedule_selector(BossModel::addBullet), 0.3);
	//停止发射检测
	this->schedule(schedule_selector(BossModel::isBossDie));
	//移动子弹
	this->schedule(schedule_selector(BossModel::moveBullet));

    return true;
}

BossModel* BossModel::createBoss(int type){

    BossModel* model = new BossModel(type);
    
    if(model && model->init()){
        model->autorelease();
        return  model;
    }
    
    CC_SAFE_DELETE( model );
    return NULL;
}

//敌人被击中
void BossModel::bossHit(){
	bossParams.lifePoint--;
	if (bossParams.lifePoint != 0){
		return;
	}
	else{
		bossDie();
	}
}

//敌人死亡
void BossModel::bossDie(){
	boss->setTag(299);
	GameLayer* gameLayer = (GameLayer*)this->getParent();
	gameLayer->addScore(bossParams.bossScore);
	boss->runAction(Sequence::create(FadeOut::create(0.01),
		CCCallFunc::create(this, callfunc_selector(BossModel::bossExplode)),
		CCCallFunc::create(this,callfunc_selector(BossModel::deleteBossInArray)),
		DelayTime::create(2.0f),
		CCCallFunc::create(this->getParent(), callfunc_selector(GameLayer::gameClear)),
		NULL));
}

//敌人爆炸特效
void BossModel::bossExplode(){
	ParticleSystem * explodingRing=ParticleSystemQuad::create("texture/boss/explodingring.plist");
	explodingRing->setTexture(TextureCache::sharedTextureCache()->addImage("texture/boss/explodingring.plist.png"));
	explodingRing->setAutoRemoveOnFinish(true);
	explodingRing->setPosition(boss->getPosition());
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_explode.wav");
	this->addChild(explodingRing, 7);
}

//从序列中移除本类
void BossModel::deleteBossInArray(){
	GameLayer* gameLayer = (GameLayer*)this->getParent();
	gameLayer->bosss.eraseObject(this);
}

void BossModel::addBullet(float t){

	CCSprite* bBullet0 = CCSprite::create("texture/bullet/eBullet2_0.png");
	bBullet0->setPosition(Point(getBossSprite()->getPosition().x - 30, getBossSprite()->getPosition().y));
	bBulletsBatchNode->addChild(bBullet0);
	bBullets.pushBack(bBullet0);
	bBullet0->setTag(102);

	CCSprite* bBullet1 = CCSprite::create("texture/bullet/eBullet2_0.png");
	bBullet1->setPosition(Point(getBossSprite()->getPosition().x, getBossSprite()->getPosition().y));
	bBulletsBatchNode->addChild(bBullet1);
	bBullets.pushBack(bBullet1);
	bBullet1->setTag(103);

	CCSprite* bBullet2 = CCSprite::create("texture/bullet/eBullet2_0.png");
	bBullet2->setPosition(Point(getBossSprite()->getPosition().x +30, getBossSprite()->getPosition().y));
	bBulletsBatchNode->addChild(bBullet2);
	bBullets.pushBack(bBullet2);
	bBullet2->setTag(104);

	CCSprite* bBullet3 = CCSprite::create("texture/bullet/eBullet2_0.png");
	bBullet3->setPosition(Point(getBossSprite()->getPosition().x + 15, getBossSprite()->getPosition().y));
	bBulletsBatchNode->addChild(bBullet3);
	bBullets.pushBack(bBullet3);
	bBullet3->setTag(105);

	CCSprite* bBullet4 = CCSprite::create("texture/bullet/eBullet2_0.png");
	bBullet4->setPosition(Point(getBossSprite()->getPosition().x - 15, getBossSprite()->getPosition().y));
	bBulletsBatchNode->addChild(bBullet4);
	bBullets.pushBack(bBullet4);
	bBullet4->setTag(106);
}

void BossModel::moveBullet(float t){
	for (int i = 0; i<bBullets.size(); i++){
		Sprite* bBullet = bBullets.at(i);
		if (bBullet->getTag() != 199){
			bBullet->setPosition(bBullet->getPositionX(), bBullet->getPositionY() - 5 - (bBullet->getPositionY() / 1280)*(bBullet->getPositionY() / 1280) * 20);

			if (bBullet->getPositionX()<-100 || bBullet->getPositionX()>820 || bBullet->getPositionY()<-100 || bBullet->getPositionY()>1380){
				bBullet->setTag(199);
				deleteBBullet(bBullet);
			}
		}
	}
}

//删除子弹
void BossModel::deleteBBullet(Object *data){
	Sprite* bBullet = (Sprite *)data;
	bBullets.eraseObject(bBullet);
}
//子弹死亡
void BossModel::bBulletDie(Sprite *bBullet){
	bBullet->setTag(199);
	bBullet->runAction(Sequence::create(FadeOut::create(0.01),
		CCCallFuncO::create(this, callfuncO_selector(BossModel::bBulletExplode), bBullet),
		CCCallFuncO::create(this, callfuncO_selector(BossModel::deleteBBullet), bBullet),
		NULL));
}
//子弹爆炸特效
void BossModel::bBulletExplode(Object *data){
	Sprite* eBullet = (Sprite *)data;
	ParticleSystem * exploding = ParticleSystemQuad::create("texture/bullet/ebulletexplode.plist");
	exploding->setTexture(TextureCache::sharedTextureCache()->addImage("texture/bullet/ebulletexplode.plist.png"));
	exploding->setAutoRemoveOnFinish(true);
	exploding->setPosition(eBullet->getPosition());
	this->addChild(exploding, 7);
}
//停止发射
void BossModel::isBossDie(float t){
	if (getBossSprite()->getTag() == 299){
		this->unschedule(schedule_selector(BossModel::addBullet));
	}
}