//
//  LocalDBManager.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/3.
//
//

#include "Constant.h"
#include "LocalDBManager.hpp"

LocalDBManager* LocalDBManager::m_pInstance = NULL;

LocalDBManager::LocalDBManager()
{
    m_bconnected = false;
}

LocalDBManager::~LocalDBManager() {
    m_bconnected = false;
}

LocalDBManager* LocalDBManager::getInstance() {
    if(!m_pInstance) {
        m_pInstance = new LocalDBManager();
        m_pInstance->connect();
    }
    return m_pInstance;
}

void LocalDBManager::destroyInstance() {
    CC_SAFE_DELETE(m_pInstance);
    CCLOG("DBLocalManager Destroyed");
}

bool LocalDBManager::connect() {
    if(m_bconnected) {
        CCLOG("DB has connected.");
        return true;
    }
    std::string dbpath = FileUtils::getInstance()->fullPathForFilename(GLOBAL::DB_PATH);
    localStorageInit(dbpath);
    m_bconnected = true;
    CCLOG("DB is connected.");
    return m_bconnected;
}

bool LocalDBManager::disconnect() {
    if(!m_bconnected) {
        CCLOG("DB has disconnected.");
        return true;
    }
    localStorageFree();
    m_bconnected = false;
    CCLOG("DB is disconnected.");
    return m_bconnected;
}

bool LocalDBManager::insert(const std::string key, const std::string value) {
    if(!m_bconnected) connect();
    localStorageSetItem(key, value);
    CCLOG("DB insert key(%s) with value(%s).", key.c_str(), value.c_str());
    return m_bconnected;
}

bool LocalDBManager::remove(const std::string key) {
    if(!m_bconnected) connect();
    CCLOG("DB remove key(%s).", key.c_str());
    localStorageRemoveItem(key);
    return m_bconnected;
}

bool LocalDBManager::clear() {
    if(!m_bconnected) connect();
    localStorageClear();
    CCLOG("DB clear data.");
    disconnect();
    return m_bconnected;
}

const std::string LocalDBManager::select(const std::string key) {
    if(!m_bconnected) connect();
    std::string out = "";
    localStorageGetItem(key, &out);
    CCLOG("DB select key(%s) as value(%s).", key.c_str(), out.c_str());
    return out;
}
