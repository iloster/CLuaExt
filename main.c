//
//  main.c
//  CLua
//
//  Created by dev on 2017/4/20.
//  Copyright © 2017年 dev. All rights reserved.
//

#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "cJSON.h"



static const char * load_config = "\
local config_name = ...\
local f = assert(io.open(config_name))\
local code = assert(f:read \'*a\')\
local function getenv(name) return assert(os.getenv(name), \'os.getenv() failed: \' .. name) end\
code = string.gsub(code, \'%$([%w_%d]+)\', getenv)\
f:close()\
local result = {}\
assert(load(code,\'=(load)\',\'t\',result))()\
return result\
";

void printTable(lua_State* L,cJSON* root){
    int it = lua_gettop(L);
    printf("lua stack size:%d\n",it);
    lua_pushnil(L);
    while (lua_next(L, it) ){
        const char* key = lua_tostring(L, -2);
        printf("key:%s\n",key);
        if(lua_istable(L, -1)){
            cJSON* node = cJSON_CreateObject();
            cJSON_AddItemToObject(root,key,node);
            printTable(L,node);
        }else{
            const char* value = lua_tostring(L, -1);
            cJSON_AddItemToObject(root,key,cJSON_CreateString(value));
            printf("value:%s\n",value);
        }
        lua_pop(L, 1);
    }
}

void init(){
    cJSON* root = cJSON_CreateObject();
    
    lua_State *L = luaL_newstate();  /* opens Lua */
    luaL_openlibs(L);   /* opens the standard libraries */
    
    int error = luaL_dofile(L,"/Users/dev/Documents/document/MyProject/CLua/CLua/test.lua"); /* runs Lua script */
    if(error == 0){
        if(lua_istable(L, -2)){
            printf("this is table\n");
            lua_gettable(L, -2);
        }
        printTable(L,root);
        char *ret=cJSON_Print(root);
        printf("ret = %s\n",ret);
        lua_close(L);
    }else{
        printf("load lua file error!!!");
    }


}

void skynet_init(){

    lua_State *L = luaL_newstate();  /* opens Lua */
    luaL_openlibs(L);   /* opens the standard libraries */
    
    luaL_loadfile(L,"/Users/dev/Documents/document/MyProject/CLua/CLua/config.lua"); /* runs Lua script */
    lua_pcall(L,0,0,0);
    int it = lua_gettop(L);
    printf("lua stack size:%d\n",it);
    lua_getglobal(L, "_G");
    if(lua_istable(L, -1)){
        printf("table\n");
        lua_gettable(L, -1);
        lua_pushnil(L);
        while (lua_next(L,-2))
        {
            lua_pushvalue(L,-2);
            const char * key =lua_tostring(L,-1);
            const char * value = lua_tostring(L,-2);
            printf("%s => %s\n",key ,value);
            lua_pop(L,2);
        }

    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    init();
//    skynet_init();
    return 0;
}
