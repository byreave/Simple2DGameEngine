#include "LuaCreateGO.h"
#include "Engine.h"
#include "SmartPointer.h"
#include "lua.hpp"
#include "ConsoleLog.h"
#include "PhysicsSystem.h"
#include "Renderable.h"
#include "Collision.h"
#include <assert.h>
namespace Engine {
	void RegisterController(std::string ControllerName, GlobalFuncPtr ControllerFactory)
	{
		assert(ControllerMapping->find(ControllerName) == ControllerMapping->end());
		
		ControllerMapping->emplace(ControllerName, ControllerFactory);
	}
	void CreateGO(const char * luaScript)

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
		assert(result == LUA_TTABLE);

		if (result == LUA_TTABLE)
		{
			//init data
			Point2D<float> initPos(0.0f, 0.0f);
			Vector3 initRot;
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
			assert(type == LUA_TNIL || type == LUA_TTABLE);

			float init_pos[3];
			size_t i = 0;
			lua_pushnil(pLuaState);
			while (lua_next(pLuaState, -2) != 0)
			{
				init_pos[i] = static_cast<float>(lua_tonumber(pLuaState, -1));
				DEBUG_PRINT("msg", "Integer from table %f.", init_pos[i]);
				i++;
				lua_pop(pLuaState, 1);
			}
			i = 0;
			lua_pop(pLuaState, 1);
			initPos.setX(init_pos[0]);
			initPos.setY(init_pos[1]);
			//get initial rotation
			lua_pushstring(pLuaState, "initial_rotation");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNIL || type == LUA_TTABLE);
			i = 0;
			lua_pushnil(pLuaState);
			while (lua_next(pLuaState, -2) != 0)
			{
				init_pos[i] = static_cast<float>(lua_tonumber(pLuaState, -1));
				DEBUG_PRINT("msg", "Integer from table %f.", init_pos[i]);
				i++;
				lua_pop(pLuaState, 1);
			}
			i = 0;
			lua_pop(pLuaState, 1);
			initRot.setX(init_pos[0]);
			initRot.setY(init_pos[1]);
			initRot.setZ(init_pos[2]);
			//Create game object
			auto spNewPlayer = StrongPointer<GameObject>(new GameObject(name, initLives, initPos, initRot));
			delete name;
			AllGameObjects.push_back(spNewPlayer);
			//get physics setting
			lua_pushstring(pLuaState, "physics_settings");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNIL || type == LUA_TTABLE);
			if (type == LUA_TTABLE)
			{
				float mass = 2.0f, drag = 0.0f;
				bool kinematic = false;
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

				//Kinematic?
				lua_pushstring(pLuaState, "kinematic");
				type = lua_gettable(pLuaState, -2);
				assert(type == LUA_TBOOLEAN);
				kinematic = static_cast<bool>(lua_toboolean(pLuaState, -1));
				lua_pop(pLuaState, 1);


				Physics::PhysicsSystem * tmpPhysics = new Physics::PhysicsSystem(spNewPlayer, mass, drag, kinematic);
				Physics::PhysicsInfo.push_back(tmpPhysics);
			}
			lua_pop(pLuaState, 1);

			//render
			lua_pushstring(pLuaState, "render_settings");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNIL || type == LUA_TTABLE);
			if (type == LUA_TTABLE)
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
			//Collision
			lua_pushstring(pLuaState, "collision_settings");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNIL || type == LUA_TTABLE);
			if (type == LUA_TTABLE)
			{
				Point2D<float> center, extents;
				//center
				lua_pushstring(pLuaState, "center");
				type = lua_gettable(pLuaState, -2);
				assert(type == LUA_TTABLE);
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
				i = 0;
				lua_pop(pLuaState, 1);
				center.setX(init_pos[0]);
				center.setY(init_pos[1]);
				//extents
				lua_pushstring(pLuaState, "extents");
				type = lua_gettable(pLuaState, -2);
				assert(type == LUA_TTABLE);
				lua_pushnil(pLuaState);
				while (lua_next(pLuaState, -2) != 0)
				{
					init_pos[i] = static_cast<float>(lua_tonumber(pLuaState, -1));
					DEBUG_PRINT("msg", "Integer from table %f.", init_pos[i]);
					i++;
					lua_pop(pLuaState, 1);
				}
				lua_pop(pLuaState, 1);
				extents.setX(init_pos[0]);
				extents.setY(init_pos[1]);
				//Create Collision
				CollisionSystem::Collision * tmpCol = new CollisionSystem::Collision(spNewPlayer, center, extents);
				CollisionSystem::CollisionObjects.push_back(tmpCol);
			}
			lua_pop(pLuaState, 1);
			//controller
			lua_pushstring(pLuaState, "controller");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TNIL || type == LUA_TSTRING);
			if (type == LUA_TSTRING)
			{
				std::string controller(lua_tostring(pLuaState, -1));
				(*ControllerMapping)[controller](spNewPlayer);
			}
		}
		lua_close(pLuaState);
		delete pFileContents;
	}

}
