//
//  BaseLayer.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#include "BaseLayer.hpp"
#include "FrameManager.hpp"

BaseLayer::BaseLayer()
: m_strCsbFile("")
, m_strJsonFile("")
, m_strFramename("")
, m_strBackground("")
, m_bShowBackground("")
, m_c4bBackground(Color4B(0,0,0,128))
, m_bMutex(false)
, m_bTouchShade(false)
, m_bAnimate(false)
, m_bRunning(false)
, m_bIsPopup(false)
{
    Layout::Layout();
    init();
    initUI();
    initData();
    setLangText();
    Text* text = Text::create();
    text->setString("Show Something");
    text->setFontSize(40);
    text->setPosition(Vec2(320.f, 120.f));
    addChild(text);
}

BaseLayer::~BaseLayer()
{
    
}

void BaseLayer::initUI() {
    if(!m_strCsbFile.empty()) {
        _initUIFromCsb();
    } else if (!m_strCsbFile.empty()) {
        _initUIFromJson();
    }
}

void BaseLayer::initData() {
    
}

void BaseLayer::setLangText() {
    
}

void BaseLayer::_initUIFromCsb() {
    
}

void BaseLayer::_initUIFromJson() {
    
}

void BaseLayer::show(bool animate) {
    m_bAnimate = animate;
    FrameManager::getInstance()->PushFrame(this);
}

void BaseLayer::close() {
    FrameManager::getInstance()->PopFrame();
}

void BaseLayer::onEnter()
{
    Layout::onEnter();
    if(!m_bAnimate) return;
    stopAllActions();
    ScaleTo     *a1 = ScaleTo::create(.1f, 1.12f);
    DelayTime   *a2 = DelayTime::create(.05f);
    ScaleTo     *a3 = ScaleTo::create(.05f, 1.f);
    Sequence    *sq = Sequence::create(a1, a2, a3, NULL);
    runAction(sq);
}

void BaseLayer::onExit() {
    Layout::onExit();
    if(!m_bAnimate) return;
    stopAllActions();
    ScaleTo     *a1 = ScaleTo::create(.05f, 1.12f);
    DelayTime   *a2 = DelayTime::create(.05f);
    ScaleTo     *a3 = ScaleTo::create(.05f, .0f);
    Sequence    *sq = Sequence::create(a1, a2, a3, NULL);
    runAction(sq);
}
