#include "LuaCreateGO.h"
#include "Engine.h"
#include "GameObject.h"
#include "SmartPointer.h"
#include "lua.hpp"
#include "ConsoleLog.h"
#include "PhysicsSystem.h"
#include "Renderable.h"
#include <assert.h>
void Engine::CreateGO(const char * luaScript)

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
		//init data
		Point2D<float> initPos(0.0f, 0.0f);
		char * name;
		int initLives = 3;
		// get name
		lua_pushstring(pLuaState, "name");
		int type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TSTRING);
		name = _strdup(lua_tostring(pLuaState, -1));
		lua_pop(pLuaState, 1);
		//get initial lives
		lua_pushstring(pLuaState, "initial_lives");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		initLives = static_cast<int>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);
		//get initial position
		lua_pushstring(pLuaState, "initial_position");
		type = lua_gettable(pLuaState, -2);
		assert(result == LUA_TNIL || result == LUA_TTABLE);

		float init_pos[2];
		size_t i = 0;
		lua_pushnil(pLuaState);
		while (lua_next(pLuaState, -2) != 0)
		{
			init_pos[i] = static_cast<float>(lua_tonumber(pLuaState, -1));
			DEBUG_PRINT("msg", "Integer from table %f.", init_pos[i]);
			i++;
			lua_pop(pLuaState, 1);
		}
		lua_pop(pLuaState, 1);
		initPos.setX(init_pos[0]);
		initPos.setY(init_pos[1]);

		//Create game object
		auto spNewPlayer = StrongPointer<GameObject>(new GameObject(name, initLives, initPos));
		delete name;
		AllGameObjects.push_back(spNewPlayer);
		//get physics setting
		lua_pushstring(pLuaState, "physics_settings");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNIL || type == LUA_TTABLE);
		if (result == LUA_TTABLE)
		{
			float mass = 2.0f, drag = 0.0f;
			//mass
			lua_pushstring(pLuaState, "mass");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNUMBER);
			mass = static_cast<float>(lua_tonumber(pLuaState, -1));
			//DEBUG_PRINT("MSG", "STRING IN PHYSICS %f", lua_tonumber(pLuaState, -1));
			lua_pop(pLuaState, 1);

			//drag
			lua_pushstring(pLuaState, "drag");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNUMBER);
			drag = static_cast<float>(lua_tonumber(pLuaState, -1));
			lua_pop(pLuaState, 1);
			Physics::PhysicsSystem * tmpPhysics = new Physics::PhysicsSystem(spNewPlayer, mass, drag);
			Physics::PhysicsInfo.push_back(tmpPhysics);
		}
		lua_pop(pLuaState, 1);

		//render
		lua_pushstring(pLuaState, "render_settings");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNIL || type == LUA_TTABLE);
		if (result == LUA_TTABLE)
		{
			char * sprite;
			//mass
			lua_pushstring(pLuaState, "sprite");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TSTRING);
			sprite = _strdup(lua_tostring(pLuaState, -1));
			DEBUG_PRINT("MSG", "STRING IN RENDER %s", sprite);
			lua_pop(pLuaState, 1);

			auto pGoodGuy = Engine::CreateSprite(sprite);
			Render::Renderable * tmpRenderable = new Render::Renderable(spNewPlayer, pGoodGuy);
			delete sprite;
			Render::RenderableInfo.push_back(tmpRenderable);
		}
		lua_pop(pLuaState, 1);
	}
	lua_close(pLuaState);
	delete pFileContents;
}
