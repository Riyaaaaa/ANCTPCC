//
//  TitleScene.cpp
//  pcc01
//
//  Created by Riya.Liel on 2015/01/23.
//
//

#include "TitleScene.h"
#include "Structure.h"
#include "GameScene.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool TitleScene::init()
{
    this->initWithColor(Color4B(255,255,255,255) ); //fill layer with white
    GameData::getVisibleSize() = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Label* label = Label::createWithSystemFont("PLAY GAME", "arial", 48);
    //remainLife->setPosition(Point(50, GameData::getVisibleSize().height-50));
    label->setColor(Color3B::BLACK);
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TitleScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);
    
    auto pBtnItem = MenuItemLabel::create(label,CC_CALLBACK_1( TitleScene::startGame, this));
    
    Menu* pMenu = Menu::create(pBtnItem, NULL);
    pMenu->setPosition(GameData::getVisibleSize()/2);
    this->addChild(pMenu);
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TitleScene::startGame(cocos2d::Ref* _ref){
    Scene* nextScene = GameScene::createScene();
    float duration = 1.0f;
    Scene* pScene = TransitionFade::create(duration, nextScene);
    if(pScene){
        Director::sharedDirector()->replaceScene(pScene);
    }
}