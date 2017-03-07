//
//  TouchNode.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/7.
//
//

#ifndef TouchNode_hpp
#define TouchNode_hpp

#include <CocoSupport.h>

class TouchNode : public Node {
private:
    EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events
    
public:
    TouchNode();
    ~TouchNode();
    
    void setTouchEnable(bool enable);
    
    virtual void onEnter();
    virtual void onExit();
    
};

#endif /* TouchNode_hpp */
