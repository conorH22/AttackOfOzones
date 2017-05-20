#include "AppDelegate.h"
#include "Level1.h"
#include "MainMenu.h"


//cocos2d namespace used to make code more readable and less clutter in cpp files
USING_NS_CC;
// the multiple device resolutions than can be enable 
// In this Game Attack of Ozones , full screen is enabled. the exit icon is plaed in both levels, ther player can leave application safely
static cocos2d::Size designResolution = cocos2d::Size(1350, 768);// resolution size for application
static cocos2d::Size smallResolution = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolution = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolution = cocos2d::Size(2048, 1536);

//appdelgate constructor
AppDelegate::AppDelegate() {

}
//appdelgate deconstructor
AppDelegate::~AppDelegate() 
{
}
// boolean appdidfinishlaunching checks screen size and launches My game which is called from main method
//Game/app is created with  full screen using glview
bool AppDelegate::applicationDidFinishLaunching() {
	/*sdkBox::PlugGPG::init();*/
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)||(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)|| ( CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)||(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//
//		glview = GLViewImpl::createWithRect("My Game", Rect(0, 0, designResolution.width, designResolution.height));
//#else
        glview = GLViewImpl::createWithFullScreen("My Game");
//#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS for testing debugging reasons
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = MainMenu ::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
