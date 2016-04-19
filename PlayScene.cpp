#include "PlayScene.hpp"
#include "Cursor.hpp"
#include "OverScene.hpp"
#include "SimpleAudioEngine.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
}

cocos2d::Scene* PlayScene::createScene() {
	auto s = cocos2d::Scene::create();
	auto l = PlayScene::create();
	s->addChild(l);
	return s;
}

bool PlayScene::init() {
	if(!Layer::init())
		return false;

	auto size = cocos2d::Director::getInstance()->getVisibleSize();
	
	auto partBack = cocos2d::ParticleSystemQuad::create("res/particleBack.plist");
	partBack->setAnchorPoint({ 0.5f, 0.5f });
	partBack->setPosition(size.width / 2, size.height / 2);
	this->addChild(partBack, 1);

	auto comboLabel = cocos2d::Label::create();
	comboLabel->setSystemFontSize(56);
	comboLabel->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	comboLabel->setAnchorPoint({ 0.5f, 0.5f });
	comboLabel->setColor(cocos2d::Color3B(220, 220, 220));
	comboLabel->setPosition(size.width / 2, 5 * size.height / 6);
	comboLabel->setScale(0.f);
	this->addChild(comboLabel, 5, "comboLabel");

	auto scoreLabel = cocos2d::Label::create();
	scoreLabel->setSystemFontSize(15);
	scoreLabel->setAlignment(cocos2d::TextHAlignment::LEFT, cocos2d::TextVAlignment::CENTER);
	scoreLabel->setAnchorPoint({ 0.f, 0.5f });
	scoreLabel->setPosition(5, size.height - 70);
	scoreLabel->setString("Score: 0");
	this->addChild(scoreLabel, 2, "scoreLabel");

	for(int i = 0; i < 3; i++) {

		auto pipeMid = cocos2d::Sprite::createWithSpriteFrameName("pipeMid.png");
		pipeMid->setScaleX(size.width - 20);
		pipeMid->setAnchorPoint({ 0.f, 0.5f });
		pipeMid->setPosition(10, (1 + i) * size.height / 4);
		this->addChild(pipeMid, 2, "pipeMid" + std::to_string(i));

		auto pipeLeft = cocos2d::Sprite::createWithSpriteFrameName("pipeBorder.png");
		pipeLeft->setAnchorPoint({ 0.f, 0.5f });
		pipeLeft->setPosition(0, (1 + i) * size.height / 4);
		this->addChild(pipeLeft, 2, "pipeLeft" + std::to_string(i));

		auto pipeRight = cocos2d::Sprite::createWithSpriteFrameName("pipeBorder.png");
		pipeRight->setScaleX(-1);
		pipeRight->setAnchorPoint({ 0.f, 0.5f });
		pipeRight->setPosition(size.width, (1 + i) * size.height / 4);
		this->addChild(pipeRight, 2, "pipeRight" + std::to_string(i));
	}

	auto heart1 = cocos2d::Sprite::createWithSpriteFrameName("fullHeart.png");
	heart1->setAnchorPoint({ 0.5f, 0.5f });
	heart1->setPosition(20, size.height - 20);
	this->addChild(heart1, 2, "heart1");
	auto heart2 = cocos2d::Sprite::createWithSpriteFrameName("fullHeart.png");
	heart2->setAnchorPoint({ 0.5f, 0.5f });
	heart2->setPosition(55, size.height - 20);
	this->addChild(heart2, 2, "heart2");
	auto heart3 = cocos2d::Sprite::createWithSpriteFrameName("fullHeart.png");
	heart3->setAnchorPoint({ 0.5f, 0.5f });
	heart3->setPosition(90, size.height - 20);
	this->addChild(heart3, 2, "heart3");

	auto ind = cocos2d::Sprite::createWithSpriteFrameName("indicator.png");
	ind->setAnchorPoint({ 0.5f, 1.f });
	ind->setPosition(size.width / 2, size.height);
	this->addChild(ind, 2, "ind");

	auto mask = cocos2d::Sprite::createWithSpriteFrameName("pointeur.png");
	mask->setAnchorPoint({ 0.5f, 1.f });
	mask->setPosition(size.width / 2 - 165, size.height);
	this->addChild(mask, 3, "mask");

	auto cursor = Cursor::create();
	this->addChild(cursor, 3, "cursor");

	auto keyEvent = cocos2d::EventListenerKeyboard::create();
	keyEvent->onKeyPressed = [&, size](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *e)->void {
		int i = getChildByName("mask")->getPositionX() - (size.width / 2 - 165);
		i /= 100;
		i++;
		switch(code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			((Cursor*)getChildByName("cursor"))->jumpUp();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			((Cursor*)getChildByName("cursor"))->jumpDown();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
			((Cursor*)getChildByName("cursor"))->switchShape(0);
			getChildByName("mask")->runAction(cocos2d::MoveBy::create(0.1f, { (1 - i) * 110.f, 0 }));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
			((Cursor*)getChildByName("cursor"))->switchShape(1);
			getChildByName("mask")->runAction(cocos2d::MoveBy::create(0.1f, { (2 - i) * 110.f, 0 }));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
			((Cursor*)getChildByName("cursor"))->switchShape(2);
			getChildByName("mask")->runAction(cocos2d::MoveBy::create(0.1f, { (3 - i) * 110.f, 0 }));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_4:
			((Cursor*)getChildByName("cursor"))->switchShape(3);
			getChildByName("mask")->runAction(cocos2d::MoveBy::create(0.1f, { (4 - i) * 110.f, 0 }));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
			triggerPause();
			break;
		}
	};

	auto mouseEvent = cocos2d::EventListenerMouse::create();
	mouseEvent->onMouseMove = [&, size](cocos2d::EventMouse *e)->void {
		if(!paused){
			float y = e->getCursorY();
			if(y < size.height / 3) {
				if(((Cursor*)getChildByName("cursor"))->pos > 1) {
					((Cursor*)getChildByName("cursor"))->jumpDown();
				}
			} else if(y < 2 * size.height / 3) {
				if(((Cursor*)getChildByName("cursor"))->pos == 1) {
					((Cursor*)getChildByName("cursor"))->jumpUp();
				} else if(((Cursor*)getChildByName("cursor"))->pos == 3) {
					((Cursor*)getChildByName("cursor"))->jumpDown();
				}
			} else {
				if(((Cursor*)getChildByName("cursor"))->pos < 3) {
					((Cursor*)getChildByName("cursor"))->jumpUp();
				}
			}
		}
	};

	_eventDispatcher->addEventListenerWithFixedPriority(mouseEvent, 2);
	_eventDispatcher->addEventListenerWithFixedPriority(keyEvent, 1);

	this->setAnchorPoint({ 0.5f, 0.5f });

	this->scheduleOnce(schedule_selector(PlayScene::popFrame), 1.f);
	this->scheduleOnce([&](float)->void {
		if(cocos2d::UserDefault::getInstance()->getBoolForKey("MUSIC_ENABLED", true)) {
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("res/backgroundMusic.wav", true);
		}
	}, 0.1f, "sound");
	this->scheduleUpdate();
	return true;
}

