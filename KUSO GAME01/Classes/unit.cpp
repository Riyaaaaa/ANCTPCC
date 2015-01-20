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

void mapobject::moveTarget(int x){
    cocos2d::MoveTo* action = cocos2d::MoveTo::create(1.0f, unitImage->getPosition()+Vec2(-x,0));
    unitImage->runAction(action);
}

void mapobject::setLine(line _l){
    belonging = _l;
    unitImage->setPosition(Vec2(unitImage->getPosition().x,GameData::getLineWidth() * (int)_l + 100));
    log("%d %d %lf¥n",GameData::getLineWidth(),_l,Vec2(unitImage->getPosition().x,GameData::getLineWidth() * (int)_l + 50).y);
}
void mapobject::moveLine(vec V){
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

mapobject* player::attack(){
    rangeType  _rtype = myWeapon->reach();
    effect* obj= new effect(myWeapon->getEffectStr(),getLine());
    obj->setReach(_rtype);
    obj->setRemain(myWeapon->getValidFrame());
    obj->setRange(myWeapon->getRange());
    obj->setLine(getLine());
    return obj;
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
    unitImage->setPosition(Vec2(100,0));
    setLine(_l);
    
}

void effect::setReach(rangeType _type){
    rtype = _type;
    switch (rtype) {
        case FRONTONLY:
            remainFrame = 1;
            break;
        case ALL:
            remainFrame = 1;
            break;
        default:
            remainFrame = -1;
            movement = 20;
            break;
    }
}

void effect::progress(GameScene* game){
    switch (rtype) {
        case FRONTONLY:
            if(remainFrame==0)valid = false;
            break;
        case LINE:
            mapobject::moveTarget(movement);
            break;
        case ALL:
            if(remainFrame==0)valid = false;
            break;
        default:
            break;
    }

    for(mapobject* obj : game->getObjectAtline(getLine())){
        if(isCollision(obj)){
            obj->kill();
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



/*
player::player(std::string _filename){
}
*/