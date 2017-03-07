//
//  TouchNode.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/7.
//
//

#include "TouchNode.hpp"

TouchNode::TouchNode () {
    Node::Node();
}

TouchNode::~TouchNode() {
    
}

void TouchNode::setTouchEnable(bool enable) {
    
}

void TouchNode::onEnter() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Node*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode)) {
            log("node began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            return true;
        }
        return false;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Node*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Node*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode)) {
            log("node ended... x = %f, y = %f", locationInNode.x, locationInNode.y);
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    

}

void TouchNode::onExit() {
    
}
