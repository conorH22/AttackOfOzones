// include header files simpleaudioengine, level2, parallaxNodeExtra, gameover and level2story
#include "SimpleAudioEngine.h"
#include "Level2.h"
#include "ParallaxNodeExtras.h"
#include "GameOver.h"
#include "Level2Story.h"

using namespace CocosDenshion;// for the in house cocos audio engine
//cocos2d namespace
USING_NS_CC;
#define COCOS2D_DEBUG 1 //used for CCLOG for debugging/testing

// level2 audio
#define GAME_AUDIO "Far_The_Days_Come.mp3"
#define EXPLOSION_LARGE "explosion_large.wav"
#define BULLET "Emergency_Siren_Short_Burst.mp3"
#define ENEMY_BULLET "Crash.mp3"

int Score2;
Scene* Level2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Level2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level2::init()
{
	// super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Level2::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
	scale = visibleSize.width / 320.0f;

	//rain weather particle effect
	ParticleSystemQuad* RainEffect = ParticleSystemQuad::create("Particle_texture_raincy.plist");
	RainEffect->setPosition(Point(visibleSize.width/2-30, visibleSize.height)); //position in screen
	RainEffect->setScale(scale); //set scale for rain particle
	this->addChild(RainEffect);

	//cloud sprites added to game scene . 4 cloud sprites position in level2 at top of screen
	Sprite *cloud1Sprite = Sprite::create("dark_clouds_1.png");
	cloud1Sprite->setPosition(Point(visibleSize.width / 2, visibleSize.height - 50));
	cloud1Sprite->setScale(scale);
	cloud1Sprite->setOpacity(103.0);
	this->addChild(cloud1Sprite);

	// cloud movement using FiniteTimeAction moves to position in level2 scene
	FiniteTimeAction* cloud1ActionMove = MoveTo::create((float)visibleSize.width / 10, Point(visibleSize.width + cloud1Sprite->getTextureRect().getMaxX(), visibleSize.height - 100));
	FiniteTimeAction* cloud1ActionMoveDone = CallFuncN::create(this, callfuncN_selector(Level2::cloudy1SpriteMoveFinished));
	cloud1Sprite->runAction(Sequence::create(cloud1ActionMove, cloud1ActionMoveDone, NULL));


	Sprite *cloud2Sprite = Sprite::create("dark_clouds_2.png");
	cloud2Sprite->setPosition(Point(0, visibleSize.height - 100));
	cloud2Sprite->setScale(scale);
	cloud2Sprite->setOpacity(103.0);
	this->addChild(cloud2Sprite);

	FiniteTimeAction* cloud2ActionMove = MoveTo::create((float)visibleSize.width / 6, Point(visibleSize.width + cloud2Sprite->getTextureRect().getMaxX(), visibleSize.height - 100));
	FiniteTimeAction* cloud2ActionMoveDone = CallFuncN::create(this, callfuncN_selector(Level2::cloudy2SpriteMoveFinished));
	cloud2Sprite->runAction(Sequence::create(cloud2ActionMove, cloud2ActionMoveDone, NULL));


	Sprite *cloud3Sprite = Sprite::create("dark_clouds_3.png");
	cloud3Sprite->setPosition(Point(visibleSize.width / 2 * -1, visibleSize.height - 150));
	cloud3Sprite->setScale(scale);
	cloud3Sprite->setOpacity(103.0);
	this->addChild(cloud3Sprite);

	FiniteTimeAction* cloud3ActionMove = MoveTo::create((float)visibleSize.width / 4, Point(visibleSize.width + cloud3Sprite->getTextureRect().getMaxX(), visibleSize.height - 100));
	FiniteTimeAction* cloud3ActionMoveDone = CallFuncN::create(this, callfuncN_selector(Level2::cloudy3SpriteMoveFinished));
	cloud3Sprite->runAction(Sequence::create(cloud3ActionMove, cloud3ActionMoveDone, NULL));


	Sprite *cloud4Sprite = Sprite::create("dark_clouds_4.png");
	cloud4Sprite->setPosition(ccp(visibleSize.width*-1, visibleSize.height - 200));
	cloud4Sprite->setScale(scale);
	cloud4Sprite->setOpacity(103.0);
	this->addChild(cloud4Sprite);

	FiniteTimeAction* cloud4ActionMove = MoveTo::create((float)visibleSize.width / 8, ccp(visibleSize.width + cloud4Sprite->getTextureRect().getMaxX(), visibleSize.height - 100));
	FiniteTimeAction* cloud4ActionMoveDone = CallFuncN::create(this, callfuncN_selector(Level2::cloudy4SpriteMoveFinished));
	cloud4Sprite->runAction(Sequence::create(cloud4ActionMove, cloud4ActionMoveDone, NULL));

   //player ship created using sprite, position and added to scene 
	player = Sprite::create("Player1.png");
	player->setPosition(Vec2(visibleSize.width/2.4f, visibleSize.height/2.2f));

	this->addChild(player);

	// Create the ParallaxNode
	_backgroundNode = ParallaxNodeExtras::create();
	this->addChild(_backgroundNode, -1);

	// Create the sprites will be added to the ParallaxNode
	_spaceDust1 = Sprite::create("landscape.png");
	_spaceDust2 = Sprite::create("landscape.png");
	

	//Determine relative movement speeds for space dust and background
	auto dustSpeed = Point(0.1F, 0.1F);
	auto bgSpeed = Point(0.05F, 0.05F);

	// Add children to ParallaxNode
	_backgroundNode->addChild(_spaceDust1, 0, dustSpeed, Point(0, visibleSize.height/2));
	_backgroundNode->addChild(_spaceDust2, 0, dustSpeed, Point(_spaceDust1->getContentSize().width, visibleSize.height/2));
	

	
	// timer label for level2 

	const float timerFontSize = 2;
	const float timerPostitionX = 24;
	const float timerPostitionY = 12;
	CountDown = 120;
	String * temptimer = String::createWithFormat("Time Remaining:%i", CountDown);

	TimerLabel = Label::create(temptimer->getCString(), "fonts/Marker felt.tff", visibleSize.height * 0.1);
	TimerLabel->setColor(Color3B::RED);
	TimerLabel->setAnchorPoint(Vec2(0, 1));
	TimerLabel->setPosition(visibleSize.width * 0.3, visibleSize.height* 1.0);
	TimerLabel->setScale(0.5f);

	this->addChild(TimerLabel, 1);
	this->schedule(schedule_selector(Level2::UpdateTimer), 1); //added to scene/schedule_selector
	this->scheduleUpdate();


	// enemy vector that loads enemy image for level2 enemy sprite
#define ENEMYARMYNUM 20
	_enemies = new Vector<Sprite*>(ENEMYARMYNUM);
	for (int i = 0; i < ENEMYARMYNUM; ++i) {
		auto *enemy2 = Sprite::create("Boss2.png");
		enemy2->setVisible(false);
		this->addChild(enemy2);
		_enemies->pushBack(enemy2);
	}
	/*this->schedule(schedule_selector(Level1::addEnemy), 1);
	this->scheduleUpdate();*/
	// player laser bullets, using green laser image
#define LASERSNUM 10
	_shipLasers = new Vector<Sprite*>(LASERSNUM);
	for (int i = 0; i < LASERSNUM; ++i) {
		auto shipLaser = Sprite::create("GreenLaser.png");
		shipLaser->setVisible(false);
		this->addChild(shipLaser);
		_shipLasers->pushBack(shipLaser);
	}
	//enemy lasers using redbeam laser image
	_EnemyLasers = new Vector<Sprite*>(LASERSNUM);
	for (int i = 0; i < LASERSNUM; ++i) {
		auto EnemyLaser = Sprite::create("RedBeam.png");
		EnemyLaser->setVisible(false);
		
		this->addChild(EnemyLaser);
		_EnemyLasers->pushBack(EnemyLaser);
	}
	// device sets acceleromterEnabled to true, with new Event listenerAccleration added
	Device::setAccelerometerEnabled(true);
	auto accelerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(Level2::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(accelerationListener, this);
	// new touch listener for player bullets/lasers
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = CC_CALLBACK_2(Level2::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//// keyboard listener for keyboard input switch statement is used for w,s,up and down keys
	//auto eventListener = EventListenerKeyboard::create();
	//eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

	//	Vec2 loc = event->getCurrentTarget()->getPosition();
	//	switch (keyCode) {
	//	/*case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	//	case EventKeyboard::KeyCode::KEY_A:
	//		event->getCurrentTarget()->setPosition(--loc.x-=12, loc.y);
	//		break;
	//	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	//	case EventKeyboard::KeyCode::KEY_D:
	//		event->getCurrentTarget()->setPosition(++loc.x+=12, loc.y);
	//		break;*/
	//	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	//	case EventKeyboard::KeyCode::KEY_W:
	//		event->getCurrentTarget()->setPosition(loc.x, ++loc.y+=52);
	//		break;
	//	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	//	case EventKeyboard::KeyCode::KEY_S:
	//		event->getCurrentTarget()->setPosition(loc.x, --loc.y-=52);
	//		break;
	//	}
	//};

	//this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, player);

	//level 2 lives label
	_lives = 6;
	String * tempLives = String::createWithFormat("Lives:%d", _lives);
	LivesLabel = Label::create(tempLives->getCString(), "fonts/Marker felt.tff", visibleSize.height* 0.1);
	LivesLabel->setColor(Color3B::RED);
	LivesLabel->setAnchorPoint(Vec2(0, 1));
	LivesLabel->setPosition(visibleSize.width / 12.3 + origin.x, visibleSize.height * 1.0);
	LivesLabel->setScale(0.5f);
	this->addChild(LivesLabel, 1000);
	double curTime = getTimeTick();
	_gameOverTime = curTime + 200000;

	//level2 score label
	const float ScoreFontSize = 2;
	const float ScorePositionX = 24;
	const float ScorepositionY = 12;
	Score2 = 0;
	String * tempScore = String::createWithFormat("Score:%i", Score2);
	ScoreLabel = Label::create(tempScore->getCString(), "fonts/Marker felt.tff", visibleSize.height* 0.1);
	ScoreLabel->setColor(Color3B::RED);
	ScoreLabel->setAnchorPoint(Vec2(0, 1));
	ScoreLabel->setPosition(visibleSize.width / 1.2 + origin.x, visibleSize.height * 1.0);
	ScoreLabel->setScale(0.5f);
	this->addChild(ScoreLabel, 1000);

	this->scheduleUpdate();
	this->schedule(schedule_selector(Level2::enemybullets), 2.0f);
	
	//this->schedule(schedule_selector(HelloWorld::UpdateTimer), 1.0f);
	// level 2 game audio 
	SimpleAudioEngine::getInstance()->playBackgroundMusic(GAME_AUDIO, true);
	SimpleAudioEngine::getInstance()->preloadEffect(EXPLOSION_LARGE);
	SimpleAudioEngine::getInstance()->preloadEffect(BULLET);
	SimpleAudioEngine::getInstance()->preloadEffect(ENEMY_BULLET);

	return true;
}
// timer method 
void Level2::UpdateTimer(float dt)
{
	CountDown--;
	String * tempTimer = String::createWithFormat("Time Remaining:%i", CountDown);
	TimerLabel->setString(tempTimer->getCString());
	TimerLabel->setScale(0.5f);
	//if  timer reaches zero new level
	if (CountDown <= 0)
	{
		Level2::endScene(LOSE2);
		this->unscheduleUpdate();
	}
}
 // move background sprites method  for clouds sprites
void Level2::moveBackgroundSprite(Node *sender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	int zorder = 0;

	if (sender != NULL) {
		zorder = sender->getZOrder();
		sender->runAction(Sequence::create(FadeOut::create(4), RemoveSelf::create(), NULL));
	}


	Sprite *bgSprite = Sprite::createWithTexture(bgTexture);
	float bgSpritespx = bgTexture->getContentSize().width;
	float bgSpritespy = bgTexture->getContentSize().height;

	//Set the bg location
	bgSprite->setPosition(ccp(0,visibleSize.height / 2));
	bgSprite->setScaleX(visibleSize.width / bgSpritespx * 2);//Enlarge the width by a factor of 2
	bgSprite->setScaleY(visibleSize.height / bgSpritespy);

	this->addChild(bgSprite, zorder - 1);
	// finiteTimeaction to move top point/position in level2
	FiniteTimeAction* actionMove = MoveTo::create((float)visibleSize.width / 5, Point(visibleSize.width, visibleSize.height / 2));
	FiniteTimeAction* actionMoveDone =CallFuncN::create(this, callfuncN_selector(Level2::moveBackgroundSprite));
	bgSprite->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}
// method for cloud one 
void Level2::cloudy1SpriteMoveFinished(Node *sender)
{
	Sprite *cloud1Sprite = (Sprite *)sender;
	float bgSpritespx = cloud1Sprite->getTextureRect().getMaxX();
	Size size = Director::sharedDirector()->getWinSize(); //Screen size
	cloud1Sprite->setPosition(ccp(size.width - bgSpritespx - bgSpritespx, size.height - 50));
	//Cloud 1 moves
	FiniteTimeAction* cloud1ActionMove = MoveTo::create((float)size.width / 5, ccp(size.width + bgSpritespx, size.height - 50));
	FiniteTimeAction* cloud1ActionMoveDone = CallFuncN::create(this, callfuncN_selector(Level2::cloudy1SpriteMoveFinished));
	cloud1Sprite->runAction(Sequence::create(cloud1ActionMove, cloud1ActionMoveDone, NULL));
}
// method for cloud two 
void Level2::cloudy2SpriteMoveFinished(Node *sender)
{
	Sprite *cloud1Sprite = (Sprite *)sender;
	float bgSpritespx = cloud1Sprite->getTextureRect().getMaxX();
	Size size = Director::sharedDirector()->getWinSize(); // The screen size
	cloud1Sprite->setPosition(ccp(size.width - bgSpritespx - bgSpritespx, size.height - 50));
	//Cloud 1 moves
	FiniteTimeAction* cloud1ActionMove = MoveTo::create((float)size.width / 8, ccp(size.width + bgSpritespx, size.height - 50));
	FiniteTimeAction* cloud1ActionMoveDone = CallFuncN::create(this, callfuncN_selector(Level2::cloudy1SpriteMoveFinished));
	cloud1Sprite->runAction(Sequence::create(cloud1ActionMove, cloud1ActionMoveDone, NULL));
}
//method for cloud three
void Level2::cloudy3SpriteMoveFinished(Node *sender)
{
	Sprite *cloud1Sprite = (Sprite *)sender;
	float bgSpritespx = cloud1Sprite->getTextureRect().getMaxX();
	Size size = Director::sharedDirector()->getWinSize(); //The screen size
	cloud1Sprite->setPosition(ccp(size.width - bgSpritespx - bgSpritespx, size.height - 50));
	//Cloud 1 moves
	FiniteTimeAction* cloud1ActionMove = MoveTo::create((float)size.width / 5, ccp(size.width + bgSpritespx, size.height - 50));
	FiniteTimeAction* cloud1ActionMoveDone = CallFuncN::create(this, callfuncN_selector(Level2::cloudy1SpriteMoveFinished));
	cloud1Sprite->runAction(Sequence::create(cloud1ActionMove, cloud1ActionMoveDone, NULL));
}
//method for cloud four
void Level2::cloudy4SpriteMoveFinished(Node *sender)
{
	Sprite *cloud1Sprite = (Sprite *)sender;
	float bgSpritespx = cloud1Sprite->getTextureRect().getMaxX();
	Size size = Director::sharedDirector()->getWinSize();
	cloud1Sprite->setPosition(ccp(size.width - bgSpritespx - bgSpritespx, size.height - 50));

	FiniteTimeAction* cloud1ActionMove = MoveTo::create((float)size.width / 8, ccp(size.width + bgSpritespx, size.height - 50));
	FiniteTimeAction* cloud1ActionMoveDone = CallFuncN::create(this, callfuncN_selector(Level2::cloudy1SpriteMoveFinished));
	cloud1Sprite->runAction(Sequence::create(cloud1ActionMove, cloud1ActionMoveDone, NULL));
}


// key board press  message in CCLOG
void Level2::onkeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	CCLOG("Key with keycode %d released", keyCode);

}
// key board release  message in CCLOG
void Level2::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	CCLOG("Key with keycode %d released", keyCode);

}

