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
        
        // remove
        LevelDBManager::getInstance()->remove("version");
        LevelDBManager::getInstance()->remove("notfound");
        
        // select
        std::string ret;
        LevelDBManager::getInstance()->select("version", ret);
        LevelDBManager::getInstance()->select("code", ret);
        
        // dump
        LevelDBManager::getInstance()->dump();
        
        // disconnect
        LevelDBManager::getInstance()->disconnect(LevelDBCode::User);
    }
    
}
