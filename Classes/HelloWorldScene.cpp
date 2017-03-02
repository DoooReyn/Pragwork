#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BaseLayer.hpp"
#include "BaseFrame.hpp"
#include "CocosDefine.h"

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
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
//    BaseLayer* pLayer = new BaseLayer();
//    pLayer->show(true);
    
    BaseFrame* pFrame = new BaseFrame();
    auto label = Label::createWithTTF("BaseFrame", "fonts/Marker Felt.ttf", 24);
    label->setPosition(ccpRightCenter(pFrame));
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
//    Director::getInstance()->end();

//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//    #endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