// update method for level2 background movement/parallax scrolling, collison detection for player, enemies, laser bullets
void Level2::update(float dt)
{
	auto backgroundScrollVert = Point(-1000, 0);
	_backgroundNode->setPosition(_backgroundNode->getPosition() + (backgroundScrollVert * dt));

	

	//Parallax
	auto spaceDusts = new Vector<Sprite*>(2);
	spaceDusts->pushBack(_spaceDust1);
	spaceDusts->pushBack(_spaceDust2);
	for (auto spaceDust : *spaceDusts) {
		float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x;
		float size = spaceDust->getContentSize().width;
		if (xPosition < -size / 2) {
			_backgroundNode->incrementOffset(Point(spaceDust->getContentSize().width * 2, 0), spaceDust);
		}
	}


	//Acceleration
	Size winSize = Director::getInstance()->getWinSize();
	float maxY = winSize.height - player->getContentSize().height / 2;
	float minY = player->getContentSize().height / 2;
	float diff = (_shipPointsPerSecY * dt);
	float newY = player->getPosition().y + diff;
	newY = MIN(MAX(newY, minY), maxY);
	player->setPosition(player->getPosition().x, newY);

	float curTimeMillis = getTimeTick();
	if (curTimeMillis > _nextEnemySpawn) {

		float randMillisecs = randomValueBetween(0.20F, 0.9F) * 1000;
		_nextEnemySpawn = randMillisecs + curTimeMillis;

		float randY = randomValueBetween(0.0F, winSize.height);
		float randDuration = randomValueBetween(3.0F, 5.0F);

		enemy2 = _enemies->at(_nextEnemy);
		_nextEnemy++;

		if (_nextEnemy >= _enemies->size())
			_nextEnemy = 0;

		enemy2->stopAllActions();
		enemy2->setPosition(winSize.width + enemy2->getContentSize().width / 2, randY);
		enemy2->setVisible(true);
		enemy2->runAction(
			Sequence::create(
				MoveBy::create(randDuration, Point(-winSize.width - enemy2->getContentSize().width, 0)),
				MoveBy::create(randDuration, Point(winSize.width - enemy2->getContentSize().width, 0)),
				CallFuncN::create(CC_CALLBACK_1(Level2::setInvisible, this)),
				NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
		);
	}
	// Enemies type level 1
	for (auto enemy2 : *_enemies) {
		if (!(enemy2->isVisible()))
			continue;
		for (auto shipLaser : *_shipLasers) {
			if (!(shipLaser->isVisible()))
				continue;
			if (shipLaser->getBoundingBox().intersectsRect(enemy2->getBoundingBox())) {
				ParticleSystemQuad*particleEnemyCollision = CCParticleSystemQuad::create("particle_textureEnemydeath.plist");
				particleEnemyCollision->setPosition(enemy2->getPosition());
				particleEnemyCollision->setAutoRemoveOnFinish(true);
				this->addChild(particleEnemyCollision);
				SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_LARGE);
				shipLaser->setVisible(false);
				enemy2->setVisible(false);
				Score2++;

				String * tempScore = String::createWithFormat("Score:%i", Score2);
				ScoreLabel->setString(tempScore->getCString());
				ScoreLabel->setScale(0.5f);
				if (Score2 == 60)
				{
					auto scene = GameOver::createScene();
					Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));
				}
			}
		}
		for (auto EnemyLaser : *_EnemyLasers) {
			if (!(EnemyLaser->isVisible()))
				continue;
			if (EnemyLaser->getBoundingBox().intersectsRect(player->getBoundingBox())) {
				ParticleSystemQuad*particleEnemyCollision = ParticleSystemQuad::create("particle_textureEnemydeath.plist");
				particleEnemyCollision->setPosition(player->getPosition());
				particleEnemyCollision->setAutoRemoveOnFinish(true);
				this->addChild(particleEnemyCollision);
				SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_LARGE);
				EnemyLaser->setVisible(false);
				//player->setVisible(false);
				player->runAction(Blink::create(1.0F, 4));
				_lives--;
				String * tempLives = String::createWithFormat("Lives:%d", _lives);
				LivesLabel->setString(tempLives->getCString());
				LivesLabel->setScale(0.5f);
			}
		}

		if (player->getBoundingBox().intersectsRect(enemy2->getBoundingBox())) {
			enemy2->setVisible(false);
			//player->runAction(Blink::create(1.0F, 4));
			_lives--;
			String * tempLives = String::createWithFormat("Lives:%d", _lives);
			LivesLabel->setString(tempLives->getCString());
			LivesLabel->setScale(0.5f);
		}
	}

	if (_lives <= 0) {
		player->stopAllActions();
		player->setVisible(false);
		this->endScene(LOSE2);
	}
	else if (curTimeMillis >= _gameOverTime) {
		this->endScene(WIN2);
	}
}
// level2 acceleration method for android tilt controls
void Level2::onAcceleration(Acceleration* acc, Event* event) {
#define FILTERINGFACTOR 0.1
#define RESTACCELX -0.6
#define SHIPMAXPOINTSPERSEC (winSize.height*0.5)        
#define MAXDIFFX 0.2

	double rollingX;

	// Cocos2DX inverts X and Y accelerometer depending on device orientation
	// in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
	acc->x = acc->y;
	acc->z;
	rollingX = (acc->x * FILTERINGFACTOR) + (rollingX * (1.0 - FILTERINGFACTOR));
	float accelX = acc->x - rollingX;
	Size winSize = Director::getInstance()->getWinSize();
	float accelDiff = accelX - RESTACCELX;
	float accelFraction = accelDiff / MAXDIFFX;
	_shipPointsPerSecY = SHIPMAXPOINTSPERSEC * accelFraction;
}
// random  method in level2
float Level2::randomValueBetween(float low, float high) {
	// from http://stackoverflow.com/questions/686353/c-random-float-number-generation
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}
// get time for update method and timed events in level2
float Level2::getTimeTick() {
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float)millisecs;
}
// set invisible  method when objects have been collided with
void Level2::setInvisible(Node * node) {
	node->setVisible(false);
}
// enemy bullets methods (AI) what happens to enemy bullets
void Level2::enemybullets(float dt)
{

	SimpleAudioEngine::getInstance()->playEffect(ENEMY_BULLET);
	auto winSize = Director::getInstance()->getWinSize();
	auto EnemyLaserz = _EnemyLasers->at(_nextEnemyLaser++);
	if (_nextEnemyLaser >= _EnemyLasers->size())
		_nextEnemyLaser = 0;
	EnemyLaserz->setPosition(enemy2->getPosition() + Point(EnemyLaserz->getContentSize().width / 2, 0));
	EnemyLaserz->setVisible(true);
	EnemyLaserz->stopAllActions();
	EnemyLaserz->runAction(
		Sequence::create(
			MoveBy::create(1, Point(-winSize.width, 0)),  // enemy bullets move from right to left towards player
			CallFuncN::create(CC_CALLBACK_1(Level2::setInvisible, this)),
			NULL));
}


