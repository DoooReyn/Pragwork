//
//  FrameManager.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#ifndef FrameManager_hpp
#define FrameManager_hpp

#include <iostream>
#include <vector>
#include "PragworkMacro.h"
USING_NS_CC;

// 窗口树
enum class EFrameTree : unsigned short {
    
};

// 窗口树管理
class FrameManager {
    INIT_INSTANCE(FrameManager);
private:
    std::vector<Layer> m_vecFrames;
public:
    void PushFrame(EFrameTree frame);
    cocos2d::Layer PopFrame();
    void gotoFrame(EFrameTree frame);
    void clear();
    
protected:
    FrameManager();
    ~FrameManager();
};
#endif /* FrameManager_hpp */
