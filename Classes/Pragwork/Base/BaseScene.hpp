//
//  BaseScene.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include "BaseFrame.hpp"

class BaseScene : public cocos2d::Scene {
private:
    BaseFrame* m_pMainFrame;
    std::vector<BaseFrame*> m_vecFrames;
protected:
    std::string m_pSceneName;
public:
    BaseScene(std::string scenename="BaseScene");
    ~BaseScene();
    BaseFrame* getMainFrame();
    BaseFrame* getLastFrame();
    void appendFrame(BaseFrame* pFrame);
    void removeLastFrame();
    void removeAllFrame();
    bool existFrame(BaseFrame* pFrame);
    bool eraseFrame(BaseFrame* pFrame);
    virtual bool init();
    
};

#endif /* BaseScene_hpp */
