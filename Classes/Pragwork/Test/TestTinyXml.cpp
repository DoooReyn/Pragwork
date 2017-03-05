//
//  TestTinyXml.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//
#include "TestTinyXml.hpp"
#include "CocoSupport.h"
#include "XmlParser.hpp"


void TinyXmlTestcase() {

    XMLDocument* doc2 = XmlParser::getInstance()->GetDocument("config/cc_data/Vip.xml");
    if(doc2) {
        doc2->Print();
        XmlParser::getInstance()->GetChildrenCount(doc2->RootElement());
        doc2->RootElement()->FirstChildElement()->Attributes();
    }
    
}

