//includes header files from level2story, level1 , simpleaudioengine and level2
#include "Level2Story.h"
#include "Level1.h"
#include "SimpleAudioEngine.h"
#include "Level2.h"



// level2story background music
#define BACKGROUND_AUDIO "Drizzle_to_Downpour.mp3"



using namespace CocosDenshion;// for the in house cocos audio engine

// cocos2d namespace
USING_NS_CC;
#define SPLASH_SCREEN_SOUND_SFX "menu.mp3"//sound for the splash screen
Scene* Level2Story::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Level2Story::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level2Story::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("LEVEL TWO ", "fonts/Marker Felt.ttf", 48);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 1.1));
	label->setColor(ccc3(255, 0, 0));
	this->addChild(label, 1);

	// labels for level2 instructions, story, and controls, with position and colour on screen
	auto label1 = Label::createWithTTF(" INSTRUCTIONS: kill 60 enemies to progress to Complete Game!!\n watch out for the  enemies from behind you!!! and enemy lasers\n you have 2 minutes to complete the level and have 6 lives", "fonts/Marker Felt.ttf", 36);
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 1.4));
	label1->setColor(ccc3(255, 0, 0));
	this->addChild(label1, 1);

	auto label2 = Label::createWithTTF(" LEVEL2 STORY: After sucessfully destroying the first wave of enemies,\n Level 2 is set in the forest region of blackmor,\n You must fight the elite unit from Planet OZONES called staros,\n Staros ships are faster and larger unit than the Ozonies  ", "fonts/Marker Felt.ttf", 36);
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 1.8));
	label2->setColor(ccc3(255, 0, 0));
	this->addChild(label2, 1);

	auto label3 = Label::createWithTTF(" PC CONTROLS: USE W,S keys to move PLAYER up and down in game and\n Use mouse/touchpad click to fire lasers\n ANDROID CONTROLS: Tilt phone up and down to move player in game and tap screen to fire lasers\n ", "fonts/Marker Felt.ttf", 36);
	label3->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 3.0));
	label3->setColor(ccc3(255, 0, 0));
	this->addChild(label3, 1);
	// play icon/button goes to level2
	auto story = MenuItemImage::create("Play.png", "Play.png", CC_CALLBACK_1(Level2Story::GoToLevel2, this));
	story->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 6 + origin.y));

	auto storyButton = Menu::create(story, NULL);
	storyButton->setPosition(Point::ZERO);
	this->addChild(storyButton);
	//keep playing from the main menu
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_AUDIO, true);

	return true;

}
// this is called when play button is clicked
void Level2Story::GoToLevel2(Ref * sender)
{
	auto scene = Level2::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));

}
