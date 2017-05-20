// include needed header files forlisted class methods
#include "Level1.h"
#include "SimpleAudioEngine.h"
#include "Level2.h"
#include "Level2Story.h"
#include"ParallaxNodeExtras.h"
using namespace CocosDenshion;// for the in house cocos audio engine
// namespace for cocos
USING_NS_CC;
#define COCOS2D_DEBUG 1
// level background audio and sound effect for collisions in game
//player fires lasrt siren is used/ enemy fires crash
#define GAME_AUDIO "U_Make_Me_Feel.mp3"
#define EXPLOSION_LARGE "explosion_large.wav"
#define BULLET "Emergency_Siren_Short_Burst.mp3"
#define ENEMY_BULLET "Crash.mp3"

//int Score1;
Scene* Level1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Level1::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level1::init()
{
    // super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Level1::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);


	// player sprite created using image listed as player1.pnh
	player = Sprite::create("Player1.png");
	player->setPosition(Vec2(visibleSize.width/2.4f, visibleSize.height/2.2f));
	//player added to scene
	this->addChild(player);

	// ParallaxNode creation for moving background
	_backgroundNode = ParallaxNodeExtras::create();
	this->addChild(_backgroundNode, -1); // added to the back of the scene use -1

	//sprites will be added to the ParallaxNode
	ScrollingBackground1 = Sprite::create("desert.png");
	ScrollingBackground2 = Sprite::create("desert.png");

	


	// Determine relative movement speeds for space dust and background
	auto dustSpeed = Point(0.1F, 0.1F);
	auto bgSpeed = Point(0.05F, 0.05F);

	//  Add children to ParallaxNode
	_backgroundNode->addChild(ScrollingBackground1, 0, dustSpeed, Point(0, visibleSize.height/2));
	_backgroundNode->addChild(ScrollingBackground2, 0, dustSpeed, Point(ScrollingBackground1->getContentSize().width, visibleSize.height/2));

	// counter timer size ,postitionx and postion Y
	const float timerFontSize = 2;
	const float timerPostitionX = 24;
	const float timerPostitionY = 12;
	CountDown = 120; //int CountDown given value
	String * temptimer = String::createWithFormat("Time Remaining:%i", CountDown); // string points to tempTimer
	// creation of label for timer with set position, colour, anchor point and scsale
	TimerLabel = Label::create(temptimer->getCString(), "fonts/Marker felt.tff", visibleSize.height * 0.1);
	TimerLabel ->setColor(Color3B::RED);
	TimerLabel->setAnchorPoint(Vec2(0, 1));
	TimerLabel->setPosition(visibleSize.width * 0.3, visibleSize.height* 1.0);
	TimerLabel->setScale(0.5f);
	// added to scene ever second
	this->addChild(TimerLabel, 1);
	//schedule selector call Update timer every sescond
	this->schedule(schedule_selector(Level1::UpdateTimer), 1);
	// update of schedule
	this->scheduleUpdate();


	// EnemiesArmy has value of 15 whenever the word is used 
	// new vector called sprite pointer
	// for loop goes through enemyarmy by create an enemy sprite, setvisible to false, add to scene ans push back enemy sprite
#define ENEMIESARMY 15
	_enemies = new Vector<Sprite*>(ENEMIESARMY);
	for (int i = 0; i < ENEMIESARMY; ++i) {
		auto *enemy = Sprite::create("Player2.png");
		enemy->setVisible(false);
		this->addChild(enemy);
		_enemies->pushBack(enemy);
	}
	/*this->schedule(schedule_selector(Level1::addEnemy), 1);
	this->scheduleUpdate();*/
	//similar to enemy sprite above laser creation using png image LASERS has a value of 22
#define LASERS 22
	_Lasers = new Vector<Sprite*>(LASERS);
	for (int i = 0; i < LASERS; ++i) {
		auto shipLaser = Sprite::create("GreenLaser.png");
		shipLaser->setVisible(false);
		this->addChild(shipLaser);
		_Lasers->pushBack(shipLaser);
	}
	// enemy lasers  uses redbeam
	_EnemyLasers = new Vector<Sprite*>(LASERS);
	for (int i = 0; i < LASERS; ++i) {
		auto EnemyLaser = Sprite::create("RedBeam.png");
		EnemyLaser->setVisible(false);
		//_batchNode->addChild(EnemyLaser);
		this->addChild(EnemyLaser);
		_EnemyLasers->pushBack(EnemyLaser);
	}
	// device calles setAccelerometer to true, EventListener created by calling level1 onAcceleation
	Device::setAccelerometerEnabled(true);
	auto accelerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(Level1::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(accelerationListener, this);
	// touch listener is created to scene
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = CC_CALLBACK_2(Level1::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	// key board  cont rols for windows pc W and S keys are used to simulate tilt controls
	// eventkeyboard is set up in scene
	//auto eventListener = EventListenerKeyboard::create();
	//eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
	//	// vector2 called loc gets currenttarget and getposition
	//	// switch  statement waits for  a eventkeyboard with keycode W or S 
	//	//(note Left and Right option has been not used. in relation to android tilt controls up down for android users)
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
	//		event->getCurrentTarget()->setPosition(loc.x, ++loc.y+=52); // moves up 52
	//		break;
	//	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	//	case EventKeyboard::KeyCode::KEY_S:
	//		event->getCurrentTarget()->setPosition(loc.x, --loc.y-=52); // moves down 53
	//		break;
	//	}
	//};

	//this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, player);

	// lives  int at 6 , creation of lives label with size colour, position
	_lives = 6;
	String * tempLives = String::createWithFormat("Lives:%d", _lives);
	LivesLabel = Label::create(tempLives->getCString(), "fonts/Marker felt.tff", visibleSize.height* 0.1);
	LivesLabel->setColor(Color3B::RED);
	LivesLabel->setAnchorPoint(Vec2(0, 1));
	LivesLabel->setPosition(visibleSize.width / 12.3 + origin.x, visibleSize.height * 1.0);
	LivesLabel->setScale(0.5f);
	this->addChild(LivesLabel, 1000);

	double curTime = getTimeTick();
	//_gameOverTime = curTime + 200000; used for testing
	_gameOverTime = curTime + 120000;
	// score label simiular to timer and lives label
	const float ScoreFontSize = 2;
	const float ScorePositionX = 24;
	const float ScorepositionY = 12;
	Score1 = 0; //score starts at zero
	String * tempScore = String::createWithFormat("Score:%d", Score1);
	ScoreLabel = Label::create(tempScore->getCString(), "fonts/Marker felt.tff", visibleSize.height* 0.1);
	ScoreLabel->setColor(Color3B::RED);
	ScoreLabel->setAnchorPoint(Vec2(0, 1));
	ScoreLabel->setPosition(visibleSize.width / 1.2 + origin.x, visibleSize.height * 1.0);
	ScoreLabel->setScale(0.5f);
	this->addChild(ScoreLabel, 1000);



	this->scheduleUpdate();
	this->schedule(schedule_selector(Level1::enemybullets),3.0f); // enemy bullets added tp schedule selector
	// game sounds added to level 1
	SimpleAudioEngine::getInstance()->playBackgroundMusic(GAME_AUDIO, true);
	SimpleAudioEngine::getInstance()->preloadEffect(EXPLOSION_LARGE);
	SimpleAudioEngine::getInstance()->preloadEffect(BULLET);
	SimpleAudioEngine::getInstance()->preloadEffect(ENEMY_BULLET);

    return true;
}
// timer method where it counts down from 120 to o
void Level1::UpdateTimer(float dt)
{
	CountDown--;
	String * tempTimer = String::createWithFormat("Time Remaining:%i", CountDown);
	TimerLabel->setString(tempTimer->getCString());
	TimerLabel->setScale(0.5f);
	//if  timer reaches zero new level
	if (CountDown <= 0)
	{
	//	auto scene =
	Level1::endScene(LOSE);
	this->unscheduleUpdate();
		
	}
}
// log prints key pressed and released
void Level1::onkeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	CCLOG("Key with keycode %d released", keyCode);

}

void Level1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	CCLOG("Key with keycode %d released", keyCode);

}


