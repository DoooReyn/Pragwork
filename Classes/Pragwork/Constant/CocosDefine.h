//
//  CocosDefine.h
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/1.
//
//

#ifndef CocosDefine_h
#define CocosDefine_h

#define WIN_SIZE Director::getInstance()->getWinSize()

#define JSON_STR_TO(json,type)\
CCString::create(json.asCString())->type##Value()

//-- Center point maker
#define ccpCenter(node) ccp(node->getContentSize().width*0.5f, node->getContentSize().height*0.5f)
#define ccpTopCenter(node) ccp(node->getContentSize().width*0.5f, node->getContentSize().height)
#define ccpBottomCenter(node) ccp(node->getContentSize().width*0.5f, 0)
#define ccpLeftCenter(node) ccp(0, node->getContentSize().height*0.5f)
#define ccpRightCenter(node) ccp(node->getContentSize().width, node->getContentSize().height*0.5f)

#define MaskLayer(opacity) (LayerColor::create(ccc4(0, 0, 0, opacity)))
#define DefaultMaskLayer MaskLayer(128)

//-- Game internal version control
#define SECRET_KEY "129*(<da?"
#define SECRET_XOR_KEY "$#((Lwd8*da))#$"
#define APP_ID "pramwork_demo"
extern const char* getAppVersion();
#define APP_VERSION getAppVersion()

typedef std::pair<cocos2d::Ref*, cocos2d::SEL_CallFunc> CALLBACK_PAIR;

#endif /* CocosDefine_h */
