//
//  VersionDefine.h
//  Pragwork
//
//  Created by Reyn-Mac on 2017/3/1.
//
//

#ifndef VersionDefine_h
#define VersionDefine_h

//#define DISABLE_LOG 0
#define DEBUG_VERSION 1

#ifdef DISABLE_LOG
#define LOG(...) do() {} while(0)
#else
#ifdef DEBUG_VERSION
#define LOG(format, ...) CCLOG("[Pragwork]====");CCLOG(format, ##__VA_ARGS__)
#else
#define LOG(format, ...) printf("[Pragwork]====");CCLOG(format, ##__VA_ARGS__)
#endif
#endif


#endif /* VersionDefine_h */
