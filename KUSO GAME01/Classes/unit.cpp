//
//  unit.cpp
//  pcc01
//
//  Created by Riya.Liel on 2015/01/19.
//
//

#include "unit.h"

USING_NS_CC;

mapobject::mapobject(std::string _filename){
    unitImage = Sprite::create(_filename);
    size = unitImage->getContentSize();
}

mapobject::~mapobject(){
    unitImage->removeFromParent();
}

void mapobject::moveTarget(int x){ //move x position
    cocos2d::MoveTo* action = cocos2d::MoveTo::create(1.0f, unitImage->getPosition()+Vec2(-x,0));
    unitImage->runAction(action);
}

void mapobject::setLine(line _l){ //set belonging to line
    belonging = _l;
    unitImage->setPosition(Vec2(unitImage->getPosition().x,GameData::getLineWidth() * (int)_l + 100));
    log("%d %d %lf¥n",GameData::getLineWidth(),_l,Vec2(unitImage->getPosition().x,GameData::getLineWidth() * (int)_l + 50).y);
}
void mapobject::moveLine(vec V){ //move belongig to line
    switch (V) {
        case UP:
            if(belonging==CENTER)setLine(TOP);
            else if(belonging==BOTTOM)setLine(CENTER);
            break;
        case DOWN:
            if(belonging==CENTER)setLine(BOTTOM);
            else if(belonging==TOP)setLine(CENTER);
            break;
        default:
            throw;
            break;
    }
}

void mapobject::releace(){
    unitImage->removeFromParent();
}

mapobject* player::attack(){ //make effect object from weapon status
    effect* obj= new effect(myWeapon->getEffectStr(),getLine());
    obj->Init(myWeapon);
    
    return obj;
}

void effect::Init(weapon* myWeapon){ //effect init
    setReach(myWeapon->reach());
    setRemain(myWeapon->getValidFrame());
    setRange(myWeapon->getRange());
    unitImage->setPosition(Vec2(unitImage->getContentSize().width,0));
    setLine(getLine());
    setFlag(myWeapon->getAnimeFlag());
    
    animeFrame = myWeapon->getFrame();
    unitImage->runAction(cocos2d::Animate::create(myWeapon->getAnimation()));
}

enemy::enemy(std::string _filename,line _l) :mapobject(_filename){
    unitImage->setPosition(Vec2(GameData::getVisibleSize().width,0));
    setLine(_l);
}

void enemy::progress(GameScene* game){
    mapobject::moveTarget(movement);
    if(unitImage->getPosition().x <= 0){
        game->damage();
        valid = false;
    }
}

effect::effect(std::string _filename,line _l) :mapobject(_filename){
    setLine(_l);
    
}

void effect::setReach(rangeType _type){
    rtype = _type;
    switch (rtype) {
        case FRONTONLY:
            movement=0;
            break;
        case ALL:
            movement=0;
            break;
        default:
            movement = -50; //line type
            break;
    }
}

void effect::progress(GameScene* game){
    std::vector<std::vector<mapobject*>*> targetIt;
    switch (rtype) {
        case FRONTONLY:
            if(remainFrame==0)valid = false;
            targetIt.push_back(&game->getObjectAtline(getLine()));
            break;
        case LINE:
            mapobject::moveTarget(movement);
            targetIt.push_back(&game->getObjectAtline(getLine()));
            break;
        case ALL:
            game->getPlayer()->getImage()->setTexture(cocos2d::TextureCache::getInstance()->addImage("front.png"));
            if(remainFrame==0){
                game->getPlayer()->getImage()->setTexture(cocos2d::TextureCache::getInstance()->addImage("right01.png"));

                valid = false;
            }
            targetIt.push_back(&game->getObjectAtline(BOTTOM));
            targetIt.push_back(&game->getObjectAtline(CENTER));
            targetIt.push_back(&game->getObjectAtline(TOP));
            break;
        default:
            break;
    }

    for(auto objectlist: targetIt){
        for(auto it = objectlist->begin(); it < objectlist->end(); it++){
            if(isCollision(*it)){
                (*it)->kill();
            }
        }
    }

    if(unitImage->getPosition().x > GameData::getVisibleSize().width)valid = false;
    remainFrame--;
}

bool effect::isCollision(mapobject* target){
    if(target!=this && abs(unitImage->getPosition().x - target->getImage()->getPosition().x) < Range){
        return true;
    }
    else return false;
}

void effect::setFlag(bool _flag){
    flag=_flag;
}



/*
player::player(std::string _filename){
}
*/