//
//  local_parse.c
//  CLua
//
//  Created by cheng on 2017/4/26.
//  Copyright © 2017年 cheng. All rights reserved.
//
#include <stdio.h>
#include "lua.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "cJSON.h"


void light_local_loop(lua_State* L,cJSON* root){
    int it = lua_gettop(L);
    lua_pushnil(L);
    while (lua_next(L, it) ){
        const char* key = lua_tostring(L, -2);
        const char * value = "unknow";
        if(lua_istable(L, -1)){
            cJSON* node = cJSON_CreateObject();
            cJSON_AddItemToObject(root,key,node);
            light_local_loop(L,node);
        }else{
            if(lua_isuserdata(L, -1)){
                value = "userdata";
                cJSON_AddItemToObject(root,key,cJSON_CreateString(value));
            }else if(lua_isfunction(L, -1)){
                value = "function";
                cJSON_AddItemToObject(root,key,cJSON_CreateString(value));
            }else if(lua_isnumber(L, -1)){
                int n = lua_tonumber(L, -1);
                cJSON_AddItemToObject(root,key,cJSON_CreateNumber(n));
            }else if(lua_isboolean(L, -1)){
                cJSON_AddItemToObject(root,key,cJSON_CreateBool(lua_toboolean(L, -1)));
            }else if(lua_isnil(L, -1)){
                value = "nil";
                cJSON_AddItemToObject(root,key,cJSON_CreateString(value));
            }else{
                value = lua_tostring(L, -1);
                cJSON_AddItemToObject(root,key,cJSON_CreateString(value));
            }
        
//             printf("%s => %s\n",key ,value);
        }
        lua_pop(L, 1);
    }
}
/**
 *解析本地变量
 */
char* light_local_parse(const char* path){
    cJSON* root = cJSON_CreateObject();
    lua_State *L = luaL_newstate();  /* opens Lua */
    luaL_openlibs(L);   /* opens the standard libraries */
    int error = luaL_dofile(L,path); /* runs Lua script */
    if(error!=0){
        perror("语法错误");
        exit(0);
    }
    if(lua_istable(L, -2)){
        lua_gettable(L, -2);
    }
    light_local_loop(L,root);
    char *ret=cJSON_Print(root);
//    printf("ret = %s\n",ret);
    lua_close(L);
    return ret;
}

