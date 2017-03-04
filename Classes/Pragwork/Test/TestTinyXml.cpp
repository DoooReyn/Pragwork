//
//  TestTinyXml.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/4.
//
//
#include "CocoSupport.h"
#include "TestTinyXml.hpp"
#include <iostream>
using namespace std;

void testcase_create() {
//    const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
//    XMLDocument doc;
//    doc.Parse(declaration);
//    
//    XMLElement* root = doc.NewElement("DBUSER");
//    doc.InsertEndChild(root);
//    
//    std::string path = FileUtils::getInstance()->fullPathForFilename("test.xml");
//    CCLOG("xml Path = %s", path.c_str());
//    doc.SaveFile("config/cc_data/test.xml");
    
    XMLDocument doc;
    XMLError errCode = doc.LoadFile("cc_data/Vip.xml");
    if(errCode > 0) {
//        CCLOG("")
        doc.PrintError();
    } else {
        doc.Print();
    }
}

void testcase_addNode() {
    
}

void testcase_findNode() {
    
}

void testcase_modifyNode() {
    
}

void testcase_removeNode() {
    
}

void testcase_dump() {
    
}
