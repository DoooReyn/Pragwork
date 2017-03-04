//
//  MainScene.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include "BaseScene.hpp"

class MainScene : public BaseScene {
private:
    vector<BaseFrame*> m_vecLocalFrame;
public:
    MainScene();
    ~MainScene();
    bool init();
private:
    void appendFrameCB(cocos2d::Ref* pSender);
    void removeFrameCB(cocos2d::Ref* pSender);
    void clearFrameCB (cocos2d::Ref* pSender);
};

#endif /* MainScene_hpp */
