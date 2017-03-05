//
//  XmlParser.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//

#include "XmlParser.hpp"

XmlParser* XmlParser::m_pInstance = NULL;

XmlParser::XmlParser() {
    
}

XmlParser::~XmlParser() {
    
}

XMLDocument* XmlParser::GetDocument(const char* filename) {
    XMLDocument* doc = new XMLDocument;
    XMLError err = doc->LoadFile(FileUtils::getInstance()->fullPathForFilename(filename).c_str());
    if(err != XMLError::XML_SUCCESS)
        return NULL;
    return doc;
}

XMLDocument* XmlParser::GetDocumentFromString(const char* text) {
    XMLDocument* doc = new XMLDocument;
    XMLError err = doc->Parse(text);
    if(err != XMLError::XML_SUCCESS) {
        return NULL;
    }
    return doc;
}

int XmlParser::GetChildrenCount(XMLElement* element) {
    if(!element) return 0;
    
    int count = 0;
    for( XMLNode* ele = element->FirstChild(); ele; ele = ele->NextSibling() ) {
        count++;
    }
    CCLOG("element [%s] have [%d] children", element->Name(), count);
    return count;
}

int XmlParser::GetAttributeCount(XMLElement* element) {
    if(!element) return 0;
    int count = element->AttributeCount();
    CCLOG("element [%s] have [%d] attributions", element->Name(), count);
    return count;
}
