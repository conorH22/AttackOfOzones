 //Level 1 class file
//Conor Holmes
//date: 15/02/17

//class definition and include files from cocos2d and ParallaxNodeExtra class
// cocos 2d name USING_NS_CC is used
// typedef enum is used  contains WIN and LOSE
#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include "cocos2d.h"
#include "ParallaxNodeExtras.h"

USING_NS_CC;

typedef enum {
	WIN,
	LOSE
} EndReason;

class Level1 : public Layer
{
	// public level 1 class definitions  static cocos2d::Scene new pointer createScene()
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // CREATE_FUNC(Leevel1) implements the "static create()" method manually
    CREATE_FUNC(Level1);

	/* class methods in level1 dewfined below initialized  in level1.cpp file
	 *  methods defined are onAcceleration, randomValuebetween, SetInvisible, float getTimeTick
	 *  add Enemy, onTouchesBegan, OnKeyPressed, onKeyReleased, Scored, SetIsScored, GetIsScored,GetScore
	 *  CountDown*/
	virtual void onAcceleration(Acceleration* acc, Event* event);
	float randomValueBetween(float low, float high);
	void setInvisible(Node * node);
	float getTimeTick();
	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	virtual void onkeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,Event* event);
	bool scored;
	void setIsScored();
	bool GetIsScored();
	int getScore();
	int CountDown;

	//// KEYBOARD INPUTS
	//const EventKeyboard::KeyCode ENTER = EventKeyboard::KeyCode::KEY_KP_ENTER;
	//const EventKeyboard::KeyCode UP_ARROW = EventKeyboard::KeyCode::KEY_UP_ARROW;
	//const EventKeyboard::KeyCode DOWN_ARROW = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	//const EventKeyboard::KeyCode LEFT_ARROW = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	//const EventKeyboard::KeyCode RIGHT_ARROW = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	const float SCALE_FACTOR = 2.0f;
	const float PLAYER_MAX_VELOCITY = 5.0f;
	const float PLAYER_JUMP_VELOCITY = 40.0f;
	const float DAMPING = 0.87f;
	// private defintions in Level1 class file
private:
	Sprite* player;
	Sprite* enemy;
	unsigned int Score1;
	//cocos2d labels in game scene for score, health, Lives and timer
	Label * ScoreLabel;
	Label * HealthLabel;
	Label * TimerLabel;
	Label * LivesLabel;
	// parallaxNodeExtras  pointer
	ParallaxNodeExtras *_backgroundNode;
	Sprite * ScrollingBackground1, * ScrollingBackground2;
	float _shipPointsPerSecY;
	Vector<Sprite*> *_enemies;
	int _nextEnemy=0;
	float _nextEnemySpawn=0;
	Vector<Sprite*> *_Lasers;
	Vector<Sprite*>*_EnemyLasers;
	int _nextShipLaser=0;
	int _nextEnemyLaser = 0;
	int _lives=0;
	double _gameOverTime;
	bool _gameOver=false;
	// methods defined(private) for  level1
	void update(float dt);
	void enemybullets(float dt);
	void UpdateTimer(float dt);
	void endScene(EndReason endReason);
	void restartTapped(Ref* pSender);
	
};

#endif // __LEVEL1_H__
