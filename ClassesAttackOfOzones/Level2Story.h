#ifndef __LEVEL2_STORY_H__
#define __LEVEL2_STORY_H__

#include "cocos2d.h"
//Level 2 story describes the tasks to complete level2
// level2story header class  lists  method  and variables defintions 
class Level2Story: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Level2Story);

private:
	void GoToLevel2(Ref * sender);

};

#endif // __LEVEL2__STORY_H__

