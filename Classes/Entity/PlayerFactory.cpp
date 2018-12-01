#include "entity/PlayerFactory.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

PlayerFactory::PlayerFactory(){

	//触摸控制系统flag量
	isOnCtrl = true;
	isFingerOn = false;
	//自机准备中
	isPlayerSetOn = false;
	//自机是否进入无敌状态
	isPlayerInvincible = false;
	//设置自机生命值
	life = 3;
	//建立帧序列
	char fileName[100] = { 0 };
	for (int i = 0; i < 2; i++)
	{
		sprintf(fileName, "player0_%i.png", i);
		SpriteFrame *frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
		spriteFrames.pushBack(frame);
	}
}
PlayerFactory::~PlayerFactory(){
}
bool PlayerFactory::init(){
	createPlayer();
	setupTouchControl();
	this->schedule(schedule_selector(PlayerFactory::isGameOver));
    return true;
}
PlayerFactory* PlayerFactory::createPlayerFactory(){

	PlayerFactory* model = new PlayerFactory();
    
    if(model && model->init()){
        model->autorelease();
        return  model;
    }
    
    CC_SAFE_DELETE( model );
    return NULL;
}

//新建自机
void PlayerFactory::createPlayer(){
	//设置贴图
	player = Sprite::createWithSpriteFrameName("player0_0.png");
	cPoint = Sprite::create("texture/player/point.png");

	//创建自机
	player->setPosition(getVisibleSize().width/2, -100);
	player->setTag(300);
	pPosition = Point(getVisibleSize().width / 2, getVisibleSize().height * 0.1);

	//设置判定点
	cPoint->setOpacity(0);
	cPoint->setTag(400);
	cPoint->setPosition(pPosition);

	this->addChild(player, 4);
	this->addChild(cPoint, 11);

	//执行动画
	player->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(spriteFrames, 0.08))));
	player->runAction(Sequence::create(
		CCMoveTo::create(1.5f, Point(getVisibleSize().width / 2, getVisibleSize().height * 0.1)),
		CCCallFunc::create(this, callfunc_selector(PlayerFactory::playerSetOn)),
		NULL));
	if (isFingerOn)cPoint->runAction(FadeIn::create(0.1));
	//进入无敌状态
	playerInvincible();

}

//自机就位
void PlayerFactory::playerSetOn(){
	isPlayerSetOn = true;
}
//自机尚未就位
void PlayerFactory::playerStandBy(){
	isPlayerSetOn = false;
}

//自机发射子弹
void PlayerFactory::createMyBullet(float t){
	Sprite* bullet = Sprite::create("texture/player/bullet.png");
	bullet->setPosition(pPosition);
	this->addChild(bullet, 5);
	bullet->setOpacity(140);
	bullet->setTag(100);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_playershot.wav");
	this->pBullets.pushBack(bullet);
}
//自机子弹移动
void PlayerFactory::moveMyBullet(float t){
	for (int i = 0; i < pBullets.size(); i++)
	{
		auto pBullet = pBullets.at(i);
		pBullet->setPositionY(pBullet->getPositionY() + 25);
		if (pBullet->getPositionY()>1280+20)
		{
			deletePBullet(pBullet);
			i--;
		}
	}
}
//移除自机子弹
void PlayerFactory::deletePBullet(Object *data){
	Sprite* pBullet = (Sprite*)data;
	pBullet->removeFromParent();
	pBullets.eraseObject(pBullet);
}

//自机进入无敌状态
void PlayerFactory::playerInvincible(){
	isPlayerInvincible = true;
	Sprite* player = (Sprite*)getChildByTag(300);

	player->runAction(Sequence::create(
		CCBlink::create(5, 120),
		CCCallFunc::create(this, callfunc_selector(PlayerFactory::exitInvincible)),
		NULL));
}
//自机退出无敌状态
void PlayerFactory::exitInvincible(){ isPlayerInvincible = false; };

