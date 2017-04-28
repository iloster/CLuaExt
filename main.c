//
//  main.c
//  CLua
//
//  Created by dev on 2017/4/20.
//  Copyright © 2017年 dev. All rights reserved.
//

#include <stdio.h>
//#include "lua.h"
//#include "lauxlib.h"
//#include "lualib.h"
#include "cJSON.h"
#include "light_main.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
//    const char* path ="/Users/dev/Documents/document/MyProject/CLua/CLua/config.lua";
//    const char* path="/Users/dev/Documents/CLuaExt/test/test.lua";
//    printf("%s\n",light_global_parse(path));
    const char* path="/Users/dev/Documents/CLuaExt/test/test1.lua";
    printf("%s\n",get(path,2));
//    printf("%s\n",getVersion());
    return 0;
}