void PlayScene::update(float dt) {
	elapsed += dt;
}

void PlayScene::changeLife(int l) {
	if(l > 0) {
		for(int i = 6; i > l; i -= 2) {
			std::string str = "heart" + std::to_string((int)ceil(i / 2));
			auto s = ((cocos2d::Sprite*)(getChildByName(str)));
			s->setTexture("res/emptyHeart.png");
		}
		if((l % 2) == 1) {
			int i = 1 + ((int)floor(l / 2));
			((cocos2d::Sprite*)(getChildByName("heart" + std::to_string(i))))->setTexture("res/halfHeart.png");
		}
	} else {
		((cocos2d::Sprite*)(getChildByName("heart1")))->setTexture("res/emptyHeart.png");
		this->runAction(cocos2d::Spawn::create(
			cocos2d::ScaleTo::create(0.5f, 0.2f),
			cocos2d::CallFunc::create([&]()->void {
				getEventDispatcher()->removeAllEventListeners();
				CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5f, OverScene::createScene(score)));
			}),
			nullptr
		));
	}
}

void PlayScene::popCombo() {
	score += combo;
	((cocos2d::Label*)(this->getChildByName("scoreLabel")))->setString("Score: " + std::to_string(score));
	auto l = (cocos2d::Label*)getChildByName("comboLabel");
	l->setString("COMBO X" + std::to_string(combo));
	l->runAction(cocos2d::Sequence::createWithTwoActions(
		cocos2d::EaseIn::create(cocos2d::ScaleTo::create(0.4f, 1.f), 1.f),
		cocos2d::EaseIn::create(cocos2d::ScaleTo::create(0.4f, 0.f), 1.f)
	));
}