//设置自机生命值
void PlayerFactory::setPlayerLife(int life){
	CCNode* playerLifes = this->getParent()->getChildByTag(501);
	playerLifes->removeAllChildren();
	for (int i = 0; i<life; i++){
		Sprite* playerLife = Sprite::create("texture/player/player0life.png");
		playerLife->setAnchorPoint(Point(0, 1));
		playerLife->setPosition(Point(20 + i * 55, 1260));
		playerLifes->addChild(playerLife, 12);
	}
}
//自机死亡
void PlayerFactory::playerDie(){
	if (isPlayerSetOn&&!isPlayerInvincible){
		setPlayerLife(--life);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/se/se_playerdie.wav");
		playerStandBy();
		player->removeFromParent();
		cPoint->removeFromParent();
		createPlayer();
	}
}
//判断自机生命是否为0
void PlayerFactory::isGameOver(float t){
	if (life == -1){
		this->runAction(CCSequence::create(DelayTime::create(0.5f),
			CCCallFunc::create(this->getParent(), callfunc_selector(GameLayer::gameOver)),
			NULL));
	}
}

//触摸事件
bool PlayerFactory::onTouchBegan(Touch *touch, Event *unused_event){
	isFingerOn = true;
	if (isPlayerSetOn){
		isOnCtrl = true;
		Sprite* player = (Sprite*)getChildByTag(300);
		Sprite* cPoint = (Sprite*)getChildByTag(400);
		pPosition = player->getPosition();
		cPoint->setPosition(pPosition);
		cPoint->runAction(FadeIn::create(0.1));
		touchPosition.setPoint(touch->getLocation().x, touch->getLocation().y);
		this->schedule(schedule_selector(PlayerFactory::createMyBullet), 0.08);
		this->schedule(schedule_selector(PlayerFactory::moveMyBullet), 0.01);
	}
	return true;
}
void PlayerFactory::onTouchMoved(Touch *touch, Event *unused_event){
	isFingerOn = true;
	if (isPlayerSetOn){
		if (!isOnCtrl){
			Sprite* player = (Sprite*)getChildByTag(300);
			Sprite* cPoint = (Sprite*)getChildByTag(400);
			pPosition = player->getPosition();
			cPoint->setPosition(pPosition);
			//cPoint ->runAction(CCShow::create());
			cPoint->runAction(FadeIn::create(0.1));
			touchPosition.setPoint(touch->getLocation().x, touch->getLocation().y);
			this->schedule(schedule_selector(PlayerFactory::createMyBullet), 0.08);
			this->schedule(schedule_selector(PlayerFactory::moveMyBullet), 0.01);
			isOnCtrl = true;
		}
		Point movePosition = Point(touch->getLocation().x - touchPosition.x, touch->getLocation().y - touchPosition.y);
		if (movePosition.x + pPosition.x >= getVisibleSize().width){ movePosition.x = 0; }
		if (movePosition.y + pPosition.y >= getVisibleSize().height){ movePosition.y = 0; }
		if (movePosition.x + pPosition.x <= 0){ movePosition.x = 0; }
		if (movePosition.y + pPosition.y <= 0){ movePosition.y = 0; }

		auto player = this->getChildByTag(300);
		player->runAction(MoveBy::create(0, Point(movePosition.x, movePosition.y)));
		auto cPoint = this->getChildByTag(400);
		cPoint->runAction(MoveBy::create(0, Point(movePosition.x, movePosition.y)));
		touchPosition.setPoint(touch->getLocation().x, touch->getLocation().y);
		pPosition.setPoint(pPosition.x + movePosition.x, pPosition.y + movePosition.y);
	}
	else{
		isOnCtrl = false;
		if (!isFingerOn)getChildByTag(400)->runAction(FadeOut::create(0.2));
		this->unschedule(schedule_selector(PlayerFactory::createMyBullet));
	}
}
void PlayerFactory::onTouchEnded(Touch *touch, Event *unused_event){
	isFingerOn = false;
	this->getChildByTag(400)->runAction(FadeOut::create(0.2));
	this->unschedule(schedule_selector(PlayerFactory::createMyBullet));
}

//设置触摸控制
void PlayerFactory::setupTouchControl(){

	//通过触摸控制飞机移动
	EventListenerTouchOneByOne * event = EventListenerTouchOneByOne::create();
	event->setSwallowTouches(true);
	event->onTouchBegan = CC_CALLBACK_2(PlayerFactory::onTouchBegan, this);
	event->onTouchMoved = CC_CALLBACK_2(PlayerFactory::onTouchMoved, this);
	event->onTouchEnded = CC_CALLBACK_2(PlayerFactory::onTouchEnded, this);

	//注册
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
}
