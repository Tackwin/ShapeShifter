#include "OptionsScreen.hpp"
#include "MenuScene.hpp"
#include "PlayScene.hpp"

MenuScene::MenuScene() {
}

MenuScene::~MenuScene() {
}

cocos2d::Scene* MenuScene::createScene() {
	auto l = MenuScene::create();
	auto s = cocos2d::Scene::create();
	s->addChild(l);
	return s;
}

bool MenuScene::init() {
	if(!Layer::init()) {
		return false;
	}

	auto size = cocos2d::Director::getInstance()->getWinSize();

	auto l = cocos2d::Label::create();
	l->setString("Play");
	l->setSystemFontSize(20);
	l->setAnchorPoint({ 0.5f, 0.5f });
	l->setPosition(size.width / 2, 3 * size.height / 4);
	this->addChild(l, 1, "play");


	auto optionsLabel = cocos2d::Label::create();
	optionsLabel->setString("Options");
	optionsLabel->setSystemFontSize(20);
	optionsLabel->setAnchorPoint({ 0.5f, 0.5f });
	optionsLabel->setPosition(size.width / 2, 2 * size.height / 4);
	this->addChild(optionsLabel, 1, "options");

	auto instructions = cocos2d::Label::create();
	instructions->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	instructions->setAnchorPoint({ 0.5f,0.5f });
	instructions->setSystemFontSize(20);
	instructions->setPosition(size.width / 2, size.height / 4);
	instructions->setString(
		"Welcom in my entrie for LD35 ! \n \
		 You can start to play by clicking on Play or pressing anything (how simple is that ?), \n\
		 to move your cursor you can use the up and down arrow key \n\
		 or simply move your mouse around \n\
		 and to change shape you will need the 1, 2, 3, 4, keys\n\
		 Gl & hf !"
	);
	this->addChild(instructions);

	auto touch = cocos2d::EventListenerTouchOneByOne::create();
	touch->onTouchBegan = [](cocos2d::Touch*, cocos2d::Event*)->bool {return true;};
	touch->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);

	auto key = cocos2d::EventListenerKeyboard::create();
	key->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event*)->void {
		getEventDispatcher()->removeAllEventListeners();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5f, PlayScene::createScene()));
	};
	getEventDispatcher()->addEventListenerWithFixedPriority(key, 1);
	getEventDispatcher()->addEventListenerWithFixedPriority(touch, 1);

	return true;
}

void MenuScene::onTouchEnded(cocos2d::Touch *t, cocos2d::Event *e) {
	if(getChildByName("play")->getBoundingBox().containsPoint(t->getLocation())) {
		getEventDispatcher()->removeAllEventListeners();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5f, PlayScene::createScene()));
	}
	if(getChildByName("options")->getBoundingBox().containsPoint(t->getLocation())) {
		getEventDispatcher()->removeAllEventListeners();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5f, OptionsScreen::createScene()));
	}
}
