//
//  local_parse.h
//  CLua
//
//  Created by cheng on 2017/4/26.
//  Copyright © 2017年 cheng. All rights reserved.
//

#ifndef light_local_parse_h
#define light_local_parse_h

void light_local_loop(lua_State* L);
char* light_local_parse(const char* path);
#endif /* light_local_parse_h */
