//
//  global_parse.h
//  CLua
//
//  Created by dev on 2017/4/25.
//  Copyright © 2017年 dev. All rights reserved.
//

#ifndef global_parse_h
#define global_parse_h

void light_global_loop(lua_State* L);
char* light_global_parse(const char* path);
//过滤_G中关键字
void light_iskeyword();


#endif /* global_parse_h */
