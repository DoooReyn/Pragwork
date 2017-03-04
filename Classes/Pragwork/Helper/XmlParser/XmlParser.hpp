//
//  XmlParser.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//

#ifndef XmlParser_hpp
#define XmlParser_hpp

#include "CocoSupport.h"

class XmlPaser {
    static XmlPaser* m_pInstance;
public:
    static XmlPaser* getInstance() {
        if(!m_pInstance)
            m_pInstance = new XmlPaser();
        return m_pInstance;
    }
    XMLDocument* GetDocument(const char* filename);
    int GetChildrenCount(XMLElement*);
    int GetAttributeCount(XMLElement*);
protected:
    XmlPaser();
    ~XmlPaser();
};

#endif /* XmlParser_hpp */
