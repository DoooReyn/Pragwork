//
//  LevelDBManager.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/5.
//
//

#include "LevelDBManager.hpp"
#include "CocoSupport.h"


LevelDBManager* LevelDBManager::m_pInstance = NULL;

LevelDBManager::LevelDBManager() {
    m_pDatabase = NULL;
    m_eDBCode = LevelDBCode::None;
}

LevelDBManager::~LevelDBManager() {
    CC_SAFE_DELETE(m_pDatabase);
}

leveldb::Status LevelDBManager::connect(LevelDBCode code) {
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, FileUtils::getInstance()->fullPathForFilename(MapLevelDB.at(code)), &m_pDatabase);
    if(status.ok()) {
        m_eDBCode = code;
        CCLOG("Database : %s\t connect %s", MapLevelDB.at(code).c_str(), status.ToString().c_str());
    } else {
        CCLOG("!!! [warning] Database : %s\t connect : %s", MapLevelDB.at(code).c_str(), status.ToString().c_str());
    }
    return status;
}


leveldb::Status LevelDBManager::insert(const std::string key, const std::string value, bool sync) {
    leveldb::WriteOptions options;
    options.sync = sync;
    leveldb::Status status;
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        status = m_pDatabase->Put(options, key, value);
        CCLOG("Database : %s\t insert $(%s) #(%s)", MapLevelDB.at(m_eDBCode).c_str(), key.c_str(), value.c_str());
    }
    return status;
}

leveldb::Status LevelDBManager::remove(const std::string key, bool sync) {
    leveldb::WriteOptions options;
    options.sync = sync;
    leveldb::Status status;
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        status = m_pDatabase->Delete(options, key);
        CCLOG("Database : %s\t delete $(%s)", MapLevelDB.at(m_eDBCode).c_str(), key.c_str());
    }
    return status;
}

leveldb::Status LevelDBManager::select(const std::string key, std::string& value) {
    leveldb::ReadOptions options;
    leveldb::Status status;
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        status = m_pDatabase->Get(options, key, &value);
        CCLOG("Database : %s\t seclect $(%s) #(%s)", MapLevelDB.at(m_eDBCode).c_str(), key.c_str(), value.c_str());
    }
    return status;
}

void LevelDBManager::disconnect(LevelDBCode code) {
    if(m_eDBCode == code) {
        CC_SAFE_DELETE(m_pDatabase);
        CCLOG("Database : %s\t disconnected", MapLevelDB.at(m_eDBCode).c_str());
    }
}

void LevelDBManager::dump() {
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        leveldb::Iterator* it = m_pDatabase->NewIterator(leveldb::ReadOptions());
        CCLOG("Database : %s\t dump", MapLevelDB.at(m_eDBCode).c_str());
        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            CCLOG(" ==> DUMP: $(%s) #(%s)", it->key().ToString().c_str(), it->value().ToString().c_str());
        }
    }
}

void LevelDBManager::seek(std::string start, std::string limit) {
    if(m_pDatabase || connect(m_eDBCode).ok()) {
        leveldb::Iterator* it = m_pDatabase->NewIterator(leveldb::ReadOptions());
        
        it->SeekToLast();
        const leveldb::Slice last = it->key();
        if(limit.empty()) {
            limit = last.ToString();
        }
        
        it->SeekToFirst();
        if(!start.empty()) {
            it->Seek(start);
        }
        
        CCLOG("Database : %s\t seek ", MapLevelDB.at(m_eDBCode).c_str());
        
        for( ; it->Valid() && it->key().ToString() < limit; it->Next()) {
            CCLOG(" ==> SEEK: $(%s) #(%s)", it->key().ToString().c_str(), it->value().ToString().c_str());
        }
    }
}
