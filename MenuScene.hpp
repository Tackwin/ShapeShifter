#pragma once
#include "cocos2d.h"
class MenuScene : public cocos2d::Layer {
public:
	MenuScene();
	~MenuScene();

	static cocos2d::Scene* createScene();
	bool init();

	void onTouchEnded(cocos2d::Touch *t, cocos2d::Event *e);

	CREATE_FUNC(MenuScene);
};

