//
//  BaseFrame.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/2.
//
//

#ifndef BaseFrame_hpp
#define BaseFrame_hpp

#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/UIHelper.h"
using namespace cocos2d;
using namespace cocos2d::ui;

enum class UI_FILE_TYPE : unsigned char {
    CSB,
    JSON,
    XML
};

class BaseFrame : public cocos2d::Layer {
public:
    std::string     m_sFrameName;   //窗口类名称
    std::string     m_sUIFile;      //窗口 UI 文件
    std::string     m_sTitleText;   //窗口标题文本
    UI_FILE_TYPE    m_eUIFileType;  //窗口 UI 文件类型：CSB，JSon，XML
    bool            m_bIsGuide;     //是否是新手引导
    bool            m_bUseBaseAnim; //是否使用原定的动画
    bool            m_bIsNeedAnim;  //是否需要支持弹出收起动画
    bool            m_bShouldMask;  //是否屏蔽下层触摸事件
    bool            m_bIsMultiTouch;//是否需要开启多点触摸(预留)
    bool            m_bTouchClose;  //触摸屏蔽层关闭
//    EventCode       m_eEventCode;   //注册事件类型
//    CustomEventListener*  m_event;  //注册事件
    static bool     m_bOnSingleton; //是否需要支持创建单例
    
private:
    static BaseFrame* m_pSingleton; //单例指针，如果不允许创建单例，当使用获取\
                                      单例方法时，每次都将获得全新的实例
    
public:
    BaseFrame();
    
//Singleton
    static BaseFrame* getInstance() {
        if(!m_bOnSingleton) return new BaseFrame();
        if(!m_pSingleton) m_pSingleton = new BaseFrame();
        return m_pSingleton;
    }
    
    static void destroyInstance() {
        if(!m_bOnSingleton) return;
        if(!m_pSingleton) return;
        CC_SAFE_DELETE(m_pSingleton);
    }
    
//Virtual
    virtual void onEnter();
    virtual void onExit();
    virtual void onCleanUp();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void onFrameUpdate();
    virtual void doEnterAnimation();
    virtual void doExitAnimation();
    virtual void loadUI();
    virtual void onCloseBtnEvt(Ref* pSender, Widget::TouchEventType type);
    virtual void onConfirmBtnEvt(Ref* pSender, Widget::TouchEventType type);
    virtual void onUpdateGuide();
    virtual void enableListenEvent();
    virtual void disableListenEvent();
    virtual void loadResources();
    virtual void cleanResources();

//Other
    void addMaskFrame();
    void removeMaskFrame();
    void setMaskColor(const Color3B& c3b);
    void setMaskOpacity(unsigned char opacity);
    void setMaskColorOpacity(const Color3B& c3b, unsigned char opacity);
    void setMaskZOrder(int zorer);
    
protected:
    ~BaseFrame();
    
private:
    void _loadUIFromCSB();
    void _loadUIFromJSON();
    void _loadUIFromXML();
};

#endif /* BaseFrame_hpp */