// update method
void Level1::update(float dt)
{
	auto backgroundScrollVert = Point(-1000, 0); //position  to -1000
	_backgroundNode->setPosition(_backgroundNode->getPosition() + (backgroundScrollVert * dt));

	//Parallax
	auto ScrollingbgUpdate = new Vector<Sprite*>(2);
	ScrollingbgUpdate->pushBack(ScrollingBackground1);
	ScrollingbgUpdate->pushBack(ScrollingBackground2);
	for (auto Scrollingbg : *ScrollingbgUpdate) {
		float xPosition = _backgroundNode->convertToWorldSpace(Scrollingbg->getPosition()).x;
		float size = Scrollingbg->getContentSize().width;
		if (xPosition < -size / 2) {
			_backgroundNode->incrementOffset(Point(Scrollingbg->getContentSize().width * 2, 0), Scrollingbg);
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

		float randMillisecs = randomValueBetween(0.20F, 1.0F) * 1000;
		_nextEnemySpawn = randMillisecs + curTimeMillis;

		float randY = randomValueBetween(0.0F, winSize.height);
		float randDuration = randomValueBetween(2.0F, 10.0F);
		// enemy movement  enemies are created to scene using vector
		enemy = _enemies->at(_nextEnemy);
		_nextEnemy++;

		if (_nextEnemy >= _enemies->size())
			_nextEnemy = 0;

		
		enemy->stopAllActions();
		enemy->setPosition(winSize.width + enemy->getContentSize().width / 2, randY);
		enemy->setVisible(true);
		enemy->runAction(
			Sequence::create(
			MoveBy::create(randDuration, Point(-winSize.width - enemy->getContentSize().width, 0)), 
			CallFuncN::create(CC_CALLBACK_1(Level1::setInvisible, this)),
			NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
			);
	}
	// Enemy collsion detections particle effect is used when laser intersectrect with enemy object
	for (auto enemy : *_enemies){
		if (!(enemy->isVisible()))
			continue;
		for (auto shipLaser : *_Lasers){
			if (!(shipLaser->isVisible()))
				continue;
			if (shipLaser->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
				ParticleSystemQuad*particleEnemyCollision = CCParticleSystemQuad::create("particle_textureEnemydeath.plist");
				particleEnemyCollision->setPosition(enemy->getPosition());
				particleEnemyCollision->setAutoRemoveOnFinish(true);
				this->addChild(particleEnemyCollision);
				SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_LARGE);
				shipLaser->setVisible(false);
				enemy->setVisible(false);
				// socre goes up by one
				Score1++;
				// score label 
				String * tempScore = String::createWithFormat("Score:%d", Score1);
				ScoreLabel->setString(tempScore->getCString());
				ScoreLabel->setScale(0.5f);
				if (Score1 == 30) // if score reaches 30 level2 replaces scene
				{
					auto scene = Level2Story::createScene();
					Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene,true));
				}
			}
		}
		// enemy laser collision with player sprite/object
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


				
		// player collides with enemy player blinks four times and minus one life
		if (player->getBoundingBox().intersectsRect(enemy->getBoundingBox())){
			enemy->setVisible(false);
		//	player->runAction(Blink::create(1.0F, 10));
			_lives--;
			String * tempLives = String::createWithFormat("Lives:%d", _lives);
			LivesLabel->setString(tempLives->getCString());
			LivesLabel->setScale(0.5f);
			
		}
	}
	// players life reaches zero game over
	if (_lives <= 0) {
		player->stopAllActions();
		player->setVisible(false);
		this->endScene(LOSE);
	}
	else if (curTimeMillis >= _gameOverTime) {
		this->endScene(WIN);
	}
}
// acceleration for  android controls
void Level1::onAcceleration(Acceleration* acc, Event* event) {
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

float Level1::randomValueBetween(float low, float high) {
	// from http://stackoverflow.com/questions/686353/c-random-float-number-generation
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}
// timer  used for update of sprites in level1
float Level1::getTimeTick() {
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float)millisecs;
}
// setInvisble to show collision has occured between sprites and lasers
void Level1::setInvisible(Node * node) {
	node->setVisible(false);
}
// enemy laser method 
void Level1::enemybullets(float dt)
{

	SimpleAudioEngine::getInstance()->playEffect(ENEMY_BULLET);
	auto winSize = Director::getInstance()->getWinSize();
	auto EnemyLaserz = _EnemyLasers->at(_nextEnemyLaser++);
	if (_nextEnemyLaser >= _EnemyLasers->size())
		_nextEnemyLaser = 0;
	EnemyLaserz->setPosition(enemy->getPosition() + Point(EnemyLaserz->getContentSize().width / 2, 0));
	EnemyLaserz->setVisible(true);
	EnemyLaserz->stopAllActions();
	EnemyLaserz->runAction(
		Sequence::create(
			MoveBy::create(1.5, Point(-winSize.width, 0)),
			CallFuncN::create(CC_CALLBACK_1(Level1::setInvisible, this)),
			NULL));



}

