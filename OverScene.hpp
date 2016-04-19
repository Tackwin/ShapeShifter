#pragma once
#include "cocos2d.h"

class OverScene : public cocos2d::Layer {
public:
	OverScene();
	~OverScene();

	static cocos2d::Scene* createScene(int score);
	bool init(int score);
	static OverScene* create(int score) {
		OverScene* pRet = new(std::nothrow) OverScene();
		if(pRet && pRet->init(score)) {
			pRet->autorelease();
			return pRet;
		} else {
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	};
};

