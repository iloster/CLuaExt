//
//  light_main.c
//  CLua
//
//  Created by dev on 2017/4/27.
//  Copyright © 2017年 dev. All rights reserved.
//

#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "light_local.h"
#include "light_global.h"

#define MODE_GOBAL 1
#define MODE_LOCAL 2
#define LIGHT_VERSION "light v1.0.0"

int main(int argc, const char * argv[]) {
    return 0;
}
/**
 *@path lua文件的路径
 *@mode 是全局的是局部变量的方式
 *@return 将table转换成json
 */
char* getLight(const char* path,int mode){
    if(MODE_GOBAL == mode){
//     全局变量的方式
        return light_global_parse(path);
    }else if(MODE_LOCAL == mode){
//        局部变量的方式
        return light_local_parse(path);
    }
    return NULL;
}


/**
 *@param null
 *@return lua的版本号
 */
char* getLuaVersion(){
    return LUA_RELEASE;
}


/**
 *@param null
 *@return light的版本号
 */
char* getVersion(){
    return LIGHT_VERSION;
}