// touch screen to start firing laser bullets
void Level1::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event){
	SimpleAudioEngine::getInstance()->playEffect(BULLET);
	auto winSize = Director::getInstance()->getWinSize();
	auto shipLaser = _Lasers->at(_nextShipLaser++);
	if (_nextShipLaser >= _Lasers->size())
		_nextShipLaser = 0;
	shipLaser->setPosition(player->getPosition() + Point(shipLaser->getContentSize().width / 2, 0));
	shipLaser->setVisible(true);
	shipLaser->stopAllActions();
	shipLaser->runAction(
		Sequence::create(
		MoveBy::create(0.5, Point(winSize.width, 0)), 
		CallFuncN::create(CC_CALLBACK_1(Level1::setInvisible, this)),
		NULL));
}
// restart method that starts game back at the start of level1
void Level1::restartTapped(Ref* pSender) {
	Director::getInstance()->replaceScene
		(TransitionZoomFlipX::create(0.5, this->createScene()));
	// reschedule
	this->scheduleUpdate();
}
// end scene if player runs out of time or loses all lives during the level
void Level1::endScene(EndReason endReason) {
	if (_gameOver)
		return;
	_gameOver = true;

	auto winSize = Director::getInstance()->getWinSize();
	char message[10] = "You Win";
	if (endReason == LOSE)
		strcpy(message, "You Lose");
	auto label = Label::createWithBMFont("Arial.fnt", message);
	label->setScale(0.1F);
	label->setColor(Color3B::RED);
	label->setPosition(winSize.width / 2, winSize.height*0.6F);
	this->addChild(label);

	strcpy(message, "Restart");
	auto restartLabel = Label::createWithBMFont("Arial.fnt", message);
	restartLabel->setColor(Color3B::RED);
	auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_1(Level1::restartTapped, this));
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
	this->unschedule(schedule_selector(Level1::UpdateTimer));

}
// set score
void Level1::setIsScored() {
	scored = true;
}
// get score
bool Level1::GetIsScored() {
	return scored;
}
//get score for cclog
int Level1::getScore() {
	CCLOG("Score %d", Score1);
	return Score1;
}

// this make x button close game
void Level1::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
