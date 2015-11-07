#include "HelloWorldScene.h"
#include <random>

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> dist(0,5);
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
   
    _scene = CSLoader::createNode("MainScene.csb");
    addChild(_scene);
    
    _time = dist(mt);
    
    _button = _scene->getChildByName<ui::Button*>("SButton");
    _button->addClickEventListener(CC_CALLBACK_0(HelloWorld::initGame, this));
    
    return true;
}

bool HelloWorld::initGame(){
    _button->removeFromParent();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegin,this);
    listener->setSwallowTouches(true);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    schedule(schedule_selector(HelloWorld::update),0.1f);
    return true;
}

void HelloWorld::addBall(){
    Size size = Director::getInstance()->getVisibleSize();
    
    _balls.push_back(Sprite::create("ball.png"));
    _scene->addChild(_balls.back());
    _balls.back()->setPosition(Vec2(size.width + 100, BALL_HEIGHT));
    _balls.back()->runAction(MoveTo::create(BALL_MOVE_TIME,Vec2(0,BALL_HEIGHT)));
}

bool HelloWorld::onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event){
    const float reach = 100;
    auto* chara = _scene->getChildByName<Sprite*>("charactor");
    chara->setTexture("charactor02.png");
    _eventDispatcher->setEnabled(false);
    scheduleOnce(schedule_selector(HelloWorld::charactorReady), 0.2f);
    
    for(auto*& ball: _balls){
        float x_diff = ball->getPosition().x - chara->getPosition().x;
        
        if( x_diff > 0 && x_diff < reach){
            ball->stopAllActions();
            ball->setTexture("breaked_ball.png");
            ball->setPosition(Vec2(ball->getPosition().x, BALL_HEIGHT+30));
            ball->runAction(Sequence::create(FadeOut::create(1.0f),RemoveSelf::create(),nullptr));
            ball = nullptr;
        }
    }
    
    _balls.erase(std::remove_if(_balls.begin(),_balls.end(),[](Sprite* sprite){ return sprite==nullptr;}),_balls.end());
    return true;
}

void HelloWorld::charactorReady(float){
    auto* chara = _scene->getChildByName<Sprite*>("charactor");
    chara->setTexture("charactor01.png");
    
    _eventDispatcher->setEnabled(true);
}

void HelloWorld::update(float delta){
    static std::random_device rnd;
    static std::mt19937 mt(rnd());
    static std::uniform_int_distribution<> dist(0,10);
    
    if(dist(mt) == 10)addBall();
    
    auto* chara = _scene->getChildByName<Sprite*>("charactor");
    
    for(auto*& ball: _balls){
        float x_diff = ball->getPosition().x - chara->getPosition().x;
        if( x_diff < 0){
            ball->removeFromParent();
            ball = nullptr;
            chara->setTexture("charactor03.png");
            chara->runAction(MoveTo::create(BALL_MOVE_TIME/3.,Vec2(30,BALL_HEIGHT)));
            _eventDispatcher->setEnabled(false);
            endGame();
        }
    }
    
    _balls.erase(std::remove_if(_balls.begin(),_balls.end(),[](Sprite* sprite){ return sprite==nullptr;}),_balls.end());
}

void HelloWorld::endGame(){
    Size size = Director::getInstance()->getVisibleSize();
    
    Label* label = Label::create();
    label->setString("GAME OVER");
    label->setScale(3.0f);
    label->setColor(Color3B::BLACK);
    addChild(label);
    
    label->setPosition(size/2.);
    
    unscheduleAllCallbacks();
}