//
//  FrameManager.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#include "FrameManager.hpp"
#include "SceneManager.hpp"

FrameManager* FrameManager::m_pInstance = NULL;

FrameManager::FrameManager()  {
    m_pCurFrame = NULL;
    m_pFrames.clear();
};

FrameManager::~FrameManager() {};


bool FrameManager::_isFrameExist(BaseLayer* frame) {
    vector<BaseLayer*>::iterator iter = std::find(m_pFrames.begin(), m_pFrames.end(), frame);
    return (iter != m_pFrames.end());
}

void FrameManager::PushFrame(BaseLayer* frame) {
    if(_isFrameExist(frame)) {
        return;
    }
    if(frame->isMutex()) {
        BaseLayer* layer = getPrevFrame();
        if(layer) {
            layer->retain();
            layer->removeFromParent();
            layer->release();
        }
    }
    m_pCurFrame = frame;
    m_pFrames.push_back(frame);
    if(SceneManager::getInstance()->getRunningScene()) {
        SceneManager::getInstance()->getRunningScene()->addChild(frame);
    }
}

BaseLayer* FrameManager::getPrevFrame() {
    if(m_pFrames.empty())
        return NULL;
    return m_pFrames.at(m_pFrames.size()-1);
}

BaseLayer* FrameManager::PopFrame() {
    if(!m_pCurFrame) return NULL;
    m_pCurFrame->removeFromParent();
    m_pFrames.erase(m_pFrames.end());
    m_pCurFrame = getPrevFrame();
    if(m_pCurFrame) return NULL;
    SceneManager::getInstance()->getRunningScene()->addChild(m_pCurFrame);
    return m_pCurFrame;
}
