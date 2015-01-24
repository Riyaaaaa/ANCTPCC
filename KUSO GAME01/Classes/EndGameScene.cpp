//
//  EndGameScene.cpp
//  pcc01
//
//  Created by Riya.Liel on 2015/01/23.
//
//

#include "EndGameScene.h"
#include "Structure.h"


USING_NS_CC;

Scene* EndGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndGameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool EndGameScene::init()
{
    this->initWithColor(Color4B(255,255,255,255) ); //fill layer with white
    

    Label* label = Label::createWithSystemFont(std::string("SCORE = ") + std::to_string(GameData::getScore()) , "arial", 48);
    label->setColor(Color3B::BLACK);
    label->setPosition(GameData::getVisibleSize()/2);
    
    this->addChild(label);
    
    this->runAction(Sequence::create(DelayTime::create(10),CallFunc::create([this](){this->endGame();}), NULL));
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}

void EndGameScene::endGame()
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
