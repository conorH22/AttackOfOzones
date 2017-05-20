#include "MainMenu.h"  // mainmenu header file included in this cpp file
#include "Level1.h"  // level1 header file include to cpp  
#include "StoryScene.h" // story scene header file calls backstory and level one instructions
#include "SimpleAudioEngine.h" // audio engine for cocos2d


#define BACKGROUND_AUDIO "Drizzle_to_Downpour.mp3"


using namespace CocosDenshion;// for the in house cocos audio engine
 
USING_NS_CC;
// scene points to createscene method from MainMenu
Scene* MainMenu::createScene()
{
	// new cocos scene
	auto scene = Scene::create();
	// scene adds layer to game scene
	auto layer = MainMenu::create();
	scene->addChild(layer); //scene addchild (layer)
	return scene;
	
}
// mainMenu init bool checks if layer exists if not return false
bool MainMenu::init()
{
	//super init()
	if (!Layer::init())
	{
		return false;
	}
	// visibleSize  gets the director that handles all scene to get visibleSize
	// origins call s the director to getVisivible orgin
	Size visibleSize = Director::getInstance()->getVisibleSize();//init size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//init the origin
	//  background image  sprite for  menu
	auto backgroundSprite = Sprite::create("Flag of xexes.png"); //main menu image
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.2 + origin.y)); //posiotion of background sprite
	this->addChild(backgroundSprite); // adds bacgroundsprite to scene
	// game title sprite
	auto titleSprite = Sprite::create("Title.png");// title image
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)); //position of title sprite
	this->addChild(titleSprite); // add title sprite to scene
	//play menu image using play png image used when click cc_callback  calls menu go to game
	auto playGameScene = MenuItemImage::create("Play.png", "Play.png", CC_CALLBACK_1(MainMenu::GoToGame, this)); 
	playGameScene->setPosition(Point(visibleSize.width /5 + origin.x, visibleSize.height / 4 + origin.y)); // set play button position  in scene
	//exit button that create aexit image and calls the  method menuclosecallback
	auto closeGame = MenuItemImage::create("Exitbutton.png", "Exitbutton.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	closeGame->setPosition(Point(visibleSize.width / 1.3 + origin.x, visibleSize.height / 4 + origin.y));// exit button position in scene

	 //play button calls menu class to create the play button
	auto PlayButton = Menu::create(playGameScene, NULL);
	PlayButton->setPosition(Point::ZERO);
	this->addChild(PlayButton);
	//exit button calls menu class to create the play button
	auto exitButton = Menu::create(closeGame, NULL);
	exitButton->setPosition(Point::ZERO);
	this->addChild(exitButton);
	// background audio is called and plays on start up of scene
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_AUDIO, true);
	//true is return as init is bool
	return true;
}
// this method calls the director class to replace this scene wiht storyscene, tranisition effect is used , page turn for 1 second
void MainMenu::GoToGame(Ref *sender)
{
	auto scene = StoryScene::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene,true));
}
// this method is called for exit button, director close application 
void MainMenu::menuCloseCallback(Ref *sender)
{
	Director::getInstance()->end();
}



