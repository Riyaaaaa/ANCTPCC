//
//  weapon.cpp
//  pcc01
//
//  Created by Riya.Liel on 2015/01/19.
//
//

#include "weapon.h"

blade::blade(){
    effectStr = "zangekiOrigin.png";
    validFrame = 4;
    Range = 100;
    
    for(int i=0;i<4;i++){
        cocos2d::Rect rect(float(i * 200),
                           float(0),
                           float(200),
                           float(200));
        animeFrame.pushBack(cocos2d::SpriteFrame::create("zangeki.png",rect));
    }
    animation = cocos2d::Animation::createWithSpriteFrames(animeFrame);
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(false);
    animation->retain();
}

star::star(){
    effectStr = "star.png";
    validFrame = 1;
    Range = 100;
    
    cocos2d::Rect rect(float(200),
                       float(0),
                       float(200),
                       float(200));
    animeFrame.pushBack(cocos2d::SpriteFrame::create("star.png",rect));
    
    animation = cocos2d::Animation::createWithSpriteFrames(animeFrame);
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    animation->retain();
}

fire::fire(){
    effectStr = "fire.png";
    validFrame = 4;
    Range = 1000;
    
    cocos2d::Rect rect(float(200),
                       float(0),
                       float(200),
                       float(200));
    animeFrame.pushBack(cocos2d::SpriteFrame::create("fire.png",rect));
    
    animation = cocos2d::Animation::createWithSpriteFrames(animeFrame);
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    animation->retain();

}