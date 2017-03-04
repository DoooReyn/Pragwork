//
//  BaseScene.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//

#include "BaseScene.hpp"

BaseScene::BaseScene(std::string scenename)
: m_pSceneName(scenename)
, m_pMainFrame(NULL)
{
    Scene::Scene();
    m_vecFrames.clear();
}

BaseScene::~BaseScene() {
    for(unsigned long i=m_vecFrames.size(); i>0; i--) {
        m_vecFrames.at(i-1)->close();
    }
    if(m_pMainFrame)
        m_pMainFrame->close();
//    Scene::~Scene();
}

bool BaseScene::init() {
    bool initialized = Scene::init();
    
    m_pMainFrame = new BaseFrame();
    m_pMainFrame->m_bIsGuide = false;
    m_pMainFrame->m_bShouldMask = true;
    m_pMainFrame->m_bTouchClose = false;
    m_pMainFrame->m_bIsMutex = false;
    m_pMainFrame->m_eUIFileType = BaseFrame::UILoadMode::None;
    m_pMainFrame->m_bIsNeedAnim = false;
    m_pMainFrame->addMaskFrameAtBottom();
    m_pMainFrame->setMaskColorOpacity(Color3B::BLACK, 0);
    addChild(m_pMainFrame);
    
    return initialized;
}

BaseFrame* BaseScene::getMainFrame() {
    return m_pMainFrame;
}

void BaseScene::appendFrame(BaseFrame* pFrame) {
    eraseFrame(pFrame);
    
    if(pFrame->isMutexAll()) {
        removeAllFrame();
    }
    
    if(pFrame->isMutex()) {
        BaseFrame* pLastFrame = getLastFrame();
        if(pLastFrame && pLastFrame != pFrame) {
            pLastFrame->runAction(getActionByCode(ActionCode::FadeAwayBaseFrame));
        }
    }
    
    pFrame->setVisible(true);
    m_pMainFrame->addChild(pFrame);
    m_vecFrames.push_back(pFrame);
}

void BaseScene::removeLastFrame() {
    if(m_vecFrames.size() == 0) return;
    eraseFrame(m_vecFrames.at(m_vecFrames.size()-1));
    BaseFrame* pLastFrame = getLastFrame();
    if(pLastFrame)
//        pLastFrame->runAction(getActionByCode(ActionCode::FadeInBaseFrame));
        pLastFrame->setVisible(true);
}

BaseFrame* BaseScene::getLastFrame() {
    if(m_vecFrames.size() == 0) return NULL;
    return m_vecFrames.at(m_vecFrames.size()-1);
}

bool BaseScene::existFrame(BaseFrame* pFrame) {
    return std::find(m_vecFrames.begin(), m_vecFrames.end(), pFrame) != m_vecFrames.end();
}

bool BaseScene::eraseFrame(BaseFrame* pFrame) {
    vector<BaseFrame*>::iterator iter = std::find(m_vecFrames.begin(), m_vecFrames.end(), pFrame);
    if(iter != m_vecFrames.end()) {
        m_vecFrames.erase(iter);
        (*iter)->close();
        return true;
    }
    return false;
}

void BaseScene::removeAllFrame() {
    for(unsigned long i=m_vecFrames.size(); i>0; i--) {
        m_vecFrames.at(i-1)->close();
    }
    m_vecFrames.clear();
}
