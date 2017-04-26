//
//  local_parse.h
//  CLua
//
//  Created by cheng on 2017/4/26.
//  Copyright © 2017年 cheng. All rights reserved.
//

#ifndef local_parse_h
#define local_parse_h

void lua_local_loop(lua_State* L);
char* lua_local_parse(const char* path);
#endif /* local_parse_h */
