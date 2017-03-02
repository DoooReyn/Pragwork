//
//  TagDefine.h
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/1.
//
//

#ifndef TagDefine_h
#define TagDefine_h

enum class SceneTag : unsigned short {
    Main,
    CreateRole,
    Help,
    Game,
    Loading,
    Update
};

enum ActionTag : unsigned int {
    EnterBaseFrame,
    ExitBaseFrame,
};

enum FrameTag : unsigned int {
    Mask = 9999,
};
    
#endif /* TagDefine_h */

