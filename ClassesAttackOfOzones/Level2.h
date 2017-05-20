#ifndef __LEVEL2__
#define __LEVEL2__

#include "cocos2d.h"
#include "ParallaxNodeExtras.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1

 // win/lose enums
typedef enum {
	WIN2,
	LOSE2
} EndReason2;
// class defines all methods and variables/then implemented in cpp level2 file
class Level2 : public Layer
{
	//public methods and variables
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Level2);
	Texture2D *bgTexture;

	Sprite *thunderlight1;

	Sprite *thunderlight2;

	virtual void onAcceleration(Acceleration* acc, Event* event);
	float randomValueBetween(float low, float high);
	void setInvisible(Node * node);
	float getTimeTick();
	float scale;
	void addEnemy(float dt);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	virtual void onkeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	bool scored;
	void SetIsScored();
	bool GetIsScored();
	int GetScore();
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
	// private variables and methods
private:

	Sprite* player;
	Sprite* enemy2;
	unsigned int Score2;
	//cocos2d labels in game scene for score, health and timer
	Label * ScoreLabel;
	Label * HealthLabel;
	Label * TimerLabel;
	Label * LivesLabel;

	ParallaxNodeExtras *_backgroundNode;
	Sprite *_spaceDust1, *_spaceDust2;
	float _shipPointsPerSecY;
	Vector<Sprite*> *_enemies;
	int _nextEnemy = 0;
	float _nextEnemySpawn = 0;
	Vector<Sprite*> *_shipLasers;
	Vector<Sprite*>*_EnemyLasers;
	int _nextShipLaser = 0;
	int _nextEnemyLaser = 0;
	int _lives = 0;
	double _gameOverTime;
	bool _gameOver = false;

	void update(float dt);
	void UpdateTimer(float dt);
	void endScene(EndReason2 endReason2);
	void enemybullets(float dt);
	void restartTapped(Ref* pSender);
	//void gotolevel2(Ref* psender);
	virtual void moveBackgroundSprite(Node *sender);
	virtual void cloudy1SpriteMoveFinished(Node *sender);
	virtual void cloudy2SpriteMoveFinished(Node *sender);
	virtual void cloudy3SpriteMoveFinished(Node *sender);
	virtual void cloudy4SpriteMoveFinished(Node *sender);
};

#endif // __LEVEL2__
