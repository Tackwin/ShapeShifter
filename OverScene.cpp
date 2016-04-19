#include "OverScene.hpp"
#include "PlayScene.hpp"


OverScene::OverScene() {
}

OverScene::~OverScene() {
}

cocos2d::Scene* OverScene::createScene(int score) {
	auto l = OverScene::create(score);
	auto s = cocos2d::Scene::create();
	s->addChild(l);
	return s;
}

bool OverScene::init(int score) {
	if(!Layer::init()) {
		return false;
	}

	auto s = cocos2d::Director::getInstance()->getWinSize();
	auto userdata = cocos2d::UserDefault::getInstance();
	if(userdata->getIntegerForKey("HIGH_SCORE") < score)
		userdata->setIntegerForKey("HIGH_SCORE", score);

	auto l = cocos2d::Label::create();
	l->setAnchorPoint({ 0.5f,0.5f });
	l->setPosition(s.width / 2, 2 * s.height / 3);
	l->setSystemFontSize(54);
	l->setString("SCORE: " + std::to_string(score) + "\n\
				  BEST: " + std::to_string(userdata->getIntegerForKey("HIGH_SCORE")));
	this->addChild(l);

	auto instructions = cocos2d::Label::create();
	instructions->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	instructions->setAnchorPoint({ 0.5f,0.5f });
	instructions->setPosition(s.width / 2, s.height / 3);
	instructions->setSystemFontSize(20);
	instructions->setString(
		"game over, to restart press anything"
	);
	this->addChild(instructions);

	auto e = cocos2d::EventListenerKeyboard::create();
	e->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode, cocos2d::Event*)->void {
		getEventDispatcher()->removeAllEventListeners();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5f, PlayScene::createScene()));
	};
	getEventDispatcher()->addEventListenerWithFixedPriority(e, 1);
	return true;
}
