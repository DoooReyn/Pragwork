//
//  GameState.h
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/1.
//
//

#ifndef GameState_h
#define GameState_h

enum class GAME_STATE : unsigned short {
    DEFAULT = 0,
    INIT,
    LOAD_INIT,
    UPDATE,
    
    MAIN,
    CREATE_ROLE,
    GUIDE,
    
    PAUSE,
    RESUME,
    EXIT,
};

#endif /* GameState_h */
