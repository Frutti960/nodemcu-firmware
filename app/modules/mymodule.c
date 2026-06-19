#include "module.h"
#include "lauxlib.h"
#include "string.h"

// Функция шифрования
static int caesar_encrypt(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int shift = luaL_checkinteger(L, 2);
    int len = strlen(text);
    
    char *result = (char *)malloc(len + 1);
    if (!result) return luaL_error(L, "no memory");
    
    for (int i = 0; i < len; i++) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z')
            result[i] = ((c - 'A' + shift) % 26) + 'A';
        else if (c >= 'a' && c <= 'z')
            result[i] = ((c - 'a' + shift) % 26) + 'a';
        else
            result[i] = c;
    }
    result[len] = '\0';
    
    lua_pushstring(L, result);
    free(result);
    return 1;
}

// Функция расшифровки
static int caesar_decrypt(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int shift = luaL_checkinteger(L, 2);
    int len = strlen(text);
    
    char *result = (char *)malloc(len + 1);
    if (!result) return luaL_error(L, "no memory");
    
    for (int i = 0; i < len; i++) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z')
            result[i] = ((c - 'A' - shift + 26) % 26) + 'A';
        else if (c >= 'a' && c <= 'z')
            result[i] = ((c - 'a' - shift + 26) % 26) + 'a';
        else
            result[i] = c;
    }
    result[len] = '\0';
    
    lua_pushstring(L, result);
    free(result);
    return 1;
}

// Карта модуля
static const LUA_REG_TYPE caesar_map[] = {
    { LSTRKEY("encrypt"), LFUNCVAL(caesar_encrypt) },
    { LSTRKEY("decrypt"), LFUNCVAL(caesar_decrypt) },
    { LNILKEY, LNILVAL }
};

// Точка входа
int luaopen_caesar(lua_State *L) {
    return 0;
}

NODEMCU_MODULE(CAESAR, "caesar", caesar_map, luaopen_caesar);
