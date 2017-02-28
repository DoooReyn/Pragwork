//
//  SceneManager.hpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

//场景树
enum class ESceneTree : unsigned short {
    LoadingScene,   //加载场景
    HelloScene,     //测试场景
    MainScene,      //主场景
    BattleScene,    //战斗场景
};

// 场景树管理
class SceneManager {
private:
    static SceneManager* m_pInstance;
    
public:
    static SceneManager* getInstance() {
        if (m_pInstance) return m_pInstance;
        return m_pInstance = new SceneManager();
    }
    
    cocos2d::Scene* getRunningScene();
    cocos2d::Scene* runScene(ESceneTree scene);
    bool pushScene(ESceneTree scene);
    void popScene();
    
protected:
    SceneManager();
    ~SceneManager();

private:
    cocos2d::Scene* _loadScene(ESceneTree scene);
    
};

#endif /* SceneManager_hpp */
