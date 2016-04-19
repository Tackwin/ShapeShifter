#pragma once
#include "cocos2d.h"

#define PI 3.1415923

class Cursor : public cocos2d::Node {
public:
	int pos = 1;
	int shape = 0;
public:
	Cursor();
	~Cursor();

	static Cursor* create();
	void update(float dt);

	void switchShape(int shape);
	void jumpUp();
	void jumpDown();
	void checkShape(int shape);

	void launchFail();

	static cocos2d::Vec2 triPoly[3];
	static cocos2d::Vec2 sqrPoly[4];
	static cocos2d::Vec2 hexPoly[6];
	static cocos2d::Vec2 crlPoly[20];
};

