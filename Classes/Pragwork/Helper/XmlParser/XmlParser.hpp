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

class XmlParser {
    static XmlParser* m_pInstance;
public:
    static XmlParser* getInstance() {
        if(!m_pInstance)
            m_pInstance = new XmlParser();
        return m_pInstance;
    }
    XMLDocument* GetDocument(const char* filename);
    XMLDocument* GetDocumentFromString(const char* text);
    int GetChildrenCount(XMLElement*);
    int GetAttributeCount(XMLElement*);
protected:
    XmlParser();
    ~XmlParser();
};

#endif /* XmlParser_hpp */