void PlayScene::popFrame(float) {
	auto size = cocos2d::Director::getInstance()->getVisibleSize();

	int shape = cocos2d::RandomHelper::random_int<int>(0, 3);
	int pos = cocos2d::RandomHelper::random_int<int>(1, 3);

	auto poly = (shape == 1) ? "triangleFrame.png" : (shape == 2) ? "circleFrame.png" : (shape == 3) ? "hexagonFrame.png" : "squareFrame.png";

	auto preview = cocos2d::Sprite::createWithSpriteFrameName("preview.png");
	preview->setAnchorPoint({ 0.5f,0.5f });
	preview->setPosition(size.width - 30, pos * size.height / 4);
	this->addChild(preview, 3, "preview");

	auto previewDraw = cocos2d::Sprite::createWithSpriteFrameName(poly);
	if(poly == 0)
		preview->setAnchorPoint({ 0.6f, 0.42f });
	else
		previewDraw->setAnchorPoint({ 0.5f, 0.5f });
	previewDraw->setScale(0.5f);
	previewDraw->setPosition(preview->getContentSize().width / 2, preview->getContentSize().height / 2);
	preview->addChild(previewDraw);

	auto label = cocos2d::Label::create();
	label->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	label->setAnchorPoint({ 0.5f,0.5f });
	label->setPosition(preview->getContentSize().width / 2, preview->getContentSize().height / 2);
	label->setString(std::to_string(shape + 1));
	preview->addChild(label);

	this->scheduleOnce([&, poly, shape, pos, size, preview](float)->void {
		auto a = cocos2d::Sprite::createWithSpriteFrameName(poly);
		a->setAnchorPoint({ 0.5f, 0.5f });
		a->setPosition(size.width, pos * size.height / 4);
		a->schedule([=](float dt)->void {
			a->setPositionX(a->getPositionX() - size.width / 2 * dt);
			if(a->getPositionX() < 70) {
				auto c = ((Cursor*)getChildByName("cursor"));
				if(c->pos == pos) {
					c->checkShape(shape);
				} else {
					if(cocos2d::UserDefault::getInstance()->getBoolForKey("FX_ENABLED", true))
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/fail.wav");
					c->launchFail();
					changeLife(--life);
					auto p = cocos2d::ParticleSystemQuad::create("res/particleFail.plist");
					p->setAnchorPoint({ 0.5f,0.5f });
					p->setAutoRemoveOnFinish(true);
					p->setPosition(70, pos * size.height / 4);
					this->getParent()->addChild(p);
				}
				a->unschedule("update");
				this->removeChild(a);
			}
		}, 0, "update");

		auto l = cocos2d::Label::create();
		l->setString(std::to_string(shape + 1));
		l->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
		l->setAnchorPoint({ 0.5f,0.f });
		l->setPosition(0, 60);
		l->setSystemFontSize(20);

		this->addChild(a, 3);
		a->addChild(l);

		this->removeChild(preview);
	}, 0.4f, "unleashFrame");
	this->runAction(cocos2d::Sequence::createWithTwoActions(
		cocos2d::DelayTime::create(0.5f * exp(-elapsed/70) + 1 - 0.5f),
		cocos2d::CallFunc::create([&]()->void {popFrame(0);})
	));
}

void PlayScene::triggerPause() {
	if(paused) {
		unpauseGame();
	} else {
		pauseGame();
	}
}

void PlayScene::pauseGame() {
	auto size = cocos2d::Director::getInstance()->getWinSize();
	this->pauseSchedulerAndActions();
	for(auto a : this->getChildren()) {
		a->pauseSchedulerAndActions();
	}

	auto s = cocos2d::Sprite::createWithSpriteFrameName("blank.png");
	s->setScale(size.width * 2, size.height * 2);
	s->setAnchorPoint({ 0, 0 });
	s->setPosition(0, 0);
	s->setColor(cocos2d::Color3B::GRAY);
	s->setOpacity(220);
	this->addChild(s, 10, "backPause");

	auto l = cocos2d::Label::create();
	l->setString("Paused");
	l->setSystemFontSize(50);
	l->setAnchorPoint({ 0.5f,0.5f });
	l->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	l->setPosition(size.width / 2, size.height / 2);
	this->addChild(l, 11, "labelPause");
	paused = true;
}

void PlayScene::unpauseGame() {
	paused = false;
	this->resumeSchedulerAndActions();
	for(auto a : this->getChildren()) {
		a->resumeSchedulerAndActions();
	}

	this->removeChildByName("backPause");
	this->removeChildByName("labelPause");
}