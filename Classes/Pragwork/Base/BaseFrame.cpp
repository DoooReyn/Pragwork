//
//  BaseFrame.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/2.
//
//
#include "BaseFrame.hpp"

bool BaseFrame::m_bOnSingleton = false;
BaseFrame* BaseFrame::m_pSingleton = NULL;

BaseFrame::BaseFrame()
: m_sFrameName("BaseFrame")
, m_sUIFile("")
, m_sTitleText("")
, m_eUIFileType(UILoadMode::Csb)
, m_bIsGuide(false)
, m_bShouldMask(false)
, m_bUseBaseAnim(true)
, m_bIsNeedAnim(true)
, m_bIsMultiTouch(false)
, m_bTouchClose(false)
, m_eEnterCode(ActionCode::None)
, m_eExitCode(ActionCode::None)
{
    CCLOG("%s ctor.", m_sFrameName.c_str());
    Layer::init();
}

BaseFrame::~BaseFrame() {
    Layer::~Layer();
    
    CCLOG("%s destroy.", m_sFrameName.c_str());
}

void BaseFrame::onEnter() {
    CCLOG("%s onEnter", m_sFrameName.c_str());
    
    Layer::onEnter();
    loadResources();
    enableListenEvent();
    if(m_bIsGuide) {
        onUpdateGuide();
    }
}

void BaseFrame::onExit() {
    CCLOG("%s onExit", m_sFrameName.c_str());
    
    Layer::onExit();
    cleanResources();
    disableListenEvent();
}

void BaseFrame::onCleanUp() {
    CCLOG("%s onCleanUp", m_sFrameName.c_str());
    
    cleanResources();
    Layer::cleanup();
}

void BaseFrame::onEnterTransitionDidFinish() {
    CCLOG("%s onEnterTransitionDidFinish", m_sFrameName.c_str());
    
    Layer::onEnterTransitionDidFinish();
    doEnterAnimation();
}

void BaseFrame::onExitTransitionDidStart() {
    CCLOG("%s onExitTransitionDidStart", m_sFrameName.c_str());
    
    Layer::onExitTransitionDidStart();
    doExitAnimation();
}

void BaseFrame::onFrameUpdate() {
    
}

void BaseFrame::doEnterAnimation() {
    if(!m_bIsNeedAnim) return;
    
    setScale(.5f);
    stopActionByTag(ActionCode::EnterBaseFrame);
    if(m_bUseBaseAnim) {
        runAction(getActionByCode(ActionCode::EnterBaseFrame));
    } else {
        if(m_eEnterCode == ActionCode::None) return;
        runAction(getActionByCode(m_eEnterCode));
    }
}

void BaseFrame::doExitAnimation() {
    if(!m_bIsNeedAnim) return;
    
    stopActionByTag(ActionCode::ExitBaseFrame);
    if(m_bUseBaseAnim) {
        runAction(getActionByCode(ActionCode::ExitBaseFrame));
    } else {
        if(m_eExitCode == ActionCode::None) return;
        runAction(getActionByCode(m_eExitCode));
    }
}

void BaseFrame::loadUI() {
    if(m_sUIFile.empty()) return;
    
    CCLOG("%s Load UI from %s", m_sFrameName.c_str(), m_sUIFile.c_str());
    
    switch (m_eUIFileType) {
        case UILoadMode::Csb :
            _loadUIFromCSB();
            break;
        case UILoadMode::Json :
            _loadUIFromJSON();
            break;
        case UILoadMode::Xml :
            _loadUIFromXML();
            break;
        default:
            break;
    }
}

void BaseFrame::onCloseBtnEvt(Ref* pSender, Widget::TouchEventType type) {
    int nSenderTag = ((Node*)pSender)->getTag();
    bool bIsMaskSender  = m_bTouchClose && nSenderTag == FrameTag::Mask;
    bool bIsOtherSender = nSenderTag != FrameTag::Mask;
    
    if(!(bIsMaskSender || bIsOtherSender)) return;
    
    if(type == Widget::TouchEventType::ENDED) {
        if(m_bIsNeedAnim) {
            doExitAnimation();
        } else {
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

void BaseFrame::addMaskFrame(int nZOrder, const Color3B& color, unsigned char opacity) {
    if(!m_bShouldMask) return;
    
    Layout* mask = dynamic_cast<Layout*>(getChildByTag(FrameTag::Mask));
    if(mask) return;
    mask = Layout::create();
    mask->setTag(FrameTag::Mask);
    mask->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    mask->setBackGroundColor(color);
    mask->setBackGroundColorOpacity(opacity);//默认背景为黑色半透明
    mask->setContentSize(Director::getInstance()->getWinSize());
    mask->setTouchEnabled(true);
    mask->addTouchEventListener(CC_CALLBACK_2(BaseFrame::onCloseBtnEvt, this));
    cocos2d::ui::Helper::doLayout(mask);
    addChild(mask, nZOrder);
}

void BaseFrame::addMaskFrameAtTop() {
    addMaskFrame(ZOrderCode::MaskAtTop);
}

void BaseFrame::addMaskFrameAtBottom() {
    addMaskFrame(ZOrderCode::MaskAtBottom);
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
    cocos2d::ui::Helper::doLayout(node);
    addChild(node);
}

void BaseFrame::_loadUIFromJSON() {
    std::string fullpath  = FileUtils::getInstance()->fullPathForFilename("res/json/" + m_sUIFile);
    std::string extension = FileUtils::getInstance()->getFileExtension(fullpath);
    if(extension != ".json") return;
    
    auto node = CSLoader::getInstance()->createNodeFromJson(fullpath);
    if (node == NULL) return;
    
    node->setContentSize(Director::getInstance()->getWinSize());
    cocos2d::ui::Helper::doLayout(node);
    addChild(node);
}

void BaseFrame::_loadUIFromXML() {
    std::string fullpath  = FileUtils::getInstance()->fullPathForFilename("res/xml/" + m_sUIFile);
    std::string extension = FileUtils::getInstance()->getFileExtension(fullpath);
    if(extension != ".xml") return;
    // TODO
}

