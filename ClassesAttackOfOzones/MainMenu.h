#ifndef _MAIN_MENU_
#define _MAIN_MENU_
#define TRANSACTION_DURATION 0.8f
#include "cocos2d.h"
// uses namespace cocos2d used for layout of code readabilty
USING_NS_CC;
//class MainMenu defines main menu for the cocos2d-x game
class MainMenu : public Layer
{
	//static scene points to createScene()
public:
	static cocos2d::Scene* createScene();
	//bool init 
	virtual bool init();

	//implement the static create() method manually
	CREATE_FUNC(MainMenu);
private:
	 // got game/level1
	void GoToGame(Ref *sender);
	// menuclosecallback used for the exit button to safely exit cocos appilication
	void menuCloseCallback(cocos2d::Ref* sender);
	//void GoToLevel1(Ref *sender);
	//void GotToLevel2(Ref *sender);

};
#endif // !_MAIN_MENU_

