//
//  GameScene.h
//  pcc01
//
//  Created by Riya.Liel on 2015/01/19.
//
//

#ifndef __pcc01__GameScene__
#define __pcc01__GameScene__

#include "unit.h"

class mapobject;
class player;

class GameScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void upButtonCallBack(Ref* pSender);
    void downButtonCallBack(Ref* pSender);
    void attackButtonCallBack(Ref* pSender);
    
    void damage(){life--;};
    
    const std::vector<mapobject*>& getObjectAtline(line _l)const{return object_list[(int)_l];}
    
    
    template<class CALLBACK>
    void setButton(cocos2d::Sprite* active,cocos2d::Sprite* selected,cocos2d::Vec2 pos,CALLBACK callBack); //first argument,main image. second argumet,selected image. last argument,callback function.
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    cocos2d::Sprite* vectorButton[9]; //vectorButton image set.
    player *hero;
    
    std::vector< std::vector<mapobject*> > object_list; //run the progress() on all objects
    
    void allProgress(float); //object
    
    const int NUM_LINES = 3;
    
    int life = 5;
    
};

#endif /* defined(__pcc01__GameScene__) */
