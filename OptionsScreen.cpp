#include "OptionsScreen.hpp"
#include "ui\CocosGUI.h"
#include "MenuScene.hpp"

OptionsScreen::OptionsScreen() {
}

OptionsScreen::~OptionsScreen() {
}

cocos2d::Scene* OptionsScreen::createScene() {
	auto s = cocos2d::Scene::create();
	auto l = OptionsScreen::create();
	s->addChild(l);
	return s;
}

bool OptionsScreen::init() {
	if(!Layer::init())
		return false;

	auto size = cocos2d::Director::getInstance()->getWinSize();

	auto returnButton = cocos2d::ui::Button::create("returnButton.png", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	returnButton->setAnchorPoint({ 0.5f,0.5f });
	returnButton->setPosition({ 50.f, size.height - 50 });
	returnButton->addClickEventListener([&](cocos2d::Ref *r)->void {
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5f, MenuScene::createScene()));
	});
	this->addChild(returnButton);

	auto labelCheckMusic = cocos2d::Label::create();
	labelCheckMusic->setSystemFontSize(20);
	labelCheckMusic->setString("Music");
	labelCheckMusic->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	labelCheckMusic->setAnchorPoint({ 0.f, 0.5f });
	labelCheckMusic->setPosition(size.width / 2, 2 * size.height / 3);
	this->addChild(labelCheckMusic);

	auto checkMusic = cocos2d::ui::CheckBox::create("checkBox.png", "checkBox.png", "cross.png", "checkBox.png", "cross.png", cocos2d::ui::Widget::TextureResType::PLIST);
	checkMusic->setAnchorPoint({ 1.f, 0.5f });
	checkMusic->setSelected(cocos2d::UserDefault::getInstance()->getBoolForKey("MUSIC_ENABLED", true));
	checkMusic->setPosition({ size.width / 2 - labelCheckMusic->getContentSize().width / 2, 2 * size.height / 3 });
	checkMusic->addEventListener([&](cocos2d::Ref *r, cocos2d::ui::CheckBox::EventType t)->void {
		cocos2d::UserDefault::getInstance()->setBoolForKey("MUSIC_ENABLED", t == cocos2d::ui::CheckBox::EventType::SELECTED);
	});
	this->addChild(checkMusic);

	auto labelCheckFX = cocos2d::Label::create();
	labelCheckFX->setSystemFontSize(20);
	labelCheckFX->setString("Fx");
	labelCheckFX->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	labelCheckFX->setAnchorPoint({ 0.f, 0.5f });
	labelCheckFX->setPosition(size.width / 2, size.height / 3);
	this->addChild(labelCheckFX);

	auto checkFx = cocos2d::ui::CheckBox::create("checkBox.png", "checkBox.png", "cross.png", "checkBox.png", "cross.png", cocos2d::ui::Widget::TextureResType::PLIST);
	checkFx->setAnchorPoint({ 1.f, 0.5f });
	checkFx->setSelected(cocos2d::UserDefault::getInstance()->getBoolForKey("FX_ENABLED", true));
	checkFx->setPosition({ size.width / 2 - labelCheckFX->getContentSize().width / 2, size.height / 3 });
	checkFx->addEventListener([&](cocos2d::Ref *r, cocos2d::ui::CheckBox::EventType t)->void {
		cocos2d::UserDefault::getInstance()->setBoolForKey("FX_ENABLED", t == cocos2d::ui::CheckBox::EventType::SELECTED);
	});
	this->addChild(checkFx);

	return true;
}