//
//  LevelDBManager.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/5.
//
//

#ifndef LevelDBManager_hpp
#define LevelDBManager_hpp

#include <leveldb/db.h>

enum class LevelDBCode: unsigned char {
    None,
    User,
    Item,
};

const std::map<LevelDBCode, const std::string> MapLevelDB = {
    {LevelDBCode::None, "res/leveldb/temp"},
    {LevelDBCode::User, "res/leveldb/db_user"},
    {LevelDBCode::Item, "res/leveldb/db_item"},
};

class LevelDBManager {
private:
    leveldb::DB* m_pDatabase;
    LevelDBCode m_eDBCode;
    static LevelDBManager* m_pInstance;
public:
    static LevelDBManager* getInstance() {
        if(!m_pInstance)
            m_pInstance = new LevelDBManager();
        return m_pInstance;
    }
    leveldb::Status connect(LevelDBCode code);
    leveldb::Status insert(const std::string key, const std::string value, bool sync=false);
    leveldb::Status remove(const std::string key, bool sync=false);
    leveldb::Status select(const std::string key, std::string& value);
    void disconnect(LevelDBCode code);
    void dump();
    void seek(std::string start="", std::string limit="");
    bool compare(std::string key1, std::string key2);
private:
    LevelDBManager();
    ~LevelDBManager();
};

#endif /* LevelDBManager_hpp */
