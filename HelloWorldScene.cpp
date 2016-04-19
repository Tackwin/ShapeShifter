#include "HelloWorldScene.h"
#include "MenuScene.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/spriteSheet.plist");

    auto sprite = Sprite::create("res/HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/backgroundMusic.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("res/fail.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("res/1.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("res/2.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("res/3.wav");

	this->scheduleOnce([](float)->void {
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.5f, MenuScene::createScene()));
	}, 0.f, "transitionScene");

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
