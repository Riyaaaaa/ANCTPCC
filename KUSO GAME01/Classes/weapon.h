//
//  weapon.h
//  pcc01
//
//  Created by Riya.Liel on 2015/01/19.
//
//

#ifndef __pcc01__weapon__
#define __pcc01__weapon__

#include "cocos2d.h"

enum rangeType{
    FRONTONLY,
    LINE,
    ALL,
};

class weapon{
    cocos2d::Sprite* weaponImage;
    cocos2d::Sprite* attackEffect;
    
protected:
    weapon(){};
    std::string effectStr;
    int validFrame;
    int Range;
    bool animeFlag;
    cocos2d::Vector<cocos2d::SpriteFrame*> animeFrame;
    cocos2d::Animation *animation;
public:
    virtual rangeType reach()=0;
    std::string getEffectStr(){return effectStr;}; //return the file name of the effect image
    int getValidFrame(){return validFrame;};
    int getRange(){return Range;}
    bool getAnimeFlag(){return animeFlag;}
    cocos2d::Vector<cocos2d::SpriteFrame*>* getFrame(){return &animeFrame;}
    cocos2d::Animation* getAnimation(){return animation;}
    
    void setImage();
    virtual ~weapon(){animation->release();}
};

class blade : public weapon{
public:
    rangeType reach(){return FRONTONLY;};
    static weapon* getInstance(){static blade obj; return &obj;} //Singleton design pattern
    
private:
    blade();
};

class star : public weapon{
public:
    rangeType reach(){return LINE;};
    static weapon* getInstance(){static star obj; return &obj;} //Singleton design pattern
    
private:
    star();
};

class fire : public weapon{
public:
    rangeType reach(){return ALL;};
    static weapon* getInstance(){static fire obj; return &obj;} //Singleton design pattern
    
private:
    fire();
};


#endif /* defined(__pcc01__weapon__) */
