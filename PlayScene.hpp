#pragma once
#include "cocos2d.h"
class PlayScene : public cocos2d::Layer {
public:
	float elapsed = 0;

	int life = 6;
	int combo = 0;
	int score = 0;

	bool paused = false;

	PlayScene();
	~PlayScene();

	void update(float dt);

	bool init();
	static cocos2d::Scene* createScene();

	void changeLife(int l);
	void popFrame(float);
	void popCombo();

	void triggerPause();
	void pauseGame();
	void unpauseGame();

	CREATE_FUNC(PlayScene);
};

