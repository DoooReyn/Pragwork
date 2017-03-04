//
//  XmlParser.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//

#include "XmlParser.hpp"

XmlPaser* XmlPaser::m_pInstance = NULL;

XmlPaser::XmlPaser() {
    
}

XmlPaser::~XmlPaser() {
    
}

XMLDocument* XmlPaser::GetDocument(const char* filename) {
    XMLDocument* doc = new XMLDocument;
    XMLError err = doc->LoadFile(FileUtils::getInstance()->fullPathForFilename(filename).c_str());
    if(err != XMLError::XML_SUCCESS)
        return NULL;
    return doc;
}

int XmlPaser::GetChildrenCount(XMLElement* element) {
    if(!element) return 0;
    
    int count = 0;
    for( XMLNode* ele = element->FirstChild(); ele; ele = ele->NextSibling() ) {
        count++;
    }
    CCLOG("element [%s] have [%d] children", element->Name(), count);
    return count;
}

int XmlPaser::GetAttributeCount(XMLElement* element) {
    if(!element) return 0;
    int count = element->AttributeCount();
    CCLOG("element [%s] have [%d] attributions", element->Name(), count);
    return count;
}
