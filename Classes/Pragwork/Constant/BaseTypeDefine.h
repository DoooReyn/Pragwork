//
//  BaseTypes.h
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#ifndef BaseTypes_h
#define BaseTypes_h

//#include <iostream>

typedef const char* CStr;
typedef std::string HexStr;
typedef unsigned HexBit;

#define RGB_MAX 255
#define RGB_MIN 0

enum ErrorAlertType{
    EAT_OK_CANCEL_TEXT,
    EAT_OK_TEXT,
    EAT_OK_TEXT_UNCLOSEABLE,
};

#endif/* BaseTypes_h */
