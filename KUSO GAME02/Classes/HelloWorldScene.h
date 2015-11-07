#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    bool initGame();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float delta);
    
private:
    int _time;
    std::vector<cocos2d::Sprite*> _balls;
    cocos2d::Node* _scene;
    cocos2d::ui::Button* _button;
    
    const int BALL_HEIGHT = 170;
    const float BALL_MOVE_TIME = 3.0f;
    
    bool onTouchBegin(cocos2d::Touch*,cocos2d::Event*);
    void charactorReady(float);
    void addBall();
    void endGame();
};

#endif // __HELLOWORLD_SCENE_H__
