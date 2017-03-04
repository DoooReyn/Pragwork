//
//  TestLevelDB.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/5.
//
//

#include "TestLevelDB.hpp"
#include <cassert>
#include "LevelDBManager.hpp"
#include "CocoSupport.h"

void LevelDBTestCase() {
    leveldb::Status status = LevelDBManager::getInstance()->connect(LevelDBCode::User);
    if(status.ok()) {
        // insert
        LevelDBManager::getInstance()->insert("version", "0.0.1", true);
        LevelDBManager::getInstance()->insert("code", "100", true);
        LevelDBManager::getInstance()->insert("xml", "false", true);
        LevelDBManager::getInstance()->insert("test1", "false", false);
        LevelDBManager::getInstance()->insert("test2", "fals");
        LevelDBManager::getInstance()->insert("test3", "fal");
        LevelDBManager::getInstance()->insert("test4", "fa");
        LevelDBManager::getInstance()->insert("test5", "f");
        
        // remove
        LevelDBManager::getInstance()->remove("version");
        LevelDBManager::getInstance()->remove("notfound");
        
        // select
        std::string ret;
        LevelDBManager::getInstance()->select("version", ret);
        LevelDBManager::getInstance()->select("code", ret);
        LevelDBManager::getInstance()->select("xml", ret);
        
        // dump
        LevelDBManager::getInstance()->dump();
        
        // disconnect
        LevelDBManager::getInstance()->disconnect(LevelDBCode::User);
        
        // seek
        LevelDBManager::getInstance()->seek("test1", "test3");
        LevelDBManager::getInstance()->seek("", "test4");
        LevelDBManager::getInstance()->seek("", "test6");
        LevelDBManager::getInstance()->seek("", "");
    }
    
}
