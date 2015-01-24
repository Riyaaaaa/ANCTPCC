//
//  TitleScene.h
//  pcc01
//
//  Created by Riya.Liel on 2015/01/23.
//
//

#ifndef __pcc01__TitleScene__
#define __pcc01__TitleScene__

#include "cocos2d.h"


class TitleScene : public cocos2d::LayerColor
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    
    void startGame(cocos2d::Ref* _ref);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
    
private:
    
        void menuCloseCallback(cocos2d::Ref* pSender);
    
};


#endif /* defined(__pcc01__TitleScene__) */
