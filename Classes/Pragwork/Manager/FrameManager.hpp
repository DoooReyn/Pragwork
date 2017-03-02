//
//  FrameManager.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#ifndef FrameManager_hpp
#define FrameManager_hpp
#include <vector>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "PragworkMacro.h"
#include "UI/Layer/init.h"
#include "HelloWorldScene.h"
#include "BaseFrame.hpp"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

// 窗口树管理
class FrameManager {
    INIT_INSTANCE(FrameManager);
private:
    vector<BaseFrame*> m_pFrames;
    BaseFrame* m_pCurFrame;
public:
    void clear();
    BaseFrame* PopFrame();
    BaseFrame* getPrevFrame();
    void PushFrame(BaseFrame*);
protected:
    FrameManager();
    ~FrameManager();
private:
    bool _isFrameExist(BaseFrame*);
    void _loadFrames();
};
#endif /* FrameManager_hpp */
