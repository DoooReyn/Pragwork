//
//  MainScene.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//

#include "CocosDefine.h"
#include "MainScene.hpp"

static int i = 0;

MainScene::MainScene() {
    BaseScene::BaseScene();
    m_pSceneName = "MainScene";
    init();
}

MainScene::~MainScene() {
//    BaseScene::~BaseScene();
}

BaseFrame* createFrame(string name, int index) {
    BaseFrame* pFrame = new BaseFrame();
    
    pFrame->m_sFrameName = name;
    pFrame->m_bIsNeedAnim = true;
    pFrame->m_bShouldMask = true;
    pFrame->m_bIsMutex = false;//true;
    pFrame->m_bIsMutexAll = index == 3;//true;
    pFrame->addMaskFrameAtBottom();
    pFrame->setMaskColorOpacity(Color3B::BLUE, 168);
    auto pLabel = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 40);
    pLabel->setAnchorPoint(Vec2(0, 0.5));
    Vec2 pos = ccpLeftCenter(pFrame);
    pLabel->setPosition(pos.x, pos.y+30*(2-index));
    pFrame->addChild(pLabel, 2);
    
    return pFrame;
}

bool MainScene::init() {
    bool initialize = BaseScene::init();
    
    auto label1 = Label::createWithTTF("AppendFrame", "fonts/Marker Felt.ttf", 20);
    auto label2 = Label::createWithTTF("RemoveFrame", "fonts/Marker Felt.ttf", 20);
    auto label3 = Label::createWithTTF("RemoveAll", "fonts/Marker Felt.ttf", 20);
    
    auto closeItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(MainScene::appendFrameCB, this));
    auto closeItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(MainScene::removeFrameCB, this));
    auto closeItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(MainScene::clearFrameCB,  this));
    
    auto menu = Menu::create(closeItem1, closeItem2, closeItem3, NULL);
    menu->alignItemsVerticallyWithPadding(30);
    menu->setPosition(ccpCenter(this));
    this->addChild(menu, 9999);
    
    m_vecLocalFrame = {
        createFrame("Frame1", 1),
        createFrame("Frame2", 2),
        createFrame("Frame3", 3)
    };
    
    return initialize;
}

void MainScene::appendFrameCB(cocos2d::Ref* pSender) {
    if(i>2) return;
    if(i<0) return;
    i++;
    appendFrame(m_vecLocalFrame.at(i-1));
}

void MainScene::removeFrameCB(cocos2d::Ref* pSender) {
    if(i>3) return;
    if(i<1) return;
    i--;
    removeLastFrame();
}

void MainScene::clearFrameCB(cocos2d::Ref* pSender) {
    i = 0;
    removeAllFrame();
}
