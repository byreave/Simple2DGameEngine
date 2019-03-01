#pragma once
#include "GameObject.h"
#include "SmartPointer.h"
#include "lua.hpp"
#include "ConsoleLog.h"
#include <assert.h>
namespace Engine {

	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
	{
		assert(i_pFilename != NULL);

		FILE * pFile = NULL;

		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
		{
			DEBUG_PRINT("ERROR: ", "File Open Error!\n");
			return NULL;
		}

		assert(pFile != NULL);

		int FileIOError = fseek(pFile, 0, SEEK_END);
		assert(FileIOError == 0);

		long FileSize = ftell(pFile);
		assert(FileSize >= 0);

		FileIOError = fseek(pFile, 0, SEEK_SET);
		assert(FileIOError == 0);

		uint8_t * pBuffer = new uint8_t[FileSize];
		assert(pBuffer);

		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		assert(FileRead == FileSize);

		fclose(pFile);

		o_sizeFile = FileSize;

		return pBuffer;
	}
	//StrongPointer<GameObject> CreateGameObject(const char * luaScript)
	//{
	//	lua_State * pLuaState = luaL_newstate();
	//	assert(pLuaState);

	//	luaL_openlibs(pLuaState);
	//	size_t 		sizeFile = 0;
	//	uint8_t * 	pFileContents = static_cast<uint8_t *>(LoadFile(luaScript, sizeFile));

	//	if (pFileContents  && sizeFile)
	//	{
	//		int 		result = 0;

	//		// Necessary stuff to process our data
	//		result = luaL_loadbuffer(
	//			pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
	//		assert(result == 0);

	//		result = lua_pcall(pLuaState, 0, 0, 0);
	//		assert(result == 0);
	//	}
	//	int result = lua_getglobal(pLuaState, "Player");
	//	assert(result == LUA_TNIL || result == LUA_TTABLE);
	//	if (result == LUA_TTABLE)
	//	{
	//		lua_pushstring(pLuaState, "name");
	//		DEBUG_PRINT("Msg", "LUA gets name : %f", static_cast<float>(lua_tonumber(pLuaState, -2)));
	//		lua_pop(pLuaState, 1);
	//	}
	//	return NULL;
	//}

	void TestLua(const char * luaScript)
	{
		lua_State * pLuaState = luaL_newstate();
		assert(pLuaState);

		luaL_openlibs(pLuaState);
		size_t 		sizeFile = 0;
		uint8_t * 	pFileContents = static_cast<uint8_t *>(LoadFile(luaScript, sizeFile));

		if (pFileContents  && sizeFile)
		{
			int 		result = 0;

			// Necessary stuff to process our data
			result = luaL_loadbuffer(
				pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
			assert(result == 0);

			result = lua_pcall(pLuaState, 0, 0, 0);
			assert(result == 0);
		}

		int result = lua_getglobal(pLuaState, "Player");
		assert(result == LUA_TNIL || result == LUA_TTABLE);
		if (result == LUA_TTABLE)
		{
			// get name
			lua_pushstring(pLuaState, "name");
			int type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TSTRING);
			char * name = _strdup(lua_tostring(pLuaState, -1));
			lua_pop(pLuaState, 1);
			//get initial position
			lua_pushstring(pLuaState, "initial_position");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);
			lua_pushinteger(pLuaState, 0);
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNUMBER);

			DEBUG_PRINT("msg", "Integer from table %f.", static_cast<float>(lua_tonumber(pLuaState, -1)));
		}
	}
	
}