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
#include "TagDefine.h"
#include "ActionDefine.h"
#include "ZOrderDefine.h"
using namespace cocos2d;
using namespace cocos2d::ui;


class BaseFrame : public cocos2d::Layer {
    
public:
    
/*===========================================================
 > 以下是 UI 加载模式定义
 ============================================================
 */
    enum class UILoadMode : unsigned char {
        None,
        Csb,
        Json,
        Xml
    };
    
    
/*===========================================================
 > 以下是 BaseFrame 构造所需的字段
 ============================================================
 */
    std::string     m_sFrameName;       //窗口类名称
    std::string     m_sUIFile;          //窗口 UI 文件
    std::string     m_sTitleText;       //窗口标题文本
    UILoadMode    m_eUIFileType;      //窗口 UI 文件类型：CSB，JSon，XML
    bool            m_bIsGuide;         //是否是新手引导
    bool            m_bUseBaseAnim;     //是否使用原定的动画
    bool            m_bIsNeedAnim;      //是否需要支持弹出收起动画
    bool            m_bShouldMask;      //是否屏蔽下层触摸事件
    bool            m_bIsMultiTouch;    //是否需要开启多点触摸 TODO
    bool            m_bTouchClose;      //触摸屏蔽层关闭
    ActionCode      m_eEnterCode;       //进入动画
    ActionCode      m_eExitCode;        //进入动画
    static bool     m_bOnSingleton;     //是否需要支持创建单例
                                        //    EventCode       m_eEventCode;     //注册事件类型
                                        //    CustomEventListener*  m_event;    //注册事件
    
private:
    static BaseFrame* m_pSingleton; //单例指针，如果不允许创建单例，当使用获取\
                                      单例方法时，每次都将获得全新的实例
    
public:

/*===========================================================
 > 以下是构造函数
 ============================================================
 */
    BaseFrame();
    
/*===========================================================
 > 以下是单例获取和销毁接口
 ============================================================
 */
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
    
/*===========================================================
 *> 以下是虚函数接口,子类可自定义继承,以实现扩展
 ============================================================
 */
    
    /******************************
     * 进入
     ******************************/
    virtual void onEnter();
    
    /******************************
     * 退出
     ******************************/
    virtual void onExit();
    
    /******************************
     * 退出时清理
     ******************************/
    virtual void onCleanUp();
    
    /******************************
     * 完成进入过渡
     ******************************/
    virtual void onEnterTransitionDidFinish();
    
    /******************************
     * 开始退出过渡
     ******************************/
    virtual void onExitTransitionDidStart();
    
    /******************************
     * 帧调用 TODO
     ******************************/
    virtual void onFrameUpdate();
    
    /******************************
     * 执行进入动画
     ******************************/
    virtual void doEnterAnimation();
    
    /******************************
     * 执行退出动画
     ******************************/
    virtual void doExitAnimation();
    
    /******************************
     * 加载 UI
     ******************************/
    virtual void loadUI();
    
    /******************************
     * 注册关闭按钮事件
     ******************************/
    virtual void onCloseBtnEvt(Ref* pSender, Widget::TouchEventType type);
    
    /******************************
     * 注册确定按钮事件
     ******************************/
    virtual void onConfirmBtnEvt(Ref* pSender, Widget::TouchEventType type);
    
    /******************************
     * 刷新新手引导 TODO
     ******************************/
    virtual void onUpdateGuide();
    
    /******************************
     * 开启事件监听 TODO
     ******************************/
    virtual void enableListenEvent();
    
    /******************************
     * 关闭事件监听
     ******************************/
    virtual void disableListenEvent();
    
    /******************************
     * 加载资源( Textures, Audio 等)
     ******************************/
    virtual void loadResources();
    
    /******************************
     * 清理资源( Textures, Audio 等)
     ******************************/
    virtual void cleanResources();

/*===========================================================
 > 以下是屏蔽层相关接口
 ============================================================
 */
    
    /******************************
     * 添加一个屏蔽层
     ******************************/
    void addMaskFrame(int nZOrder=-1, const Color3B& color = Color3B::BLACK, unsigned char opaicty=128);
    
    /******************************
     * 添加一个位于顶部的屏蔽层
     ******************************/
    void addMaskFrameAtTop();
    
    /******************************
     * 添加一个位于底部的屏蔽层
     ******************************/
    void addMaskFrameAtBottom();
    
    /******************************
     * 移除屏蔽层
     ******************************/
    void removeMaskFrame();
    
    /******************************
     * 设置屏蔽层的渲染层级
     ******************************/
    void setMaskZOrder(int zorer);
    
    /******************************
     * 设置屏蔽层的颜色和透明度
     ******************************/
    void setMaskColorOpacity(const Color3B& c3b=Color3B::BLACK, unsigned char opacity=128);

/*===========================================================
 > 以下是设置进入动画和退出动画的接口
 ============================================================
 */
    inline void setEnterActionCode(ActionCode code) { m_eEnterCode = code; }
    inline void setExitActionCode(ActionCode code)  { m_eExitCode  = code; }
    
/*===========================================================
 > 以下是新手引导相关接口
 ============================================================
 */
    inline bool getIsGuide() { return m_bIsGuide; }
    inline void setIsGuide(bool isGuide) { m_bIsGuide = isGuide; }
    
/*===========================================================
 > 以下是多点触摸相关接口
 ============================================================
 */
    inline bool getIsMutilTouch() { return m_bIsMultiTouch; }
    inline void setIsMutilTouch(bool isMultiTouch) { m_bIsMultiTouch = isMultiTouch; }
    
protected:
    
/*===========================================================
 > 以下是销毁函数
 ============================================================
 */
    ~BaseFrame();
    
private:
    
/*===========================================================
 > 以下是 UI 加载模式相关接口
 ============================================================
 */
    void _loadUIFromCSB();
    void _loadUIFromJSON();
    void _loadUIFromXML();
};

#endif /* BaseFrame_hpp */