// on touch began for player bullets
void Level2::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event) {
	SimpleAudioEngine::getInstance()->playEffect(BULLET);
	auto winSize = Director::getInstance()->getWinSize();
	auto shipLaser = _shipLasers->at(_nextShipLaser++);
	if (_nextShipLaser >= _shipLasers->size())
		_nextShipLaser = 0;
	shipLaser->setPosition(player->getPosition() + Point(shipLaser->getContentSize().width / 2, 0));
	//shipLaser->setPosition(player->getPosition() + Point(shipLaser->getContentSize().width / 3, 0));
	shipLaser->setVisible(true);
	shipLaser->stopAllActions();
	shipLaser->runAction(
		Sequence::create(
			MoveBy::create(0.5, Point(winSize.width, 0)),
			//MoveBy::create(0.5, Point(-winSize.width, 0)),
			CallFuncN::create(CC_CALLBACK_1(Level2::setInvisible, this)),
			NULL));
}
// when player select restart , this is method is called
void Level2::restartTapped(Ref* pSender) {
	Director::getInstance()->replaceScene
	(TransitionZoomFlipX::create(0.5, this->createScene()));
	// reschedule
	this->scheduleUpdate();
}
// end game for level2 when timer goes to zero or lives go to zero
void Level2::endScene(EndReason2 endReason2) {
	if (_gameOver)
		return;
	_gameOver = true;

	auto winSize = Director::getInstance()->getWinSize();
	char message[10] = "You Win";
	if (endReason2 == LOSE2)
		strcpy(message, "You Lose");
	auto label = Label::createWithBMFont("Arial.fnt", message);
	label->setScale(0.1F);
	label->setColor(Color3B::RED);
	label->setPosition(winSize.width / 2, winSize.height*0.6F);
	this->addChild(label);

	strcpy(message, "Restart");
	auto restartLabel = Label::createWithBMFont("Arial.fnt", message);
	restartLabel->setColor(Color3B::RED);
	auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_1(Level2::restartTapped, this));
	restartItem->setScale(0.1F);
	restartItem->setPosition(winSize.width / 2, winSize.height*0.4);

	auto *menu = Menu::create(restartItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	// clear label and menu
	restartItem->runAction(ScaleTo::create(0.5F, 1.0F));
	label->runAction(ScaleTo::create(0.5F, 1.0F));

	// Terminate update callback
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(Level2::UpdateTimer));
}
// score methods to set score, getis score and get score
void Level2::SetIsScored()
{
	scored = true;
}

bool Level2::GetIsScored()
{
	return scored;
}

int Level2::GetScore()
{
	CCLOG("Score %d", Score2);
	return Score2;
}

// this make x button close game
void Level2::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}