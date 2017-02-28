//
//  PragworkMacro.h
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#ifndef PragworkMacro_h
#define PragworkMacro_h

#define NS_PW_BEGIN     namespace pragwork {
#define NS_PW_END       }
#define USE_NS_PW       using namespace pragwork
#define NS_PW           ::pragwork

#define INSTANCE(__TYPE__)      __TYPE__::getInstance()

#define INIT_INSTANCE(__TYPE__) \
private:\
static __TYPE__* m_pInstance;\
public:\
static __TYPE__* getInstance() { \
    if(m_pInstance) return m_pInstance; \
    return m_pInstance = new __TYPE__(); \
}



#endif /* PragworkMacro_h */
