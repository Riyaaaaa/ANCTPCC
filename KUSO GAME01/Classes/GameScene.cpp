#include "GameScene.h"

using namespace cocos2d;

static GameScene* sharedScene = NULL;

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
    
    GameData::getVisibleSize() = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    GameData::getLineWidth() = (GameData::getVisibleSize().height - 100)/3;
    
    this->initWithColor(Color4B(255,255,255,255) ); //fill layer with white
    
    hero = new player("right01.png");
    hero->setLine(CENTER);
    hero->getImage()->setPosition(Vec2(75,GameData::getVisibleSize().height/2));
    
    this->addChild(hero->getImage(),2);
    
    object_list.resize(NUM_LINES);
    
    //set button Image
    for (int y=0;y<3; y++) {
        for (int x=0;x<3; x++) {
            Rect rect(float(x * 150),  // X座標
                      float(y * 156), // Y座標
                      float(150),      // 幅
                      float(156));    // 高さ
            vectorButton[i++] = Sprite::create("yazirusi.jpg", rect);
        }
    }
    
    //set power button
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    
    //set move & attack button
    setButton(vectorButton[1], vectorButton[1],
              Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2-100 ,
                   origin.y + closeItem->getContentSize().height/2+350),
              CC_CALLBACK_1(GameScene::upButtonCallBack, this));
    
    setButton(vectorButton[4], vectorButton[4],
              Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2-100 ,
                   origin.y + closeItem->getContentSize().height/2+200),
              CC_CALLBACK_1(GameScene::attackButtonCallBack, this));
    
    setButton(vectorButton[7], vectorButton[7],
              Vec2(origin.x + GameData::getVisibleSize().width - closeItem->getContentSize().width/2-100 ,
                   origin.y + closeItem->getContentSize().height/2+50),
              CC_CALLBACK_1(GameScene::downButtonCallBack, this));
    
    
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
        Director::getInstance()->end();
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
    
    rnd = rand()%100;
    lines = rand()%3;
    
    if(rnd < 10){
        std::string base="symptte";
        base = base + "0" + std::to_string(rnd%4+1) + ".jpg";
        auto new_enemy = new enemy(base,(line)lines);
        object_list[lines].push_back(new_enemy);
        this->addChild(new_enemy->getImage());
        dynamic_cast<enemy*>(new_enemy)->setMovement(25);
    }
    else;
    
}
