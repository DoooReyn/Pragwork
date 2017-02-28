//
//  SceneManager.cpp
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#include "SceneManager.hpp"
#include <iostream>
#include "UI/Scene/init.h"
USING_NS_CC;

SceneManager* SceneManager::m_pInstance = NULL;
SceneManager::SceneManager(){}
SceneManager::~SceneManager(){}

cocos2d::Scene* SceneManager::getRunningScene() {
    return Director::getInstance()->getRunningScene();
}


cocos2d::Scene* SceneManager::_loadScene(ESceneTree scene) {
    switch (scene)
    {
        case ESceneTree::HelloScene:
        {
            Scene* pScene = new Scene();
            pScene->addChild(HelloWorld::create());
            return pScene;
        }
            break;
//        case ESceneTree::MainScene:
////            return MainScene::create();
//        case ESceneTree::BattleScene:
////            return BattleScene::create();
//        case ESceneTree::LoadingScene:
////            return LoadingScene::create();
        default:
            return NULL;
    }
    return NULL;
}

void SceneManager::popScene() {
    Director::getInstance()->popScene();
}

bool SceneManager::pushScene(ESceneTree scene) {
    auto newScene = _loadScene(scene);
    if(!newScene) return false;
    Director::getInstance()->pushScene(newScene);
    return true;
}

cocos2d::Scene* SceneManager::runScene(ESceneTree scene) {
    auto newScene = _loadScene(scene);
    if(newScene) {
        if(getRunningScene())
            Director::getInstance()->replaceScene(newScene);
        else
            Director::getInstance()->runWithScene(newScene);
        return newScene;
    }
    return NULL;
}
