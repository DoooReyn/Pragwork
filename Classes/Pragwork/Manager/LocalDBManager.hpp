//
//  LocalDBManager.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/3.
//
//

#ifndef LocalDBManager_hpp
#define LocalDBManager_hpp

#include "CocoSupport.h"

class LocalDBManager {
private:
    bool m_bconnected;
    static LocalDBManager* m_pInstance;
public:
    static LocalDBManager* getInstance();
    static void destroyInstance();
    
    bool connect();
    bool insert(const std::string key, const std::string value);
    bool remove(const std::string key);
    bool clear();
    const std::string select(const std::string key);
    const map<std::string, std::string> multiselect(const vector<std::string> keys);
    bool disconnect();
    
protected:
    LocalDBManager();
    ~LocalDBManager();
};

#endif /* LocalDBManager_hpp */
