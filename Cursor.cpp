#include "Cursor.hpp"
#include "PlayScene.hpp"
#include "audio\include\SimpleAudioEngine.h"

Cursor::Cursor() {
	auto size = cocos2d::Director::getInstance()->getVisibleSize();

	auto draw = cocos2d::Sprite::createWithSpriteFrameName("square.png");
	draw->setAnchorPoint({ 0.5f, 0.5f });
	this->addChild(draw, 1, "draw");
	this->setPosition(70, size.height / 4);

	auto l = cocos2d::Label::create();
	l->setString("1");
	l->setAnchorPoint({ 0.5f, 0.f });
	l->setPosition(0, 60);
	draw->addChild(l, 1, "label");
	this->scheduleUpdate();
}

Cursor::~Cursor() {
}

Cursor* Cursor::create(){
	auto a = new Cursor();
	a->autorelease();
	return a;
}

void Cursor::update(float dt) {
	((cocos2d::Label*)getChildByName("draw")->getChildByName("label"))->setString(std::to_string(shape + 1));
}

void Cursor::switchShape(int shape) {
	this->shape = shape;
	this->runAction(cocos2d::Sequence::create(
		cocos2d::ScaleTo::create(0.2f, 0),
		cocos2d::CallFunc::create([&, shape]()->void {
			auto d = (cocos2d::Sprite*)getChildByName("draw");
			auto poly = (shape == 1) ? "triangle.png" : (shape == 2) ? "circle.png" : (shape == 3) ? "hex.png" : "square.png";
			d->setSpriteFrame(poly);
		}),
		cocos2d::ScaleTo::create(0.2f, 1),
		nullptr
	));
}

void Cursor::jumpUp() {
	if(pos == 3)
		return;
	pos++;
	auto size = cocos2d::Director::getInstance()->getVisibleSize();
	auto seqScale = cocos2d::Sequence::createWithTwoActions(
		cocos2d::ScaleTo::create(0.05f, 0.6f),
		cocos2d::ScaleTo::create(0.05f, 1.f)
	);
	this->runAction(
		cocos2d::Spawn::createWithTwoActions(seqScale, cocos2d::MoveBy::create(0.1f, { 0, size.height / 4 }))
	);
}

void Cursor::jumpDown() {
	if(pos == 1)
		return;
	pos--;
	auto size = cocos2d::Director::getInstance()->getVisibleSize();
	auto seqScale = cocos2d::Sequence::createWithTwoActions(
		cocos2d::ScaleTo::create(0.05f, 0.6f),
		cocos2d::ScaleTo::create(0.05f, 1.f)
	);
	this->runAction(
		cocos2d::Spawn::createWithTwoActions(seqScale, cocos2d::MoveBy::create(0.1f, { 0, -size.height / 4 }))
	);
}

void Cursor::checkShape(int shape) {
	if(this->shape == shape) {
		std::string str = "res/" + std::to_string(shape + 1) + ".wav";
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(str.c_str(), false);
			
		auto p = cocos2d::ParticleSystemQuad::create("res/particleSuccess.plist");
		p->setAnchorPoint({ 0.5f,0.5f });
		p->setAutoRemoveOnFinish(true);
		p->setPosition(getPosition());
		this->getParent()->addChild(p);
		((PlayScene*)(this->getParent()))->combo++;
		((PlayScene*)(this->getParent()))->popCombo();
		this->runAction(cocos2d::Spawn::createWithTwoActions(
			cocos2d::RotateBy::create(0.3f, 360),
			cocos2d::Sequence::createWithTwoActions(
				cocos2d::ScaleTo::create(0.15f, 1.5f),
				cocos2d::ScaleTo::create(0.15f, 1.f)
			)
		));

		auto parent = getParent();
		parent->runAction(cocos2d::Sequence::createWithTwoActions(
			cocos2d::ScaleTo::create(0.1f, 0.9f),
			cocos2d::ScaleTo::create(0.1f, 1.f)
		));
	} else {
		if(cocos2d::UserDefault::getInstance()->getBoolForKey("FX_ENABLED", true))
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/fail.wav");
		auto p = cocos2d::ParticleSystemQuad::create("res/particleFail.plist");
		p->setAnchorPoint({ 0.5f,0.5f });
		p->setAutoRemoveOnFinish(true);
		p->setPosition(getPosition());
		this->getParent()->addChild(p);
		((PlayScene*)(getParent()))->changeLife(--((PlayScene*)(getParent()))->life);
		launchFail();
	}
}

void Cursor::launchFail() {
	((PlayScene*)(this->getParent()))->combo = 0;
	this->runAction(cocos2d::Spawn::createWithTwoActions(
		cocos2d::Sequence::createWithTwoActions(
		cocos2d::ScaleTo::create(0.15f, 0.8f),
		cocos2d::ScaleTo::create(0.15f, 1.f)
	),
		cocos2d::Sequence::create(
		cocos2d::MoveBy::create(0.025f, { 10, 0 }),
		cocos2d::MoveBy::create(0.05f, { -20, 0 }),
		cocos2d::MoveBy::create(0.025f, { 10, 0 }),
		cocos2d::MoveBy::create(0.025f, { 0, 10 }),
		cocos2d::MoveBy::create(0.05f, { 0, -20 }),
		cocos2d::MoveBy::create(0.025f, { 0, 10 }),
		nullptr
	)
	));
}
