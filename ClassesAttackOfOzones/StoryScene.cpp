// includes header files storyscene.h, MainMenu.h simpleaudioEngine.h and Level1
#include "StoryScene.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h" // used for background audio
#include "Level1.h"

//background audio
#define BACKGROUND_AUDIO "Drizzle_to_Downpour.mp3"


using namespace CocosDenshion;// for the in house cocos audio engine
//namespace for cocos2d
USING_NS_CC;
//scene points to storyscene createscene method
Scene* StoryScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StoryScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StoryScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(StoryScene::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	auto label = Label::createWithTTF("LEVEL ONE INSTRUCTIONS & BACKSTORY ", "fonts/Marker Felt.ttf", 48);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 1.1));
	label->setColor(ccc3(255, 0, 0));
	this->addChild(label, 1);

	// label 1 that included text  to be displayed on screen before level1 to inform the player
	auto label1 = Label::createWithTTF("\nINSTRUCTIONS kill 30 enemies to progress to the next level...\n watch out for the  enemy ships and stray bullets\n you have 2 minutes to complete the level and have 6 lives", "fonts/Marker Felt.ttf", 36);
	label1->setPosition(Vec2(origin.x + visibleSize.width /2.2, origin.y + visibleSize.height / 1.3));
	label1->setColor(ccc3(255, 0, 0));
	this->addChild(label1, 1);
	// backstory label for backstory text
	auto label2 = Label::createWithTTF(" BACKSTORY: Your home planet Icures has been at war for last few years,\n you control the last remaining ship of your fleet,\n this final battle is set in the Sandbeag region\n after your planet has been taken over by the giant army from the Planet OZONES,\n  the first unit you face is ozonizes(circular ships), this unit  is slow in speed and fires lasers\n and has been given orders to crash into to your ship. \n ", "fonts/Marker Felt.ttf", 36);
	label2->setPosition(Vec2(origin.x + visibleSize.width /2.2, origin.y + visibleSize.height / 2.0));
	label2->setColor(ccc3(255, 0, 0));
	this->addChild(label2, 1);
	// controls for pc and android 
	auto label3 = Label::createWithTTF("  PC CONTROLS: Use W,S keys to move PLAYER up and down in game and\nUse mouse/touchpad click to fire lasers\n  ANDROID CONTROLS:Tilt phone up and down to move player in game and tap screen to fire lasers\n ", "fonts/Marker Felt.ttf", 36);
	label3->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 3.3));
	label3->setColor(ccc3(255, 0, 0));
	this->addChild(label3, 1);
	                  // play button goes to level1 using the goToLevel1
	auto story = MenuItemImage::create("Play.png", "Play.png", CC_CALLBACK_1(StoryScene::GoToLevel1, this));
	story->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 7.4 + origin.y));

	auto storyButton = Menu::create(story, NULL);
	storyButton->setPosition(Point::ZERO);
	this->addChild(storyButton);
	// background audio for storyscene
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_AUDIO, true);
	// return true
	return true;

}
// gotolevel1 method director replaces current scene with level one
void StoryScene::GoToLevel1(Ref * sender)
{
	auto scene = Level1::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene,true));

}


// this make x button close game
void StoryScene::menuCloseCallback(Ref* pSender)
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

