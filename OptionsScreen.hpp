#pragma once
#include "cocos2d.h"

class OptionsScreen : public cocos2d::Layer {
public:
	OptionsScreen();
	~OptionsScreen();

	static cocos2d::Scene* createScene();
	bool init();
	CREATE_FUNC(OptionsScreen);
};

