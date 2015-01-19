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
    std::string effectStr;
public:
    virtual rangeType reach();
    std::string getEffectStr(){return effectStr;}; //return the file name of the effect image
    void setImage();
};

class blade : public weapon{
public:
    rangeType reach(){return FRONTONLY;};
    static weapon* getInstance(){static blade obj; return &obj;} //Singleton design pattern
    
private:
    blade();
};


#endif /* defined(__pcc01__weapon__) */
