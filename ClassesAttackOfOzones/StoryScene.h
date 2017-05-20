#ifndef __STORY_SCENE_H__
#define __STORY_SCENE_H__

#include "cocos2d.h"
// story scene header file  method definitions public and private
//cocos2d is  included in this header file
class StoryScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	


	// implement the "static create()" method manually
	CREATE_FUNC(StoryScene);

private:
	void GoToLevel1(Ref * sender);
	void menuCloseCallback(Ref* pSender);


};

#endif // __STORY_SCENE_H__

