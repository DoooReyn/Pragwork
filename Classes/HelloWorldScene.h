#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void connect(cocos2d::Ref* pSender);
    void insert(cocos2d::Ref* pSender);
    void remove(cocos2d::Ref* pSender);
    void clear(cocos2d::Ref* pSender);
    void select(cocos2d::Ref* pSender);
    void disconnect(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
