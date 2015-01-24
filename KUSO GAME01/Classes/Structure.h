//
//  Structure.h
//  pcc01
//
//  Created by Riya.Liel on 2015/01/20.
//
//

#ifndef __pcc01__Structure__
#define __pcc01__Structure__

#include "cocos2d.h"

enum line{
    BOTTOM,
    CENTER,
    TOP,
};

enum vec{
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

class GameData{
    static int linewidth;
    static int score;
    static cocos2d::Size visibleSize;
    
public:
    static int& getLineWidth(){return linewidth;}
    static cocos2d::Size& getVisibleSize(){return visibleSize;}
    static void addScore(int _d=1){score+=_d;};
    static int getScore(){return score;};
    static void init(){score = 0;}
};

#endif /* defined(__pcc01__Structure__) */
