#include "GameScene.h"
#include "EndGameScene.h"

using namespace cocos2d;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    int i=0;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    srand((unsigned int)time(NULL));
    schedule(schedule_selector(GameScene::allProgress), 0.1f); //run allProgress every three seconds
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    GameData::getLineWidth() = (GameData::getVisibleSize().height - 100)/3;
    
    this->initWithColor(Color4B(255,255,255,255) ); //fill layer with white
    
    hero = new player("right01.png");
    hero->setLine(CENTER);
    hero->getImage()->setPosition(Vec2(75,GameData::getVisibleSize().height/2));
    
    this->addChild(hero->getImage(),2);
    
    object_list.resize(NUM_LINES);
    
    //set button Image
    
    for (int x=0;x<2; x++) {
        Rect rect(float(x * 150),
                  float(0),
                  float(150),
                  float(150));
        weaponButton[0][x] = Sprite::create("swordIco.png",rect);
        weaponButton[1][x] = Sprite::create("starIco.png",rect);
        weaponButton[2][x] = Sprite::create("hellfire.png",rect);
        mainButton[0][x] = Sprite::create("up.png",rect);
        mainButton[1][x] = Sprite::create("attack.png",rect);
        mainButton[2][x] = Sprite::create("down.png",rect);
    }

    
    //set power button
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    
    //set move & attack button
    setButton(mainButton[0][0], mainButton[0][1],
              Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2-100 ,
                   origin.y + closeItem->getContentSize().height/2+350),
              CC_CALLBACK_1(GameScene::upButtonCallBack, this));
    
    setButton(mainButton[1][0], mainButton[1][1],
              Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2-100 ,
                   origin.y + closeItem->getContentSize().height/2+200),
              CC_CALLBACK_1(GameScene::attackButtonCallBack, this));
    
    setButton(mainButton[2][0], mainButton[2][1],
              Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2-100 ,
                   origin.y + closeItem->getContentSize().height/2+50),
              CC_CALLBACK_1(GameScene::downButtonCallBack, this));
    
    setButton(weaponButton[0][0], weaponButton[0][1],
              Vec2(GameData::getVisibleSize().width/2 - 250 , 100),
              [&](Ref* _ref){hero->setWeapon(blade::getInstance());});
    
    setButton(weaponButton[1][0], weaponButton[1][1],
              Vec2(GameData::getVisibleSize().width/2 , 100),
              [&](Ref* _ref){hero->setWeapon(star::getInstance());});
    
    setButton(weaponButton[2][0], weaponButton[2][1],
              Vec2(GameData::getVisibleSize().width/2 + 250 , 100),
              [&](Ref* _ref){hero->setWeapon(fire::getInstance());});
    

    remainLife = Label::createWithSystemFont("LIFE = ♡♡♡♡♡♡♡♡♡♡", "arial", 48);
    //remainLife->setPosition(Point(50, GameData::getVisibleSize().height-50));
    remainLife->setPosition(GameData::getVisibleSize()/2 - Size(100,0));
    remainLife->setColor(Color3B::BLACK);
    this->addChild(remainLife);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);
    
    
    
    return true;
}

template<class CALLBACK>
void GameScene::setButton(Sprite* active,Sprite* selected,Vec2 pos,CALLBACK callBack){
    auto pBtnItem = MenuItemSprite::create(active, selected, callBack);
    auto pMenu = Menu::create(pBtnItem, NULL);
    pMenu->setPosition(pos);
    this->addChild(pMenu,3);
}


void GameScene::gameOverd()
{
    Scene* nextScene = EndGameScene::createScene();
    if(nextScene){
        Director::sharedDirector()->replaceScene(nextScene);
    }
}

//define a callback group
void GameScene::upButtonCallBack(Ref* pSender){
    hero->moveLine(UP);
}

void GameScene::downButtonCallBack(Ref* pSender){
    hero->moveLine(DOWN);
}

void GameScene::attackButtonCallBack(Ref* pSender){
    object_list[hero->getLine()].push_back(hero->attack());
    this->addChild(object_list[hero->getLine()].back()->getImage());
}
//

void GameScene::allProgress(float frame){
    int rnd,lines;
    
    if(life<=0){
        gameOverd();
        exit(0);
    }
    
    for(int i=0;i<NUM_LINES;i++){
        for(auto &obj: object_list[i]){
            obj->progress(this);
        }
        log("");
        for(auto &obj: object_list[i]){
            if(!obj->isValid()){
                delete obj;
                obj=nullptr;
            }
        }
        auto it = remove_if( object_list[i].begin(), object_list[i].end(), [](mapobject* obj){return obj==nullptr;} );
        object_list[i].erase(it,object_list[i].end());
    }
    
    rnd = rand()%150;
    lines = rand()%3;
    
    if(rnd < 10){
        std::string base="symptte";
        base = base + "0" + std::to_string(rnd%4+1) + ".jpg";
        auto new_enemy = new enemy(base,(line)lines);
        object_list[lines].push_back(new_enemy);
        this->addChild(new_enemy->getImage());
        dynamic_cast<enemy*>(new_enemy)->setMovement(25);
    }
    if(rnd < 5){
        std::string base="hal";
        base = base + "0" + std::to_string(rnd%3+1) + ".png";
        auto new_enemy = new enemy(base,(line)lines);
        object_list[lines].push_back(new_enemy);
        this->addChild(new_enemy->getImage());
        dynamic_cast<enemy*>(new_enemy)->setMovement(50);
    }
    else;
    
}

void GameScene::damage(){
    life--;
    remainLife->setString("いたい");
    
    this->runAction(Sequence::create(DelayTime::create(0.5),CallFunc::create([this](){
        std::string str = "LIFE = ";
        for(int i=0;i<this->life;i++)str.append("♡");
        this->remainLife->setString(str);
    }), NULL));
};
void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}