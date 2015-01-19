//
//  unit.cpp
//  pcc01
//
//  Created by Riya.Liel on 2015/01/19.
//
//

#include "unit.h"

USING_NS_CC;

object::object(std::string _filename){
    unitImage = Sprite::create(_filename);
    size = unitImage->getContentSize();
}

void object::moveTarget(int x){
    cocos2d::MoveTo* action = cocos2d::MoveTo::create(1.0f, unitImage->getPosition()+Vec2(-x,0));
    unitImage->runAction(action);
}

object* player::attack(){
    rangeType  _rtype = myWeapon->reach();
    effect* obj= new effect(myWeapon->getEffectStr());
    obj->setReach(_rtype);
    return obj;
}

void enemy::progress(){
    object::moveTarget(movement);
}

effect::effect(std::string _filename) :object(_filename){}


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

void effect::progress(){
    switch (rtype) {
        case FRONTONLY:
            break;
        case LINE:
            object::moveTarget(movement);
            break;
        case ALL:
            break;
        default:
            break;
    }
    remainFrame--;
}

bool effect::isCollision(object* target){
    return true;
}



/*
player::player(std::string _filename){
}
*/