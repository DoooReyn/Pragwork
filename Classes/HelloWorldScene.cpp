#include "HelloWorldScene.h"
#include "BaseFrame.hpp"
#include "CocosDefine.h"
#include "LocalDBManager.hpp"
#include "ActionDefine.h"

USING_NS_CC;

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto label1 = Label::createWithTTF("connect", "fonts/Marker Felt.ttf", 20);
    auto label2 = Label::createWithTTF("insert", "fonts/Marker Felt.ttf", 20);
    auto label3 = Label::createWithTTF("remove", "fonts/Marker Felt.ttf", 20);
    auto label4 = Label::createWithTTF("clear", "fonts/Marker Felt.ttf", 20);
    auto label5 = Label::createWithTTF("select", "fonts/Marker Felt.ttf", 20);
    auto label6 = Label::createWithTTF("disconnect", "fonts/Marker Felt.ttf", 20);
    
    auto closeItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(HelloWorld::connect, this));
    auto closeItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::insert, this));
    auto closeItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(HelloWorld::remove, this));
    auto closeItem4 = MenuItemLabel::create(label4, CC_CALLBACK_1(HelloWorld::clear, this));
    auto closeItem5 = MenuItemLabel::create(label5, CC_CALLBACK_1(HelloWorld::select, this));
    auto closeItem6 = MenuItemLabel::create(label6, CC_CALLBACK_1(HelloWorld::disconnect, this));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem1, closeItem2, closeItem3, closeItem4, closeItem5, closeItem6, NULL);
    menu->setPosition(WIN_SIZE.width/2, WIN_SIZE.height/2);
    menu->alignItemsVerticallyWithPadding(20);
    this->addChild(menu, 1);
    
    auto labelClose = Label::createWithTTF("close", "fonts/Marker Felt.ttf", 20);
    auto closeItem = MenuItemLabel::create(labelClose, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    auto menuClose = Menu::create(closeItem, NULL);
    menuClose->setPosition(WIN_SIZE.width-labelClose->getContentSize().width-20, labelClose->getContentSize().height+20);
    this->addChild(menuClose);


    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    
    return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    
    BaseFrame* pFrame = new BaseFrame();
    auto label = Label::createWithTTF("BaseFrame", "fonts/arial.ttf", 24);
    label->setPosition(ccpCenter(pFrame));
    Button* pButton = Button::create("CloseNormal.png", "CloseSelected.png");
    pButton->setTitleText("Button Text");
    pButton->setContentSize(Size(200,100));
    pButton->setTouchEnabled(true);
    pButton->setTitleColor(Color3B::BLUE);
    pButton->setPosition(ccpCenter(pFrame));
    pFrame->addChild(pButton, 1);
    pFrame->addChild(label, 1);
    pFrame->m_bShouldMask = true;
    pFrame->m_bTouchClose = true;
    pFrame->addMaskFrameAtTop();
    pFrame->setMaskColorOpacity(Color3B::GREEN);
    pFrame->setPosition(ccpLeftBottom(this));
    addChild(pFrame, 2);
    
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
    #endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

    
}

void HelloWorld::connect(cocos2d::Ref* pSender) {
    ((Node*)pSender)->runAction(getActionByCode(ActionCode::EnterBaseFrame));
    LocalDBManager::getInstance()->connect();
}

void HelloWorld::insert(cocos2d::Ref* pSender) {
    ((Node*)pSender)->runAction(getActionByCode(ActionCode::EnterBaseFrame));
    LocalDBManager::getInstance()->insert("version", "0.0.1");
    LocalDBManager::getInstance()->insert("code", "100");
}

void HelloWorld::remove(cocos2d::Ref* pSender) {
    ((Node*)pSender)->runAction(getActionByCode(ActionCode::EnterBaseFrame));
    LocalDBManager::getInstance()->remove("version");
    LocalDBManager::getInstance()->remove("code");
}

void HelloWorld::clear(cocos2d::Ref* pSender) {
    LocalDBManager::getInstance()->clear();
}

void HelloWorld::select(cocos2d::Ref* pSender) {
    std::string out = LocalDBManager::getInstance()->select("version");
    if(out.size()==0) {
        ((Node*)pSender)->runAction(MoveBy::create(0.1, Vec2(2,0)));
    }
//    LocalDBManager::getInstance()->select("code");
    vector<std::string> vec = {"version", "code", "ai"};
    LocalDBManager::getInstance()->multiselect(vec);
}

void HelloWorld::disconnect(cocos2d::Ref* pSender) {
    ((Node*)pSender)->runAction(getActionByCode(ActionCode::EnterBaseFrame));
    LocalDBManager::getInstance()->disconnect();
}




