//
//  global_parse.c
//  CLua
//
//  Created by dev on 2017/4/25.
//  Copyright © 2017年 dev. All rights reserved.
//

#include <stdio.h>
#include "lua.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "cJSON.h"

const char* KeyWord[] = {"io","select","rawequal","ipairs","os","utf8","require","package","bit32","rawlen","math","rawget"
                        ,"dofile","_VERSION","tostring","loadfile","error","debug","xpcall","table","require","type","ipairs",
                        "collectgarbage","tonumber","pairs","pcall","assert","select","rawset","load","string","setmetatable",
                        "next","_G","getmetatable","print","coroutine"};

void lua_global_loop(lua_State* L,cJSON* root){
    lua_pushnil(L);
    while (lua_next(L,-2))
    {
        const char * key =lua_tostring(L,-2);
        const char * value = "unknow";
        if(lua_iskeyword(key)!=1){
            if(lua_istable(L, -1)){
//                value = "table";
                cJSON* node = cJSON_CreateObject();
                cJSON_AddItemToObject(root,key,node);

                lua_global_loop(L,node);
            }else {
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

                printf("%s => %s\n",key ,value);
            }
        }
        lua_pop(L,1);

    }
}

void lua_global_parse(const char* path){
    cJSON* root = cJSON_CreateObject();
    lua_State *L = luaL_newstate();  /* opens Lua */
    luaL_openlibs(L);   /* opens the standard libraries */
    //    "/Users/dev/Documents/document/MyProject/CLua/CLua/config.lua"
    luaL_loadfile(L,path); /* runs Lua script */
    lua_pcall(L,0,0,0);
    int it = lua_gettop(L);
    printf("lua stack size:%d\n",it);
    lua_getglobal(L, "_G");
    if(lua_istable(L, -1)){
        printf("table\n");
        lua_gettable(L, -1);
        lua_global_loop(L,root);
    }
    char *ret=cJSON_Print(root);
    printf("ret = %s\n",ret);
}


int lua_iskeyword(const char* keyword){
//    int length = strlen(KeyWord);
    int i = 0;
    for(i = 0;i<38;i++){
        if(strcmp(KeyWord[i], keyword)==0){
            return 1;
        }
    }
    return 0;
}