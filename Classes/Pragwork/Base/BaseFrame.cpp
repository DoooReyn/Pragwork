//
//  BaseFrame.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/2.
//
//
#include "TagDefine.h"
#include "BaseFrame.hpp"

bool BaseFrame::m_bOnSingleton = false;
BaseFrame* BaseFrame::m_pSingleton = NULL;

BaseFrame::BaseFrame()
: m_sFrameName("")
, m_sUIFile("")
, m_sTitleText("")
, m_eUIFileType(UI_FILE_TYPE::CSB)
, m_bIsGuide(false)
, m_bShouldMask(false)
, m_bUseBaseAnim(true)
, m_bIsNeedAnim(true)
, m_bIsMultiTouch(false)
, m_bTouchClose(false)
{
    CCLOG("%s ctor.", m_sFrameName.c_str());
    Layer::init();
}

BaseFrame::~BaseFrame() {
    Layer::~Layer();
    CCLOG("%s destroy.", m_sFrameName.c_str());
}

void BaseFrame::onEnter() {
    loadResources();
    
    Layer::onEnter();
    
    enableListenEvent();
    
    if(m_bIsGuide) {
        onUpdateGuide();
    }
}

void BaseFrame::onExit() {
    Layer::onExit();
    
    cleanResources();
    
    disableListenEvent();
}

void BaseFrame::onCleanUp() {
    cleanResources();
    
    Layer::cleanup();
}


void BaseFrame::onEnterTransitionDidFinish() {
    Layer::onEnterTransitionDidFinish();
    
    doEnterAnimation();
}


void BaseFrame::onExitTransitionDidStart() {
    Layer::onExitTransitionDidStart();
    
    doExitAnimation();
}


void BaseFrame::onFrameUpdate() {
    
}


void BaseFrame::doEnterAnimation() {
    if(!m_bIsNeedAnim) return;
    
    if(m_bUseBaseAnim) {
        stopActionByTag(ActionTag::BaseEnter);
        ScaleTo     *a1 = ScaleTo::create(.1f, 1.12f);
        DelayTime   *a2 = DelayTime::create(.05f);
        ScaleTo     *a3 = ScaleTo::create(.05f, 1.f);
        Sequence    *sq = Sequence::create(a1, a2, a3, NULL);
        sq->setTag(ActionTag::BaseEnter);
        runAction(sq);
    }
}

void BaseFrame::doExitAnimation() {
    if(!m_bIsNeedAnim) return;
    
    if(m_bUseBaseAnim) {
        stopActionByTag(ActionTag::BaseExit);
        ScaleTo     *a1 = ScaleTo::create(.05f, 1.12f);
        DelayTime   *a2 = DelayTime::create(.05f);
        ScaleTo     *a3 = ScaleTo::create(.05f, .0f);
        Sequence    *sq = Sequence::create(a1, a2, a3, NULL);
        sq->setTag(ActionTag::BaseExit);
        runAction(sq);
    }
}

void BaseFrame::loadUI() {
    if(m_sUIFile.empty()) return;
    
    switch (m_eUIFileType) {
        case UI_FILE_TYPE::CSB :
            _loadUIFromCSB();
            break;
        case UI_FILE_TYPE::JSON :
            _loadUIFromJSON();
            break;
        case UI_FILE_TYPE::XML :
            _loadUIFromXML();
            break;
        default:
            break;
    }
}


void BaseFrame::onCloseBtnEvt(Ref* pSender, Widget::TouchEventType type) {
    if(m_bTouchClose) {
        if(type == Widget::TouchEventType::ENDED) {
            removeFromParent();
        }
    }
}


void BaseFrame::onConfirmBtnEvt(Ref* pSender, Widget::TouchEventType type) {
    
}


void BaseFrame::onUpdateGuide() {
    
}

void BaseFrame::enableListenEvent() {
    
}

void BaseFrame::disableListenEvent() {
    
}


void BaseFrame::loadResources() {
    
}


void BaseFrame::cleanResources() {
    
}


void BaseFrame::addMaskFrame() {
    if(!m_bShouldMask) return;
    
    Layout* mask = dynamic_cast<Layout*>(getChildByTag(FrameTag::Mask));
    if(mask) return;
    mask = Layout::create();
    mask->setTag(FrameTag::Mask);
    mask->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    mask->setBackGroundColor(Color3B::BLACK);
    mask->setBackGroundColorOpacity(128);//默认背景为黑色半透明
    mask->setContentSize(Director::getInstance()->getWinSize());
    mask->setTouchEnabled(true);
    mask->addTouchEventListener(CC_CALLBACK_2(BaseFrame::onCloseBtnEvt, this));
    ui::Helper::doLayout(mask);
    addChild(mask, -1);//默认添加在全部层的底部
}


void BaseFrame::removeMaskFrame() {
    auto mask = getChildByTag(FrameTag::Mask);
    if(!mask) return;
    mask->removeFromParent();
}

void BaseFrame::setMaskColorOpacity(const Color3B& c3b, unsigned char opacity) {
    Layout* mask = dynamic_cast<Layout*>(getChildByTag(FrameTag::Mask));
    if(!mask) return;
    mask->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    mask->setBackGroundColor(c3b);
    mask->setBackGroundColorOpacity(opacity);
}

void BaseFrame::setMaskOpacity(unsigned char opacity) {
    Layout* mask = dynamic_cast<Layout*>(getChildByTag(FrameTag::Mask));
    if(!mask) return;
    mask->setBackGroundColorOpacity(opacity);
}

void BaseFrame::setMaskColor(const cocos2d::Color3B &c3b) {
    Layout* mask = dynamic_cast<Layout*>(getChildByTag(FrameTag::Mask));
    if(!mask) return;
    mask->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    mask->setBackGroundColor(c3b);
}

void BaseFrame::setMaskZOrder(int zorer) {
    Layout* mask = dynamic_cast<Layout*>(getChildByTag(FrameTag::Mask));
    if(!mask) return;
    mask->setLocalZOrder(zorer);
}

void BaseFrame::_loadUIFromCSB() {
    std::string fullpath  = FileUtils::getInstance()->fullPathForFilename("res/csb/" + m_sUIFile);
    std::string extension = FileUtils::getInstance()->getFileExtension(fullpath);
    if(extension != ".csb") return;
    
    Data data = FileUtils::getInstance()->getDataFromFile(fullpath);
    auto node = CSLoader::createNode(data);
    if (node == NULL) return;
    
    node->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(node);
    addChild(node);
}

void BaseFrame::_loadUIFromJSON() {
    std::string fullpath  = FileUtils::getInstance()->fullPathForFilename("res/json/" + m_sUIFile);
    std::string extension = FileUtils::getInstance()->getFileExtension(fullpath);
    if(extension != ".json") return;
    
    auto node = CSLoader::getInstance()->createNodeFromJson(fullpath);
    if (node == NULL) return;
    
    node->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(node);
    addChild(node);
}

void BaseFrame::_loadUIFromXML() {
    std::string fullpath  = FileUtils::getInstance()->fullPathForFilename("res/xml/" + m_sUIFile);
    std::string extension = FileUtils::getInstance()->getFileExtension(fullpath);
    if(extension != ".xml") return;
    // TODO
}

