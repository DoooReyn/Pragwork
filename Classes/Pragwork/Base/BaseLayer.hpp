//
//  BaseLayer.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#ifndef BaseLayer_hpp
#define BaseLayer_hpp

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

class BaseLayer : public Layout {
private:
    string  m_strCsbFile;
    string  m_strJsonFile;
    string  m_strFramename;
    string  m_strBackground;
    Color4B m_c4bBackground;
    bool    m_bShowBackground;
    bool    m_bMutex;
    bool    m_bTouchShade;
    bool    m_bAnimate;
    bool    m_bRunning;
    bool    m_bIsPopup;
public:
    BaseLayer();
    virtual ~BaseLayer();
    virtual void show(bool animate);
    virtual void close();
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void initUI();
    virtual void initData();
    virtual void setLangText();
    inline bool isMutex() { return m_bMutex; }
    inline bool isTouchShade() { return m_bTouchShade; }
    inline bool isAnimate() { return m_bAnimate; }
    inline bool isRunning() { return m_bRunning; }
    inline bool isPopup() { return m_bIsPopup; }
    inline bool isShowBackgorund() { return m_bShowBackground; }
private:
    void _initUIFromCsb();
    void _initUIFromJson();
};

#endif /* BaseLayer_hpp */
