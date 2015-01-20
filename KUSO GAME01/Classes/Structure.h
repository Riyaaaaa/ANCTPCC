//
//  Structure.h
//  pcc01
//
//  Created by Riya.Liel on 2015/01/20.
//
//

#ifndef __pcc01__Structure__
#define __pcc01__Structure__

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
    static cocos2d::Size visibleSize;
    
public:
    static int& getLineWidth(){return linewidth;}
    static cocos2d::Size& getVisibleSize(){return visibleSize;}
};

#endif /* defined(__pcc01__Structure__) */
